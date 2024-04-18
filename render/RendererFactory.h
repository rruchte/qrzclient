#ifndef QRZ_RENDERERFACTORY_H
#define QRZ_RENDERERFACTORY_H

#include "../AppFormat.h"
#include "../model/Callsign.h"
#include "../model/DXCC.h"
#include "BioRenderer.h"
#include "CallsignConsoleRenderer.h"
#include "CallsignCSVRenderer.h"
#include "CallsignJSONRenderer.h"
#include "CallsignMarkdownRenderer.h"
#include "CallsignXMLRenderer.h"
#include "DXCCConsoleRenderer.h"
#include "DXCCCSVRenderer.h"
#include "DXCCJSONRenderer.h"
#include "DXCCMarkdownRenderer.h"
#include "DXCCXMLRenderer.h"
#include "Renderer.h"

namespace qrz::render
{
	class RendererFactory
	{
	public:
		static std::unique_ptr<Renderer<Callsign>> createCallsignRenderer(AppFormat format)
		{
			switch (format)
			{
				case AppFormat::CONSOLE:
					return std::make_unique<CallsignConsoleRenderer>();
				case AppFormat::CSV:
					return std::make_unique<CallsignCSVRenderer>();
				case AppFormat::JSON:
					return std::make_unique<CallsignJSONRenderer>();
				case AppFormat::XML:
					return std::make_unique<CallsignXMLRenderer>();
				case AppFormat::MD:
					return std::make_unique<CallsignMarkdownRenderer>();
				default:
					throw std::invalid_argument("Invalid Format");
			}
		}

		static std::unique_ptr<Renderer<DXCC>> createDXCCRenderer(AppFormat format)
		{
			switch (format)
			{
				case AppFormat::CONSOLE:
					return std::make_unique<DXCCConsoleRenderer>();
				case AppFormat::CSV:
					return std::make_unique<DXCCCSVRenderer>();
				case AppFormat::JSON:
					return std::make_unique<DXCCJSONRenderer>();
				case AppFormat::XML:
					return std::make_unique<DXCCXMLRenderer>();
				case AppFormat::MD:
					return std::make_unique<DXCCMarkdownRenderer>();
				default:
					throw std::invalid_argument("Invalid Format");
			}
		}

		static std::unique_ptr<Renderer<std::string>> createBioRenderer(AppFormat format)
		{
			return std::make_unique<BioRenderer>();
		}
	};
}

#endif //QRZ_RENDERERFACTORY_H
