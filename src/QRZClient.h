#ifndef QRZ_QRZCLIENT_H
#define QRZ_QRZCLIENT_H

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeParser.h>
#include <Poco/Exception.h>
#include <Poco/LocalDateTime.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/NameValueCollection.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/SAX/SAXException.h>

#include "exception/AuthenticationException.h"
#include "model/Callsign.h"
#include "model/CallsignMarshaler.h"
#include "model/DXCC.h"
#include "model/DXCCMarshaler.h"

namespace qrz
{
	/**
	 * @class QrzResponse
	 *
	 * @brief The QrzResponse class represents the response received from a QRZ API request.
	 *
	 * It contains the POCO HTTP response object and the body of the response.
	 */
	class QrzResponse
	{
		public:
		QrzResponse() = default;
		QrzResponse(const Poco::Net::HTTPResponse &mHttpResponse,
					const std::string &mBody) : m_httpResponse(mHttpResponse), m_body(mBody)
		{}

		const std::string &getBody()
		{
			return m_body;
		}

		void setBody(const std::string &mBody)
		{
			m_body = mBody;
		}

		const Poco::Net::HTTPResponse &getHttpResponse()
		{
			return m_httpResponse;
		}

		void setHttpResponse(const Poco::Net::HTTPResponse &mHttpResponse)
		{
			m_httpResponse = mHttpResponse;
		}

	private:
			std::string m_body;
			Poco::Net::HTTPResponse m_httpResponse;
	};

	/**
	 * @brief The QRZClient class is responsible for making requests to the QRZ API and processing the responses.
	 *
	 * The QRZClient class provides methods for fetching callsign information, biography information, and DXCC information for a given query.
	 * It also provides a method for fetching a session token for authentication with the API.
	 */
	class QRZClient
	{
	public:
		QRZClient() = default;

		/**
		 * @brief Constructs a QRZClient object with the provided configuration.
		 *
		 * This constructor initializes a QRZClient object with the specified configuration. The configuration includes
		 * the callsign, password, session key, and session expiration.
		 *
		 * @param config A reference to the Configuration object containing the configuration settings.
		 */
		explicit QRZClient(Configuration &config)
		{
			setUsername(config.getCallsign());
			setPassword(config.getPassword());
			setSessionKey(config.getSessionKey());
			setSessionExpiration(config.getSessionExpiration());
		}

		/**
		 * @brief Constructs a QRZClient object with the provided username, password, session key, and session
		 * expiration.
		 *
		 * This constructor initializes a QRZClient object with the specified username, password, session key, and
		 * session expiration.
		 *
		 * @param username The username used for authentication.
		 * @param password The password used for authentication.
		 * @param sessionKey The session key.
		 * @param sessionExpiration The session expiration date and time in the format specified by m_timeFormat.
		 */
		QRZClient(const std::string &username, const std::string &password, const std::string &sessionKey,
				  const std::string &sessionExpiration) : m_username(username), m_password(password),
														  m_sessionKey(sessionKey)

		{
			setSessionExpiration(sessionExpiration);
		}

		/**
		 * @brief Get the username currently used for authentication with the QRZ API.
		 *
		 * This method returns the username that is currently used for authentication with the QRZ API.
		 *
		 * @return A constant reference to a string representing the username.
		 */
		const std::string &getUsername() const
		{
			return m_username;
		}

		/**
		* @brief Sets the username used for authentication.
		*
		* This method sets the username that is used for authentication with the QRZ API.
		* The username is required for making requests to the API.
		*
		* @param username A constant reference to a string representing the username.
		*/
		void setUsername(const std::string &username)
		{
			m_username = username;
		}

		/**
		 * @brief Get the password currently used for authentication with the QRZ API.
		 *
		 * This method returns the password that is currently used for authentication with the QRZ API.
		 *
		 * @return A constant reference to a string representing the password.
		 */
		const std::string &getPassword() const
		{
			return m_password;
		}

		/**
		 * @brief Sets the password used for authentication.
		 *
		 * This method sets the password that is used for authentication with the QRZ API.
		 * The password is required for making requests to the API.
		 *
		 * @param password A constant reference to a string representing the password.
		 */
		void setPassword(const std::string &password)
		{
			m_password = password;
		}

