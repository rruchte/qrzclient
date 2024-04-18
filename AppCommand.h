#ifndef QRZ_APPCOMMAND_H
#define QRZ_APPCOMMAND_H

#include <set>
#include <string>
#include <vector>

#include "Action.h"
#include "AppFormat.h"

namespace qrz
{
	class AppCommand
	{
	public:
		AppCommand() = default;
		AppCommand(Action mAction, AppFormat mFormat, const std::set<std::string> &mSearchTerm);
		Action getAction() const;
		void setAction(Action action);
		AppFormat getFormat() const;
		void setFormat(AppFormat format);
		const std::set<std::string> &getSearchTerms() const;
		void setSearchTerms(const std::set<std::string> &searchTerms);

	private:
		Action m_action = Action::CALLSIGN_ACTION;
		AppFormat m_format = AppFormat::CONSOLE;
		std::set<std::string> m_searchTerms;
	};
}

#endif //QRZ_APPCOMMAND_H
