#include "AppController.h"

#include <iostream>

#include <indicators/block_progress_bar.hpp>
#include <indicators/cursor_control.hpp>

#include "Action.h"
#include "OutputFormat.h"
#include "render/RendererFactory.h"

#ifdef WIN32
#include "progressbar/DefaultProgressBar.h"
#else
#include "progressbar/BlockProgressBar.h"
#endif

using namespace qrz;

AppController::AppController()
{
	initialize();
}

/**
 * @brief Initializes the application by setting up the necessary configurations and checking for authentication.
 *
 * This function is responsible for initializing the application. It checks if a callsign is set in the configuration,
 * and if not, prompts the user to enter their callsign. It also sets the callsign in the QRZ API client. Then, it checks
 * if a session key and session expiration are set in the configuration. If not, it refreshes the token by fetching a new
 * session key and expiration from the QRZ API. If the token is already expired, it refreshes it as well. Finally, it sets
 * the session key and expiration in the QRZ API client.
 */
void AppController::initialize()
{
	std::string userCall;

	if (!config.hasCallsign())
	{
		userCall = getUserCallsignFromUser();

		config.setCallsign(userCall);
		config.saveConfig();
	}

	userCall = config.getCallsign();

	client.setUsername(userCall);

	if (!config.hasSessionKey() || !config.hasSessionExpiration())
	{
		refreshToken();
	}
	else
	{
		client.setSessionKey(config.getSessionKey());
		client.setSessionExpiration(config.getSessionExpiration());

		if (!client.tokenIsValid())
		{
			refreshToken();
		}
	}

	client.setSessionKey(config.getSessionKey());
	client.setSessionExpiration(config.getSessionExpiration());
}


/**
 * @brief Handles a command by performing an action based on the command's action type.
 *
 * This function takes an AppCommand object and performs different operations based on the command's action type.
 * The action type determines the type of operation to be performed.
 *
 * @param command The AppCommand object representing the command to be executed.
 */
void AppController::handleCommand(const AppCommand &command)
{
	switch (command.getAction())
	{
		case Action::CALLSIGN_ACTION:
			fetchAndRenderCallsigns(command.getSearchTerms(), command.getFormat());
			break;
		case Action::BIO_ACTION:
			fetchAndRenderBios(command.getSearchTerms());
			break;
		case Action::DXCC_ACTION:
			fetchAndRenderDXCC(command.getSearchTerms(), command.getFormat());
			break;
	}
}

/**
 * @brief Fetches and renders callsigns based on the given search terms and output format.
 *
 * This function takes a set of search terms and an output format and fetches the callsign records using the fetchCallsignRecords function.
 * It then creates a renderer object based on the output format using the RendererFactory and renders the callsigns using the Render function.
 * After rendering, it updates the application configuration from the client state.
 *
 * @param searchTerms The set of search terms used to fetch the callsign records.
 * @param format The output format in which the callsigns should be rendered.
 */
void AppController::fetchAndRenderCallsigns(const std::set<std::string> &searchTerms, const OutputFormat &format)
{
	const std::vector<Callsign> callsigns = fetchCallsignRecords(searchTerms);

	std::unique_ptr<render::Renderer<Callsign>> renderer = render::RendererFactory::createCallsignRenderer(format);

	renderer->Render(callsigns);

	updateConfigFromClientState();
}

/**
* @brief Fetches and renders DXCC records based on the given search terms and output format.
*
* This function takes a set of search terms and an output format and fetches the DXCC records using the fetchDXCCRecords function.
* It then creates a renderer object based on the output format using the RendererFactory and renders the DXCC records using the Render function.
* After rendering, it updates the application configuration from the client state.
*
* @param searchTerms The set of search terms used to fetch the DXCC records.
* @param format The output format in which the DXCC records should be rendered.
*/
void AppController::fetchAndRenderDXCC(const std::set<std::string> &searchTerms, const OutputFormat &format)
{
	const std::vector<DXCC> dxccRecords = fetchDXCCRecords(searchTerms);

	std::unique_ptr<render::Renderer<DXCC>> renderer = render::RendererFactory::createDXCCRenderer(format);

	renderer->Render(dxccRecords);

	updateConfigFromClientState();
}

