#ifndef QRZ_DXCCXMLRENDERER_H
#define QRZ_DXCCXMLRENDERER_H

#include "Renderer.h"

#include <iostream>

#include "../model/DXCC.h"
#include "../model/DXCCMarshaler.h"

namespace qrz::render
{
	class DXCCXMLRenderer : public Renderer<DXCC>
	{
	public:
		void Render(const std::vector<DXCC> &dxccList) override
		{
			DXCCMarshaler m;

			std::cout << m.ToXML(dxccList) << std::endl;
		}
	};
}

#endif //QRZ_DXCCXMLRENDERER_H