		/**
		 * @brief Get the session key currently used for authentication with the QRZ API.
		 *
		 * This method returns the session key that is currently used for authentication with the QRZ API.
		 *
		 * @return A constant reference to a string representing the session key.
		 */
		const std::string &getSessionKey() const
		{
			return m_sessionKey;
		}

		/**
		 * @brief Sets the session key used for authentication with the QRZ API.
		 *
		 * This method sets the session key that is used for authentication with the QRZ API.
		 * The session key is required for making requests to the API.
		 *
		 * @param sessionKey A constant reference to a string representing the session key.
		 */
		void setSessionKey(const std::string &sessionKey)
		{
			m_sessionKey = sessionKey;
		}

		/**
		 * @brief Get the session expiration date and time in the format specified by m_timeFormat.
		 *
		 * This method returns the session expiration date and time as a string in YYYY-mm-DD HH:MM:SS format.
		 *
		 * @return A string representing the session expiration date and time.
		 */
		const std::string getSessionExpiration() const
		{
			Poco::DateTime dt(m_sessionTimestamp);
			return Poco::DateTimeFormatter::format(dt, m_timeFormat);
		}

		/**
		 * @brief Sets the session expiration date and time based on the provided sessionExpiration.
		 *
		 * This method parses the sessionExpiration string using the YYYY-mm-DD HH:MM:SS format and sets the session
		 * expiration timestamp based on the parsed datetime object. The session expiration timestamp is the number of
		 * microseconds since 1970-01-01 00:00:00 UTC.
		 *
		 * @param sessionExpiration A constant reference to a string representing the session expiration date and time.
		 */
		void setSessionExpiration(const std::string &sessionExpiration)
		{
			int tzd = 0;
			Poco::DateTime dt;
			Poco::DateTimeParser::parse(m_timeFormat, sessionExpiration, dt, tzd);
			m_sessionTimestamp = dt.timestamp();
		}

		/**
		 * @brief Sends a request to the QRZ API and returns the response.
		 *
		 * This method sends a request to the QRZ API with the specified URI and returns the response as a QrzResponse
		 * object.
		 *
		 * @param uri The URI of the API endpoint to send the request to.
		 * @return A QrzResponse object containing the HTTP response and body.
		 */
		virtual QrzResponse sendRequest(Poco::URI &uri)
		{
			std::string path = Poco::format("/xml/%s/", m_apiVersion);
			uri.setPath(path);
			uri.addQueryParameter("agent", m_userAgent);

			// Create a session
			const Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), ptrContext);