/**
 * @brief Fetches and renders bios based on the given search terms.
 *
 * This function fetches the specified callsign records and renders them.
 *
 * Unlike callsigns and DXCC records, bio HTML content is rendered directly as it is received from the QRZ API.
 *
 * @param searchTerms The set of search terms used to fetch the bio content.
 */
void AppController::fetchAndRenderBios(const std::set<std::string> &searchTerms)
{
	std::unique_ptr<render::Renderer<std::string>> renderer = render::RendererFactory::createBioRenderer();

	std::vector<std::string> bios = fetchBios(searchTerms);

	renderer->Render(bios);

	updateConfigFromClientState();
}

/**
 * @brief Fetches the callsign records based on the given search terms.
 *
 * This function fetches the callsign records based on the provided search terms.
 * It makes API calls to retrieve the callsigns and stores them in a vector.
 * It handles authentication errors and retries the API call after refreshing the token.
 * It also displays a progress bar to show the progress of fetching the callsigns.
 *
 * @param searchTerms The set of search terms used to fetch the callsign records.
 * @return A vector of Callsign objects representing the fetched callsign records.
 *
 * @note This function assumes that the necessary APIs and client objects are properly initialized before calling this function.
 * @note This function prints any errors encountered during the API calls to the standard error stream.
 * @note This function sets the progress bar option and progress values to reflect the progress of fetching the callsigns.
 */
std::vector<Callsign> AppController::fetchCallsignRecords(const std::set<std::string> &searchTerms)
{
	// Buffer for the output
	std::vector<Callsign> callsigns;

	// Error buffer, we will display the errors after all API calls have been made and progress bar is removed
	std::vector<std::string> errors;

	// Display our progress bar
	auto bar = buildProgressBar();

	// Progress bar value
	auto progress = 0.0f;

	// Amount to advance the progress bar after each call
	float tickSize = 100/searchTerms.size();

	// Use an iterator so we cen reset the current element in the event of authentication error
	for (auto it = searchTerms.begin() ; it != searchTerms.end() ; it++)
	{
		const std::string &call = *it;

		try
		{
			// Hide the cursor - we do this on every iteration in case we hit an authentication error previously
			showConsoleCursor(false);

			// Update progress bar
			bar->setOption(indicators::option::PostfixText{std::format("Fetching {:s}", call)});
			bar->setProgress(progress);

			progress += tickSize;

			// Fetch the callsign and add it to the output buffer
			Callsign callsign = client.fetchCallsign(call);

			callsigns.push_back(callsign);

			// Reset the fail counter
			resetFailedCallCount();
		}
		catch (AuthenticationException &e)
		{
			// If we have not exceeded the max fail count, try to authenticate
			if (m_failedCallCount < m_maxFailedCallCount)
			{
				// Hide the progress bar and give the cursor back
				eraseLine();
				showConsoleCursor(true);

				// Ask the user for their password, and refresh the bearer token
				refreshToken();

				// Roll the iterator back to retry this call
				it = std::prev(it);

				// Increment the error counter so we don't do this forever
				m_failedCallCount++;
			}
			else
			{
				// Save the error for display after we have mde all of our API calls
				errors.push_back(std::format("QRZ API Error: {:s}", e.what()));
			}
		}
		catch (std::exception &e)
		{
			// Save the error for display after we have mde all of our API calls
			errors.emplace_back(e.what());
		}
	}

	// Finalize and tear down the progress bar
	bar->setOption(indicators::option::PostfixText{""});
	bar->setProgress(100);
	eraseLine();
	showConsoleCursor(true);

	// Print the errors, if any
	for(const std::string& error : errors)
	{
		std::cerr << error << std::endl;
	}

	return callsigns;
}

