#ifndef QRZ_DXCCMARSHALER_H
#define QRZ_DXCCMARSHALER_H

#include <vector>

#include "DXCC.h"

namespace qrz
{
	/**
	 * @brief The DXCCMarshaler class provides methods for converting DXCC objects to and from XML.
	 */
	class DXCCMarshaler
	{
	public:
		/**
		 * @brief Converts an XML string representation of a DXCC record to a DXCC object.
		 *
		 * This function takes in an XML string representation of a DXCC record and converts it into a DXCC object.
		 *
		 * @param xml_str The XML string representation of a DXCC record.
		 *
		 * @return Returns a DXCC object representing the XML data.
		 *
		 * @throws std::runtime_error If there is an error parsing the XML or if the XML is invalid.
		 */
		static DXCC FromXml(const std::string &xml_str);

		/**
		 * @brief Converts a vector of DXCC objects to an XML string representation.
		 *
		 * This function takes a vector of DXCC objects and converts each object into an XML element with its attributes as child elements.
		 * The resulting XML structure has a root element named "QRZDatabase" and each DXCC object is nested under a "DXCC" element.
		 * The DXCC object attributes are added as child elements inside the "DXCC" element.
		 *
		 * @param dxccList The vector of DXCC objects to be converted.
		 * @return The XML string representation of the DXCC objects.
		 */
		static std::string ToXML(const std::vector<DXCC> &dxccList);
	};
}

#endif //QRZ_DXCCMARSHALER_H
