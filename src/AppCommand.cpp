#include "AppCommand.h"

using namespace qrz;

AppCommand::AppCommand(Action mAction, OutputFormat mFormat, const std::set<std::string> &mSearchTerms) : m_action(
		mAction), m_format(mFormat), m_searchTerms(mSearchTerms)
{}

Action AppCommand::getAction() const
{
	return m_action;
}

void AppCommand::setAction(Action action)
{
	m_action = action;
}

OutputFormat AppCommand::getFormat() const
{
	return m_format;
}

void AppCommand::setFormat(OutputFormat format)
{
	m_format = format;
}

const std::set<std::string> &AppCommand::getSearchTerms() const
{
	return m_searchTerms;
}

void AppCommand::setSearchTerms(const std::set<std::string> &searchTerms)
{
	m_searchTerms = searchTerms;
}