/**
 * @brief Fetches DXCC records based on the given search terms.
 *
 * This function fetches DXCC records based on the provided search terms. It uses the QRZ API client to fetch the records
 * for each term in the searchTerms set. If an authentication error occurs, it retries the call after refreshing the
 * authentication token. Any errors that occur during the fetch process are stored in the errors vector.
 *
 * @param searchTerms The set of search terms used to fetch the DXCC records.
 * @return A vector of DXCC objects representing the fetched DXCC records.
 */
std::vector<DXCC> AppController::fetchDXCCRecords(const std::set<std::string> &searchTerms)
{
	std::vector<DXCC> dxccs;
	std::vector<std::string> errors;

	showConsoleCursor(false);

	auto bar = buildProgressBar();

	auto progress = 0.0f;

	float tickSize = 100/searchTerms.size();

	// Use an iterator so we cen reset the current element in the event of authentication error
	for (auto it = searchTerms.begin() ; it != searchTerms.end() ; it++)
	{
		const std::string &term = *it;

		try
		{
			bar->setOption(indicators::option::PostfixText{std::format("Fetching {:s}", term)});
			bar->setProgress(progress);

			progress += tickSize;

			dxccs.push_back(client.fetchDXCC(term));

			resetFailedCallCount();
		}
		catch (AuthenticationException &e)
		{
			if (m_failedCallCount < m_maxFailedCallCount)
			{
				refreshToken();

				// Roll the iterator back to retry this call
				it = std::prev(it);

				m_failedCallCount++;
			}
			else
			{
				errors.push_back(std::format("QRZ API Error: {:s}", e.what()));
			}
		}
		catch (std::exception &e)
		{
			errors.emplace_back(e.what());
		}
	}

	bar->setOption(indicators::option::PostfixText{""});
	bar->setProgress(100);

	eraseLine();
	showConsoleCursor(true);

	for(const std::string& error : errors)
	{
		std::cerr << error << std::endl;
	}

	return dxccs;
}

/**
 * @brief Fetches and returns a vector of bios based on the given search terms.
 *
 * This function fetches the specified bio records and returns a vector of bio HTML strings.
 * It uses the QRZ API client to fetch the bios for each search term.
 *
 * @param searchTerms The set of search terms used to fetch the bios.
 * @return A vector of strings representing the fetched bios.
 *
 * @note This function assumes that the necessary APIs and client objects are properly initialized before calling this function.
 */
std::vector<std::string> AppController::fetchBios(const std::set<std::string> &searchTerms)
{
	std::vector<std::string> bios;
	std::vector<std::string> errors;

	// Use an iterator so we cen reset the current element in the event of authentication error
	for (auto it = searchTerms.begin() ; it != searchTerms.end() ; it++)
	{
		const std::string &call = *it;

		try
		{
			bios.push_back(client.fetchBio(call));

			resetFailedCallCount();
		}
		catch (AuthenticationException &e)
		{
			if (m_failedCallCount < m_maxFailedCallCount)
			{
				refreshToken();

				// Roll the iterator back to retry this call
				it = std::prev(it);

				m_failedCallCount++;
			}
			else
			{
				errors.push_back(std::format("QRZ API Error: {:s}", e.what()));
			}
		}
		catch (std::exception &e)
		{
			errors.emplace_back(e.what());
		}
	}

	for(const std::string& error : errors)
	{
		std::cerr << error << std::endl;
	}

	return bios;
}

/**
 * @brief Refreshes the access token by fetching a new token from the QRZ API
 *
 * This function refreshes the access token by fetching a new token from the QRZ API.
 * It retrieves the password from the configuration, and if it is empty, prompts the user to enter it.
 * The function then sets the username and password in the QRZ client, fetches a new token,
 * and updates the configuration with the new session information.
 *
 * @note This function assumes that the necessary APIs and client objects are properly initialized before calling this function.
 */
void AppController::refreshToken()
{
	std::string password = config.getPassword();

	if(password.empty())
	{
		password = getPasswordFromUser();
	}

	std::string userCall = config.getCallsign();

	client.setUsername(userCall);
	client.setPassword(password);

	client.fetchToken();

	updateConfigFromClientState();
}

