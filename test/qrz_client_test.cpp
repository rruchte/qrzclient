#include "../src/AppController.h"

#include <gtest/gtest.h>
#include <format>
#include <filesystem>

#include "MockClient.h"

namespace qrz
{
	namespace
	{
		class QrzClientTests : public testing::Test
		{
		protected:
			// You can remove any or all of the following functions if their bodies would
			// be empty.

			QrzClientTests()
			{
			}

			~QrzClientTests() override
			{
			}

			void SetUp() override
			{
				configDirPath = std::filesystem::temp_directory_path().string();

#ifdef WIN32
				expectedConfigFilePath = std::format("{:s}.qrz\\qrz.cfg", configDirPath);
#else
				expectedConfigFilePath = std::format("{:s}/.config/qrz/qrz.cfg", configDirPath);
#endif

				removeConfigTree();

				auto config = Configuration(configDirPath);

				// Create a timestamp 24 hours in the future to ensure a valid session expiration
				std::chrono::time_point sessionExpTime = std::chrono::system_clock::now();

				sessionExpTime += std::chrono::hours(24);

				auto time_t_format = std::chrono::system_clock::to_time_t(
						sessionExpTime
				);

				std::ostringstream oss;
				oss << std::put_time(std::localtime(&time_t_format), timeFormat.c_str());

				std::string expectedSessionExpiration = oss.str();

				std::string expectedCallsign = "W1AW";
				std::string expectedPassword = "wh15ky7@n60F0x7r07";
				std::string expectedSessionKey = "c992efd9432fbc4972b36432f822be64";

				config.setCallsign(expectedCallsign);
				config.setPassword(expectedPassword);
				config.setSessionKey(expectedSessionKey);
				config.setSessionExpiration(expectedSessionExpiration);

				config.saveConfig();

				client = MockClient(config);
			}

			void TearDown() override
			{
				removeConfigTree();
			}

			void removeConfigTree()
			{
				bool configFileExists = std::filesystem::exists(expectedConfigFilePath);

				if (configFileExists)
				{
#ifdef WIN32
					std::string toRemovePath = std::format("{:s}.qrz", configDirPath);
#else
					std::string toRemovePath = std::format("{:s}/.config", configDirPath);
#endif

					std::filesystem::remove_all(toRemovePath.c_str());
				}
			}

			// Create a timestamp 48 hours in the past to test an expired session
			std::string generateExpiredSessionExpiration()
			{
				std::chrono::time_point sessionExpTime = std::chrono::system_clock::now();

				sessionExpTime -= std::chrono::hours(48);

				auto time_t_format = std::chrono::system_clock::to_time_t(
						sessionExpTime
				);

				std::ostringstream oss;
				oss << std::put_time(std::localtime(&time_t_format), timeFormat.c_str());

				return oss.str();
			}

			// Create a timestamp 48 hours in the future to test an expired session
			std::string generateFutureSessionExpiration()
			{
				std::chrono::time_point sessionExpTime = std::chrono::system_clock::now();

				sessionExpTime += std::chrono::hours(48);

				auto time_t_format = std::chrono::system_clock::to_time_t(
						sessionExpTime
				);

				std::ostringstream oss;
				oss << std::put_time(std::localtime(&time_t_format), timeFormat.c_str());

				return oss.str();
			}

			std::string timeFormat = "%Y-%m-%d %H:%M:%S";
			std::string configDirPath;
			std::string expectedConfigFilePath;

			MockClient client;

			std::string invalidSessionResponseMissingSession=R"sessionXML(
<QRZDatabase version="1.34">
</QRZDatabase>
)sessionXML";

			std::string invalidSessionResponseTimeout=R"sessionXML(
<QRZDatabase version="1.34">
  <Session>
    <Error>Session Timeout</Error>
    <Count>123</Count>
    <SubExp>Wed Jan 1 12:34:03 2013</SubExp>
    <GMTime>Sun Aug 16 03:51:47 2012</GMTime>
  </Session>
</QRZDatabase>
)sessionXML";

