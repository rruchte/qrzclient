#ifndef QRZ_APPCOMMAND_H
#define QRZ_APPCOMMAND_H

#include <set>
#include <string>
#include <vector>

#include "Action.h"
#include "OutputFormat.h"

namespace qrz
{
	class AppCommand
	{
	public:
		AppCommand() = default;
		AppCommand(Action mAction, OutputFormat mFormat, const std::set<std::string> &mSearchTerm);
		Action getAction() const;
		void setAction(Action action);
		OutputFormat getFormat() const;
		void setFormat(OutputFormat format);
		const std::set<std::string> &getSearchTerms() const;
		void setSearchTerms(const std::set<std::string> &searchTerms);

	private:
		Action m_action = Action::CALLSIGN_ACTION;
		OutputFormat m_format = OutputFormat::CONSOLE;
		std::set<std::string> m_searchTerms;
	};
}

#endif //QRZ_APPCOMMAND_H
