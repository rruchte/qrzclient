#include "../src/AppCommand.h"
#include <gtest/gtest.h>

namespace qrz
{
	namespace
	{
		TEST(AppCommandTests, TestDefaultConstructor)
		{
			Action expectedAction = Action::CALLSIGN_ACTION;
			OutputFormat expectedFormat = OutputFormat::CONSOLE;
			std::set<std::string> expectedTerms = {};

			AppCommand cmd = AppCommand();

			ASSERT_EQ(expectedAction, cmd.getAction());
			ASSERT_EQ(expectedFormat, cmd.getFormat());
			ASSERT_EQ(expectedTerms, cmd.getSearchTerms());
		}

		TEST(AppCommandTests, TestConstructorArgs)
		{
			Action expectedAction = Action::DXCC_ACTION;
			OutputFormat expectedFormat = OutputFormat::XML;
			std::set<std::string> expectedTerms = {"K4RWR", "W1AW"};

			AppCommand cmd = AppCommand(expectedAction, expectedFormat, expectedTerms);

			ASSERT_EQ(expectedAction, cmd.getAction());
			ASSERT_EQ(expectedFormat, cmd.getFormat());
			ASSERT_EQ(expectedTerms, cmd.getSearchTerms());
		}

		TEST(AppCommandTests, TestGetSet)
		{
			Action expectedAction = Action::DXCC_ACTION;
			OutputFormat expectedFormat = OutputFormat::XML;
			std::set<std::string> expectedTerms = {"K4RWR", "W1AW"};

			AppCommand cmd = AppCommand();
			cmd.setAction(expectedAction);
			cmd.setFormat(expectedFormat);
			cmd.setSearchTerms(expectedTerms);

			ASSERT_EQ(expectedAction, cmd.getAction());
			ASSERT_EQ(expectedFormat, cmd.getFormat());
			ASSERT_EQ(expectedTerms, cmd.getSearchTerms());
		}
	}
}