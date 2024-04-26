#ifndef QRZ_CALLSIGNXMLRENDERER_H
#define QRZ_CALLSIGNXMLRENDERER_H

#include "Renderer.h"

#include <vector>

#include "../model/Callsign.h"
#include "../model/CallsignMarshaler.h"

namespace qrz::render
{
	/**
	 * @class CallsignXMLRenderer
	 * @brief The CallsignXMLRenderer class is a concrete class that renders Callsign objects to XML format.
	 *
	 * This class inherits from the Renderer base class and implements the Render method to provide customized rendering functionality for Callsign objects.
	 * It uses the CallsignMarshaler class to convert the callsign objects to XML format, and outputs the result to the standard output.
	 */
	class CallsignXMLRenderer : public Renderer<Callsign>
	{
	public:
		/**
		 * @brief Renders a vector of Callsign objects to XML format.
		 *
		 * This method converts the given vector of Callsign objects to XML format using the CallsignMarshaler class and outputs the result to the standard output.
		 *
		 * @param callsign A reference to a vector of Callsign objects to be rendered.
		 *
		 * @note The rendered XML is printed to the standard output.
		 */
		void Render(const std::vector<Callsign> &callsign) override
		{
			CallsignMarshaler m;

			std::cout << m.ToXML(callsign) << std::endl;
		}
	};
}

#endif //QRZ_CALLSIGNXMLRENDERER_H
