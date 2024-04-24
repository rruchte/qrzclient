#include "../src/AppController.h"
#include "AppControllerProxy.h"

#include <gtest/gtest.h>
#include <format>
#include <filesystem>

namespace qrz
{
	namespace
	{
		class AppControllerTests : public testing::Test
		{
		protected:
			// You can remove any or all of the following functions if their bodies would
			// be empty.

			AppControllerTests()
			{
			}

			~AppControllerTests() override
			{
			}

			void SetUp() override
			{
				configDirPath = std::filesystem::temp_directory_path().string();
				expectedConfigFilePath = std::format("{:s}/.config/qrz/qrz.cfg", configDirPath);

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
					std::string toRemovePath = std::format("{:s}/.config", configDirPath);
					std::filesystem::remove_all(toRemovePath.c_str());
				}
			}

			std::string timeFormat = "%Y-%m-%d %H:%M:%S";
			std::string configDirPath;
			std::string expectedConfigFilePath;
		};

		TEST_F(AppControllerTests, TestInitializeFromExistingConfiguration)
		{
			// Just make sure this doesn't blow up
			AppController controller;
		}

		TEST_F(AppControllerTests, TestFetchCallsignRecords)
		{
			std::set<std::string> searchTerms;
			searchTerms.insert("W1AW");
			searchTerms.insert("W5YI");

			AppControllerProxy controller;

			std::vector<Callsign> results = controller.proxyFetchCallsignRecords(searchTerms);

			ASSERT_EQ(2, results.size()) << "Two results should have been returned";

			for(const Callsign callsign : results)
			{
				std::string call = callsign.getCall();

				ASSERT_TRUE(searchTerms.contains(call)) << "Results should contain " << call;
			}
		}

		TEST_F(AppControllerTests, TestFetchDXCCRecords)
		{
			std::set<std::string> searchTerms;
			searchTerms.insert("191");
			searchTerms.insert("291");

			AppControllerProxy controller;

			std::vector<DXCC> results = controller.proxyFetchDXCCRecords(searchTerms);

			ASSERT_EQ(2, results.size()) << "Two results should have been returned";

			for(const DXCC dxcc : results)
			{
				std::string dxccId = dxcc.getDxcc();

				ASSERT_TRUE(searchTerms.contains(dxccId)) << "Results should contain " << dxccId;
			}
		}

		TEST_F(AppControllerTests, TestFetchBioRecords)
		{
			std::set<std::string> searchTerms;
			searchTerms.insert("W1AW");
			searchTerms.insert("W5YI");

			AppControllerProxy controller;

			std::vector<std::string> results = controller.proxyFetchBios(searchTerms);

			ASSERT_EQ(2, results.size()) << "Two results should have been returned";

			std::string needle = "QRZXML 1.36 W1AW";
			bool foundNeedle = (results.at(0).find(needle) != std::string::npos);
			ASSERT_TRUE(foundNeedle) << "Expected string should be found in bio HTML";

			needle = "QRZXML 1.36 W5YI";
			foundNeedle = (results.at(1).find(needle) != std::string::npos);
			ASSERT_TRUE(foundNeedle) << "Expected string should be found in bio HTML";
		}
	}
}