/**
* @brief Retrieves the user's callsign from the user.
*
* This function prompts the user to enter their callsign and reads the input from the console.
*
* @return A string representing the user's callsign.
*/
std::string AppController::getUserCallsignFromUser()
{
	std::string userCall;

	std::cout << "Enter your callsign:" << std::endl;

	std::cin >> userCall;

	return userCall;
}

/**
 * @brief Retrieves the password from the user.
 *
 * This function prompts the user to enter their password and reads the input from the console.
 *
 * @return A string representing the user's password.
 */
std::string AppController::getPasswordFromUser()
{
	std::string userCall = config.getCallsign();

	std::cout << "Login required. Enter the QRZ password for " << userCall << ":" << std::endl;

	SetStdinEcho(false);

	std::string password;
	std::cin >> password;

	SetStdinEcho(true);

	// We only set the password here, so store
	config.setPassword(password);
	config.saveConfig();

	return password;
}

/**
 * @brief Updates the application configuration based on the state of the QRZ API client.
 *
 * This function updates the application configuration by setting the callsign, session key, and session expiration
 * from the QRZ API client. It then saves the configuration.
 *
 * @note This function assumes that the QRZ API client and application configuration objects are properly initialized.
 */
void AppController::updateConfigFromClientState()
{
	config.setCallsign(client.getUsername());
	config.setSessionKey(client.getSessionKey());
	config.setSessionExpiration(client.getSessionExpiration());
	config.saveConfig();
}

/**
 * @brief Resets the counter for failed API calls.
 *
 * This function resets the counter for failed API calls. It sets the value of m_failedCallCount to 0.
 */
void AppController::resetFailedCallCount()
{
	m_failedCallCount = 0;
}

/**
 * @brief Changes the visibility of the console cursor.
 *
 * This function sets the visibility of the console cursor based on the value of the parameter `show`.
 * If `show` is `true`, the console cursor will be displayed. If `show` is `false`, the console cursor will be hidden.
 *
 * @param show A boolean value indicating whether to show or hide the console cursor.
 */
inline void AppController::showConsoleCursor(bool const show) {
	std::fputs(show ? "\033[?25h" : "\033[?25l", stderr);
}

#ifdef WIN32
/**
 * @brief Erases the current line in the console.
 *
 * This function erases the current line in the console, allowing for output to be overwritten.
 * It uses the escape sequences "\x1b[1A" and "\x1b[2K" to move the cursor to the beginning of the line and clear all characters.
 */
inline void AppController::eraseLine() {
	std::fputs("\x1b[1A", stderr);
	std::fputs("\x1b[2K", stderr);
}

/**
 * @brief Create a new instance of ProgressBar.
 *
 * This static member function creates a new instance of ProgressBar and returns it as a unique_ptr.
 * It creates an instance of the BlockProgressBar class, which is a concrete implementation of the ProgressBar interface.
 *
 * @return A unique_ptr to a ProgressBar object.
 */
std::unique_ptr<ProgressBar> AppController::buildProgressBar()
{
	return std::make_unique<DefaultProgressBar>();
}
#else
/**
* @brief Erases the current line in the console.
*
* This function erases the current line in the console, allowing for output to be overwritten.
* It uses the escape sequence "\r\033[K" to move the cursor to the beginning of the line and clear all characters.
*/
inline void AppController::eraseLine() {
	std::fputs("\r\033[K", stderr);
}

/**
 * @brief Create a new instance of ProgressBar.
 *
 * This static member function creates a new instance of ProgressBar and returns it as a unique_ptr.
 * It creates an instance of the BlockProgressBar class, which is a concrete implementation of the ProgressBar interface.
 *
 * @return A unique_ptr to a ProgressBar object.
 */
std::unique_ptr<ProgressBar> AppController::buildProgressBar()
{
	return std::make_unique<BlockProgressBar>();
}
#endif
