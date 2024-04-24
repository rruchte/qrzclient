#ifndef QRZ_APPCONTROLLERPROXY_H
#define QRZ_APPCONTROLLERPROXY_H

#include "../src/AppController.h"

namespace qrz
{
	class AppControllerProxy : public AppController
	{
	public:
		AppControllerProxy() = default;

		std::vector<Callsign> proxyFetchCallsignRecords(const std::set<std::string> &searchTerms)
		{
			return fetchCallsignRecords(searchTerms);
		}

		std::vector<DXCC> proxyFetchDXCCRecords(const std::set<std::string> &searchTerms)
		{
			return fetchDXCCRecords(searchTerms);
		}

		std::vector<std::string> proxyFetchBios(const std::set<std::string> &searchTerms)
		{
			return fetchBios(searchTerms);
		}
	};
}

#endif //QRZ_APPCONTROLLERPROXY_H