			std::string invalidSessionResponseBadKey=R"sessionXML(
<QRZDatabase version="1.34">
  <Session>
    <Error>Invalid session key</Error>
    <Count>123</Count>
    <SubExp>Wed Jan 1 12:34:03 2013</SubExp>
    <GMTime>Sun Aug 16 03:51:47 2012</GMTime>
  </Session>
</QRZDatabase>
)sessionXML";
		};

		TEST_F(QrzClientTests, TestGetTokenExpiration)
		{
			std::string expiredSessionTime = generateExpiredSessionExpiration();

			client.setSessionExpiration(expiredSessionTime);

			std::string testSessionExpiration = client.getSessionExpiration();

			ASSERT_STREQ(expiredSessionTime.c_str(), testSessionExpiration.c_str()) << "Generated expiration timestamp should match timestamp from client";
		}


		TEST_F(QrzClientTests, TestTokenIsValidFalse)
		{
			std::string expiredSessionTime = generateExpiredSessionExpiration();

			client.setSessionExpiration(expiredSessionTime);

			bool tokenIsValid = client.tokenIsValid();

			ASSERT_FALSE(tokenIsValid) << "Expired session time should be recognized";
		}

		TEST_F(QrzClientTests, TestTokenIsValidTrue)
		{
			std::string futureSessionTime = generateFutureSessionExpiration();

			client.setSessionExpiration(futureSessionTime);

			bool tokenIsValid = client.tokenIsValid();

			ASSERT_TRUE(tokenIsValid) << "Future session time should be recognized";
		}

		TEST_F(QrzClientTests, TestFetchToken)
		{
			client.fetchToken();

			const char *expectedSessionKey = "2331uf894c4bd29f3923f3bacf02c532d7bd9";

			ASSERT_STREQ(expectedSessionKey, client.getSessionKey().c_str()) << "Session key should be " << expectedSessionKey;
		}

		TEST_F(QrzClientTests, TestFetchCallsign)
		{
			Callsign testCallsign = client.fetchCallsign("W1AW");

			const char *expectedCall = "W1AW";
			const char *expectedName = "ARRL HQ OPERATORS CLUB";
			const char *expectedEmail = "W1AW@ARRL.ORG";

			ASSERT_STREQ(expectedCall, testCallsign.getCall().c_str()) << "Call should be " << expectedCall;
			ASSERT_STREQ(expectedName, testCallsign.getName().c_str()) << "Name should be " << expectedName;
			ASSERT_STREQ(expectedEmail, testCallsign.getEmail().c_str()) << "Email should be " << expectedEmail;
		}

		TEST_F(QrzClientTests, TestFetchDXCC)
		{
			DXCC testDXCC = client.fetchDXCC("291");

			const char *expectedDxcc = "291";
			const char *expectedCc = "USA";
			const char *expectedName = "United States";

			ASSERT_STREQ(expectedDxcc, testDXCC.getDxcc().c_str()) << "DXCC should be " << expectedDxcc;
			ASSERT_STREQ(expectedCc, testDXCC.getCc().c_str()) << "CC should be " << expectedCc;
			ASSERT_STREQ(expectedName, testDXCC.getName().c_str()) << "Name should be " << expectedName;
		}

		TEST_F(QrzClientTests, TestFetchBio)
		{
			std::string testBio = client.fetchBio("W1AW");
			std::string url = "http://www.arrl.org/w1aw";

			bool foundUrl = (testBio.find(url) != std::string::npos);

			ASSERT_TRUE(foundUrl) << "Expected URL should be found in bio HTML";
		}

		TEST_F(QrzClientTests, TestValidateResponseGoodResponse)
		{
			bool valid = client.testValidateResponse(client.sessionResponse);

			ASSERT_TRUE(valid) << "Expected pass when good response processed";
		}

		TEST_F(QrzClientTests, TestValidateResponseMissingSession)
		{
			bool valid = client.testValidateResponse(invalidSessionResponseMissingSession);

			ASSERT_FALSE(valid) << "Expected exception when session element missing";
		}

		TEST_F(QrzClientTests, TestValidateResponseTimeout)
		{
			bool valid = client.testValidateResponse(invalidSessionResponseTimeout);

			ASSERT_FALSE(valid) << "Expected exception when session timeout error present";
		}

		TEST_F(QrzClientTests, TestValidateResponseBadKey)
		{
			bool valid = client.testValidateResponse(invalidSessionResponseBadKey);

			ASSERT_FALSE(valid) << "Expected exception when session invalid key error present";
		}
	}
}