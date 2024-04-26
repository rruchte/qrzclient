#ifndef QRZ_DXCCXMLRENDERER_H
#define QRZ_DXCCXMLRENDERER_H

#include "Renderer.h"

#include <iostream>

#include "../model/DXCC.h"
#include "../model/DXCCMarshaler.h"

namespace qrz::render
{
	/**
	 * @class DXCCXMLRenderer
	 * @brief The DXCCXMLRenderer class is responsible for rendering DXCC objects to XML format.
	 *
	 * DXCCXMLRenderer is a concrete class that inherits from the base Renderer class. It provides functionality to render DXCC objects to XML format.
	 *
	 * @tparam DXCC The type of objects to be rendered.
	 */
	class DXCCXMLRenderer : public Renderer<DXCC>
	{
	public:
		/**
		 * @brief Render the DXCC objects to XML format.
		 *
		 * This function takes a vector of DXCC objects and renders them to XML format using the DXCCMarshaler class. The XML output is printed to the standard output.
		 *
		 * @param dxccList The vector of DXCC objects to be rendered.
		 */
		void Render(const std::vector<DXCC> &dxccList) override
		{
			DXCCMarshaler m;

			std::cout << m.ToXML(dxccList) << std::endl;
		}
	};
}

#endif //QRZ_DXCCXMLRENDERER_H
