#include <iostream>

#include <argparse/argparse.hpp>

#include "Action.h"
#include "AppController.h"
#include "OutputFormat.h"
#include "Util.h"

using namespace qrz;

int main(int argc, char **argv)
{
	argparse::ArgumentParser program("qrz");

	program.add_argument("search")
			.help("Callsign or DXCC ID to fetch details for.")
			.remaining();

	program.add_argument("-a", "--action")
			.default_value("callsign")
			.help("Specify the action to perform. callsign[default]|bio|dxcc|login");

	program.add_argument("-f", "--format")
			.default_value("console")
			.help("Specify the output format. Console[default]|CSV|JSON|XML|MD");

	try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::exception &err)
	{
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return 1;
	}

	AppController controller;

	AppCommand command;

	std::string action = program.get<std::string>("-a");
	std::string format = program.get<std::string>("-f");

	qrz::ToUpper(action);
	qrz::ToUpper(format);

	bool searchInputRequired = true;
	if(action.empty() || action == "CALLSIGN")
	{
		command.setAction(Action::CALLSIGN_ACTION);
	}
	else if(action == "BIO")
	{
		command.setAction(Action::BIO_ACTION);
	}
	else if(action == "DXCC")
	{
		command.setAction(Action::DXCC_ACTION);
	}
	else if(action == "LOGIN")
	{
		searchInputRequired = false;
		command.setAction(Action::RESET_LOGIN_ACTION);
	}

	if(format.empty() || format == "CONSOLE")
	{
		command.setFormat(OutputFormat::CONSOLE);
	}
	else if(format == "CSV")
	{
		command.setFormat(OutputFormat::CSV);
	}
	else if(format == "JSON")
	{
		command.setFormat(OutputFormat::JSON);
	}
	else if(format == "XML")
	{
		command.setFormat(OutputFormat::XML);
	}
	else if(format == "MD")
	{
		command.setFormat(OutputFormat::MD);
	}

	// Handle search input, is necessary
	if(searchInputRequired)
	{
		// If we have no input, print help and exit
		if(!program.is_used("search"))
		{
			std::cout << program << std::endl;
			return 1;
		}

		auto rawSearchList = program.get<std::vector<std::string>>("search");

		// Convert the vector to a set, we do not want duplicates
		std::set<std::string> searchList(rawSearchList.begin(), rawSearchList.end());

		command.setSearchTerms(searchList);
	}

	controller.handleCommand(command);

	return 0;
}


