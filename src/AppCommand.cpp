#include "AppCommand.h"

using namespace qrz;

/**
 * @class AppCommand
 * @brief Represents a command to be executed by the AppController
 *
 * This class stores information about an action, output format, and search terms for a command to be executed by
 * the AppController.
 */
AppCommand::AppCommand(Action mAction, OutputFormat mFormat, const std::set<std::string> &mSearchTerms) : m_action(
		mAction), m_format(mFormat), m_searchTerms(mSearchTerms)
{}

/**
 * @brief Get the action of the command.
 *
 * This function returns the action associated with the command.
 * The action determines the type of operation to be performed.
 *
 * @return The action of the command.
 */
Action AppCommand::getAction() const
{
	return m_action;
}

/**
 * @brief Set the action of the command.
 *
 * This function sets the action associated with the command.
 * The action determines the type of operation to be performed.
 *
 * @param action The action to set for the command.
 */
void AppCommand::setAction(Action action)
{
	m_action = action;
}

/**
 * @brief Get the output format associated with the command.
 *
 * This function returns the output format associated with the command.
 * The output format determines how the result of the command will be formatted.
 *
 * @return The output format of the command.
 */
OutputFormat AppCommand::getFormat() const
{
	return m_format;
}

/**
 * @brief Set the output format for the command.
 *
 * This function sets the output format for the command. The output format determines how the result of the
 * command will be formatted.
 *
 * @param format The output format to set for the command.
 */
void AppCommand::setFormat(OutputFormat format)
{
	m_format = format;
}

/**
 * @brief Get the search terms associated with the command.
 *
 * This function returns a constant reference to the set of search terms associated with the command.
 * The search terms are sent to the QRZ API to return the relevant records.
 *
 * @return A constant reference to the set of search terms.
 */
const std::set<std::string> &AppCommand::getSearchTerms() const
{
	return m_searchTerms;
}

/**
 * @brief Set the search terms for the command.
 *
 * This function sets the search terms associated with the command. The search terms are sent to the QRZ API to return
 * the relevant records.
 *
 * @param searchTerms The search terms to set for the command.
 */
void AppCommand::setSearchTerms(const std::set<std::string> &searchTerms)
{
	m_searchTerms = searchTerms;
}
