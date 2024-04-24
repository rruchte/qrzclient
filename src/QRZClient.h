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

	class QRZClient
	{
	public:
		QRZClient() = default;

		explicit QRZClient(Configuration &config)
		{
			setUsername(config.getCallsign());
			setPassword(config.getPassword());
			setSessionKey(config.getSessionKey());
			setSessionExpiration(config.getSessionExpiration());
		}

		QRZClient(const std::string &username, const std::string &password, const std::string &sessionKey,
				  const std::string &sessionExpiration) : m_username(username), m_password(password),
														  m_sessionKey(sessionKey)

		{
			setSessionExpiration(sessionExpiration);
		}

		const std::string &getUsername() const
		{
			return m_username;
		}

		void setUsername(const std::string &username)
		{
			m_username = username;
		}

		const std::string &getPassword() const
		{
			return m_password;
		}

		void setPassword(const std::string &password)
		{
			m_password = password;
		}

		const std::string &getSessionKey() const
		{
			return m_sessionKey;
		}

		void setSessionKey(const std::string &sessionKey)
		{
			m_sessionKey = sessionKey;
		}

		const std::string getSessionExpiration() const
		{
			Poco::DateTime dt(m_sessionTimestamp);
			return Poco::DateTimeFormatter::format(dt, m_timeFormat);
		}

		void setSessionExpiration(const std::string &sessionExpiration)
		{
			int tzd = 0;
			Poco::DateTime dt;
			Poco::DateTimeParser::parse(m_timeFormat, sessionExpiration, dt, tzd);
			m_sessionTimestamp = dt.timestamp();
		}

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

		bool tokenIsValid()
		{
			Poco::Timestamp now;

			return (m_sessionTimestamp > now);
		}

	protected:
		static inline const std::string m_timeFormat = "%Y-%m-%d %H:%M:%S";
		static inline const std::string m_userAgent = "qrzclnt1.0";
		static inline const std::string m_baseUrl = "https://xmldata.qrz.com";
		static inline const std::string m_apiVersion = "current";

		std::string m_username;
		std::string m_password;
		std::string m_sessionKey;
		Poco::Timestamp m_sessionTimestamp;

		void validateResponse(const std::string &responseBody)
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
