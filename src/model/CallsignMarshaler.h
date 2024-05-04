#ifndef QRZ_CALLSIGNMARSHALER_H
#define QRZ_CALLSIGNMARSHALER_H

#include <vector>

#include "Callsign.h"

namespace qrz
{
	/**
	 * @class CallsignMarshaler
	 * @brief This class provides functionality to convert callsign data between XML string representation and Callsign objects.
	 */
	class CallsignMarshaler
	{
	public:
		/**
		 * @brief Converts an XML string representation of a callsign to a Callsign object.
		 *
		 * @param xml_str The XML string representation of a callsign.
		 *
		 * @return Returns a Callsign object representing the XML data.
		 *
		 * @throws std::runtime_error If there is an error parsing the XML or if the XML is invalid.
		 */
		static Callsign FromXml(const std::string &xml_str);

		/**
		 * @brief Converts a vector of Callsign objects to an XML string representation.
		 *
		 * This function takes a vector of Callsign objects and converts them into XML format using the POCO XML library.
		 * Each Callsign object is represented as a separate XML element with its attributes as child elements.
		 * The resulting XML structure has a root element named "QRZDatabase" and each Callsign object is nested under a "Callsign" element.
		 *
		 * @param callsigns The vector of Callsign objects to be converted to XML.
		 * @return The XML string representation of the Callsign objects.
		 */
		static std::string ToXML(const std::vector<Callsign> &callsign);
	};
}

#endif //QRZ_CALLSIGNMARSHALER_H
