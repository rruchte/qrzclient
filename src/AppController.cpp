#include "AppController.h"

#include <iostream>

#include <indicators/block_progress_bar.hpp>
#include <indicators/cursor_control.hpp>

#include "Action.h"
#include "AppFormat.h"
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

void AppController::handleCommand(const AppCommand &command)
{
	switch (command.getAction())
	{
		case Action::CALLSIGN_ACTION:
			fetchAndRenderCallsigns(command.getSearchTerms(), command.getFormat());
			break;
		case Action::BIO_ACTION:
			fetchAndRenderBios(command.getSearchTerms(), command.getFormat());
			break;
		case Action::DXCC_ACTION:
			fetchAndRenderDXCC(command.getSearchTerms(), command.getFormat());
			break;
	}
}

void AppController::fetchAndRenderCallsigns(const std::set<std::string> &searchTerms, const AppFormat &format)
{
	const std::vector<Callsign> callsigns = fetchCallsignRecords(searchTerms);

	std::unique_ptr<render::Renderer<Callsign>> renderer = render::RendererFactory::createCallsignRenderer(format);

	renderer->Render(callsigns);

	updateConfigFromClientState();
}

void AppController::fetchAndRenderDXCC(const std::set<std::string> &searchTerms, const AppFormat &format)
{
	const std::vector<DXCC> dxccRecords = fetchDXCCRecords(searchTerms);

	std::unique_ptr<render::Renderer<DXCC>> renderer = render::RendererFactory::createDXCCRenderer(format);

	renderer->Render(dxccRecords);

	updateConfigFromClientState();
}

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

void AppController::fetchAndRenderBios(const std::set<std::string> &searchTerms, const AppFormat &format)
{
	std::unique_ptr<render::Renderer<std::string>> renderer = render::RendererFactory::createBioRenderer(format);

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

	renderer->Render(bios);

	updateConfigFromClientState();
}

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

std::string AppController::getUserCallsignFromUser()
{
	std::string userCall;

	std::cout << "Enter your callsign:" << std::endl;

	std::cin >> userCall;

	return userCall;
}

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

void AppController::updateConfigFromClientState()
{
	config.setCallsign(client.getUsername());
	config.setSessionKey(client.getSessionKey());
	config.setSessionExpiration(client.getSessionExpiration());
	config.saveConfig();
}

void AppController::resetFailedCallCount()
{
	m_failedCallCount = 0;
}

inline void AppController::showConsoleCursor(bool const show) {
	std::fputs(show ? "\033[?25h" : "\033[?25l", stderr);
}

#ifdef WIN32
inline void AppController::eraseLine() {
	std::fputs("\x1b[1A", stderr);
	std::fputs("\x1b[2K", stderr);
}

std::unique_ptr<ProgressBar> AppController::buildProgressBar()
{
	return std::make_unique<DefaultProgressBar>();
}
#else
inline void AppController::eraseLine() {
	std::fputs("\r\033[K", stderr);
}

std::unique_ptr<ProgressBar> AppController::buildProgressBar()
{
	return std::make_unique<BlockProgressBar>();
}
#endif
