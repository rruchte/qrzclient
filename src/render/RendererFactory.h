#ifndef QRZ_RENDERERFACTORY_H
#define QRZ_RENDERERFACTORY_H

#include "../OutputFormat.h"
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
		static std::unique_ptr<Renderer<Callsign>> createCallsignRenderer(OutputFormat format)
		{
			switch (format)
			{
				case OutputFormat::CONSOLE:
					return std::make_unique<CallsignConsoleRenderer>();
				case OutputFormat::CSV:
					return std::make_unique<CallsignCSVRenderer>();
				case OutputFormat::JSON:
					return std::make_unique<CallsignJSONRenderer>();
				case OutputFormat::XML:
					return std::make_unique<CallsignXMLRenderer>();
				case OutputFormat::MD:
					return std::make_unique<CallsignMarkdownRenderer>();
				default:
					throw std::invalid_argument("Invalid Format");
			}
		}

		static std::unique_ptr<Renderer<DXCC>> createDXCCRenderer(OutputFormat format)
		{
			switch (format)
			{
				case OutputFormat::CONSOLE:
					return std::make_unique<DXCCConsoleRenderer>();
				case OutputFormat::CSV:
					return std::make_unique<DXCCCSVRenderer>();
				case OutputFormat::JSON:
					return std::make_unique<DXCCJSONRenderer>();
				case OutputFormat::XML:
					return std::make_unique<DXCCXMLRenderer>();
				case OutputFormat::MD:
					return std::make_unique<DXCCMarkdownRenderer>();
				default:
					throw std::invalid_argument("Invalid Format");
			}
		}

		static std::unique_ptr<Renderer<std::string>> createBioRenderer()
		{
			return std::make_unique<BioRenderer>();
		}
	};
}

#endif //QRZ_RENDERERFACTORY_H