			// Prepare a GET request
			Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.toString());

			// Send Request
			session.sendRequest(request);

			// Get the response
			Poco::Net::HTTPResponse response;

			std::istream& rs = session.receiveResponse(response);
			std::string body;
			Poco::StreamCopier::copyToString(rs, body);

			// Check HTTP response status
			if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK)
			{
				std::cerr << "HTTP error: " << response.getStatus() << ' ' << response.getReason() << std::endl;
			}

			QrzResponse output{response, body};

			return output;
		}

		/**
		 * @brief Fetches a Callsign object for a given callsign string.
		 *
		 * This function fetches the callsign information for a given callsign by making a request to the QRZ API.
		 * If the session key is not valid, it fetches a new token before making the request.
		 * If the response status is not HTTP_OK, it prints the HTTP error message to standard error output.
		 * If any Poco exception occurs during the process, it prints the Poco error message to standard error output.
		 *
		 * @param call The callsign to fetch information for.
		 * @return The Callsign object containing the fetched callsign information.
		 */
		Callsign fetchCallsign(const std::string call)
		{
			Callsign callsign;
			callsign.setCall(call);

			if (!tokenIsValid())
			{
				fetchToken();
			}

			try
			{
				Poco::URI uri(m_baseUrl);

				uri.addQueryParameter("callsign", call);
				uri.addQueryParameter("s", m_sessionKey);

				QrzResponse response = sendRequest(uri);
				const Poco::Net::HTTPResponse &httpResponse = response.getHttpResponse();

				if (httpResponse.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
				{
					validateResponse(response.getBody());

					CallsignMarshaler marshaler;
					callsign = marshaler.FromXml(response.getBody());
				}
				else
				{
					std::cerr << "HTTP error: " << httpResponse.getReason() << std::endl;
				}
			}
			catch (Poco::Exception& ex)
			{
				std::cerr << "Poco error: " << ex.displayText() << std::endl;
			}

			return callsign;
		}

		/**
		 * @brief Fetches the biography information for a given callsign.
		 *
		 * This method fetches the biography information for the specified callsign by making a request to the QRZ API.
		 * If the session key is not valid, it fetches a new token before making the request.
		 * If the response status is not HTTP_OK, it prints an HTTP error message to standard error output.
		 * If any Poco exception occurs during the process, it prints a Poco error message to standard error output.
		 *
		 * @param call The callsign for which to fetch the biography information.
		 * @return A string containing the fetched biography information.
		 */
		std::string fetchBio(const std::string call)
		{
			if (!tokenIsValid())
			{
				fetchToken();
			}

			std::string output;

			try
			{
				Poco::URI uri(m_baseUrl);

				uri.addQueryParameter("html", call);
				uri.addQueryParameter("s", m_sessionKey);

				QrzResponse response = sendRequest(uri);
				const Poco::Net::HTTPResponse &httpResponse = response.getHttpResponse();

				if (httpResponse.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
				{
					output = response.getBody();
				}
				else
				{
					std::cerr << "HTTP error: " << httpResponse.getReason() << std::endl;
				}
			}
			catch (Poco::Exception& ex)
			{
				std::cerr << "Poco error: " << ex.displayText() << std::endl;
			}

			return output;
		}

		/**
		 * @brief Fetches the DXCC information for a given query string.
		 *
		 * This function fetches the DXCC information for the specified query by making a request to the QRZ API.
		 * If the session key is not valid, it fetches a new token before making the request.
		 * If the response status is not HTTP_OK, it prints an HTTP error message to standard error output.
		 * If any Poco exception occurs during the process, it prints a Poco error message to standard error output.
		 *
		 * @param query The query string for which to fetch the DXCC information.
		 * @return The DXCC object containing the fetched DXCC information if successful, otherwise an empty DXCC object.
		 */
		DXCC fetchDXCC(const std::string query)
		{
			DXCC dxcc;

			if (!tokenIsValid())
			{
				fetchToken();
			}

			try
			{
				Poco::URI uri(m_baseUrl);

				uri.addQueryParameter("dxcc", query);
				uri.addQueryParameter("s", m_sessionKey);

				QrzResponse response = sendRequest(uri);
				const Poco::Net::HTTPResponse &httpResponse = response.getHttpResponse();

				if (httpResponse.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
				{
					validateResponse(response.getBody());

					DXCCMarshaler marshaler;
					dxcc = marshaler.FromXml(response.getBody());
				}
				else
				{
					std::cerr << "HTTP error: " << httpResponse.getReason() << std::endl;
				}
			}
			catch (Poco::Exception& ex)
			{
				std::cerr << "Poco error: " << ex.displayText() << std::endl;
			}

			return dxcc;
		}

		/**
		 * @brief Fetches a token from a QRZ API.
		 *
		 * This function sends a request to the QRZ API to fetch a token. The token is used for authentication to access
		 * the API's resources. The token is obtained by sending a POST request to the API's endpoint with the username and password
		 * as query parameters. If the request is successful, the function parses the response to extract the token, and sets the
		 * session key with the obtained token. The function also sets the session timeout to the current time plus 24 hours.
		 *
		 * @note The function uses the Poco library for sending HTTP requests and parsing XML responses.
		 *
		 * @throws std::runtime_error If an invalid XML response is received from the QRZ API.
		 *
		 * @throws Poco::XML::SAXException If an error occurs during XML parsing.
		 *
		 * @throws Poco::Net::HTTPException If an error occurs during the HTTP request.
		 */
		void fetchToken()
		{
			Poco::URI uri(m_baseUrl);

			uri.addQueryParameter("username", m_username);
			uri.addQueryParameter("password", m_password);

			QrzResponse response = sendRequest(uri);
			const Poco::Net::HTTPResponse &httpResponse = response.getHttpResponse();

			if (httpResponse.getStatus() == Poco::Net::HTTPResponse::HTTP_OK)
			{
				bool validToken = false;

				try
				{
					Poco::XML::DOMParser parser;
					Poco::AutoPtr<Poco::XML::Document> doc = parser.parseString(response.getBody());
					Poco::XML::Element* rootElement = doc->documentElement();

					if (rootElement->tagName() != "QRZDatabase")
					{
						throw std::runtime_error("Invalid XML");
					}

					Poco::XML::NodeList* sessionElements = rootElement->getElementsByTagName("Session");
					if (sessionElements->length() == 0)
					{
						throw std::runtime_error("Invalid XML");
					}

					Poco::XML::Element* sessionElement = static_cast<Poco::XML::Element*>(sessionElements->item(0));
					Poco::XML::Node* currChild = sessionElement->firstChild();

					while (currChild)
					{
						if (currChild->nodeType() == Poco::XML::Node::ELEMENT_NODE)
						{
							Poco::XML::Element* currentElement = static_cast<Poco::XML::Element*>(currChild);
							std::string name = currentElement->nodeName();
							std::string value = currentElement->innerText();
							if (name == "Key")
							{
								setSessionKey(value);
								validToken = true;
							}
						}

						currChild = currChild->nextSibling();
					}
				}
				catch (const Poco::XML::SAXException &e)
				{
					std::cerr << e.what() << std::endl;
				}

				if(validToken)
				{
					Poco::Timestamp now;

					now += std::chrono::hours(24);

					m_sessionTimestamp = now;
				}
			}
			else
			{
				std::cerr << "HTTP error: " << httpResponse.getReason() << std::endl;
			}
		}

		/**
		 * @brief Checks if the token is valid.
		 *
		 * This function checks if the session timestamp is greater than the current timestamp.
		 * If it is, then the token is valid, otherwise it is not.
		 *
		 * @return True if the token is valid, false otherwise.
		 */
		bool tokenIsValid()
		{
			Poco::Timestamp now;

			return (m_sessionTimestamp > now);
		}

	protected:
		// Time format used by the QRZ API
		static inline const std::string m_timeFormat = "%Y-%m-%d %H:%M:%S";

		// User agent string sent to the QRZ API
		static inline const std::string m_userAgent = "qrzclnt1.0";

		// Base URL of the QRZ API
		static inline const std::string m_baseUrl = "https://xmldata.qrz.com";

		// Version of the QRZ API to call
		static inline const std::string m_apiVersion = "current";

		// Username (user callsign) used for API authentication
		std::string m_username;

		// QRZ password used for API authentication
		std::string m_password;

		// Session key returned from the QRZ token API endpoint, used for all other API calls
		std::string m_sessionKey;

		// Expiration time for the session token. Estimated to be 24 hours
		Poco::Timestamp m_sessionTimestamp;

		/**
		 * @brief This function validates the response from the QRZDatabase API.
		 *
		 * Parse the response body as XML and perform various checks to ensure the response is valid.
		 *
		 * @param responseBody The response body returned by the API.
		 * @throws std::runtime_error if the XML response is invalid, the session element is not found,
		 *         or an error element is found with either "Session Timeout" or "Invalid session key" text.
		 */
		static void validateResponse(const std::string &responseBody)
		{
			try
			{
				Poco::XML::DOMParser parser;
				Poco::AutoPtr<Poco::XML::Document> doc = parser.parseString(responseBody);

				auto *rootElement = doc->documentElement();
				if (rootElement == nullptr || rootElement->nodeName() != "QRZDatabase")
				{
					throw std::runtime_error("Invalid XML Response");
				}

				auto *sessionElement = rootElement->getChildElement("Session");
				if (sessionElement == nullptr)
				{
					throw std::runtime_error("Session element not found");
				}

				auto *errorElement = sessionElement->getChildElement("Error");
				if (errorElement != nullptr)
				{
					std::string errorText = errorElement->innerText();

					if (errorText == "Session Timeout" || errorText == "Invalid session key")
					{
						throw AuthenticationException{errorText};
					}
					else
					{
						throw std::runtime_error{errorText};
					}
				}
			}
			catch (Poco::Exception& ex)
			{
				throw std::runtime_error{ex.message()};
			}
		}
	};
}

#endif //QRZ_QRZCLIENT_H
