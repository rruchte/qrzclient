#include "../src/Configuration.h"

#include <gtest/gtest.h>
#include <format>
#include <filesystem>

namespace qrz
{
	namespace
	{
		class ConfigurationTests : public testing::Test
		{
		protected:
			// You can remove any or all of the following functions if their bodies would
			// be empty.

			ConfigurationTests()
			{
			}

			~ConfigurationTests() override
			{
			}

			void SetUp() override
			{
				configDirPath = std::filesystem::temp_directory_path().string();

#ifdef WIN32
				expectedConfigFilePath = std::format("{:s}\\.config\\qrz\\qrz.cfg", configDirPath);
#else
				expectedConfigFilePath = std::format("{:s}/.config/qrz/qrz.cfg", configDirPath);
#endif


				removeConfigTree();
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
					std::string toRemovePath = std::format("{:s}\\.config", configDirPath);
#else
					std::string toRemovePath = std::format("{:s}/.config", configDirPath);
#endif

					std::filesystem::remove_all(toRemovePath.c_str());
				}
			}

			std::string configDirPath;
			std::string expectedConfigFilePath;
		};

		TEST_F(ConfigurationTests, TestPersist)
		{
			auto inputConfig = Configuration(configDirPath);

			std::string expectedCallsign = "W1AW";
			std::string expectedPassword = "wh15ky7@n60F0x7r07";
			std::string expectedSessionKey = "c992efd9432fbc4972b36432f822be64";
			std::string expectedSessionExpiration = "2024-04-24 05:35:45";

			inputConfig.setCallsign(expectedCallsign);
			inputConfig.setPassword(expectedPassword);
			inputConfig.setSessionKey(expectedSessionKey);
			inputConfig.setSessionExpiration(expectedSessionExpiration);

			inputConfig.saveConfig();

			bool configFileExists = std::filesystem::exists(expectedConfigFilePath);

			ASSERT_TRUE(configFileExists) << "Config file should be written to disk in the expected location: "
										  << expectedConfigFilePath;

			auto testConfig = Configuration(configDirPath);

			ASSERT_EQ(expectedCallsign, testConfig.getCallsign());
			ASSERT_EQ(expectedPassword, testConfig.getPassword());
			ASSERT_EQ(expectedSessionKey, testConfig.getSessionKey());
			ASSERT_EQ(expectedSessionExpiration, testConfig.getSessionExpiration());
		}
	}
}