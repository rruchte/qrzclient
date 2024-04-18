#ifndef QRZ_CALLSIGNXMLRENDERER_H
#define QRZ_CALLSIGNXMLRENDERER_H

#include "Renderer.h"

#include <vector>

#include "../model/Callsign.h"
#include "../model/CallsignMarshaler.h"

namespace qrz::render
{
	class CallsignXMLRenderer : public Renderer<Callsign>
	{
	public:
		void Render(const std::vector<Callsign> &callsign) override
		{
			CallsignMarshaler m;

			std::cout << m.ToXML(callsign) << std::endl;
		}
	};
}

#endif //QRZ_CALLSIGNXMLRENDERER_H
