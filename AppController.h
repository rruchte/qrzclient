#ifndef QRZ_APPCONTROLLER_H
#define QRZ_APPCONTROLLER_H

#include <string>

#include "AppCommand.h"
#include "AppFormat.h"
#include "Configuration.h"
#include "QRZClient.h"
#include "Util.h"
#include "model/Callsign.h"
#include "model/DXCC.h"
#include "render/CallsignConsoleRenderer.h"
#include "render/CallsignXMLRenderer.h"
#include "render/CallsignMarkdownRenderer.h"
#include "render/Renderer.h"

namespace qrz
{
	class AppController
	{
	public:
		AppController();
		void handleCommand(const AppCommand &command);

	private:
		Configuration config;
		QRZClient client;

		int m_failedCallCount = 0;
		const int m_maxFailedCallCount = 4;
		bool displayProgress = false;

		void initialize();
		void fetchAndRenderCallsigns(const std::set<std::string> &searchTerms, const AppFormat &format);
		void fetchAndRenderBios(const std::set<std::string> &searchTerms, const AppFormat &format);
		void fetchAndRenderDXCC(const std::set<std::string> &searchTerms, const AppFormat &format);
		std::vector<Callsign> fetchCallsignRecords(const std::set<std::string> &searchTerms);
		std::vector<DXCC> fetchDXCCRecords(const std::set<std::string> &searchTerms);
		void refreshToken();
		static std::string getUserCallsignFromUser();
		std::string getPasswordFromUser();
		void resetFailedCallCount();
		void updateConfigFromClientState();
		void showConsoleCursor(const bool show);
		static void eraseLine();
	};
}

#endif //QRZ_APPCONTROLLER_H