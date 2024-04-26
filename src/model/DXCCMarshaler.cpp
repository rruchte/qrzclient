#include "DXCCMarshaler.h"

#include <format>
#include <sstream>
#include <stdexcept>

#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/ElementsByTagNameList.h>
#include <Poco/DOM/Node.h>
#include <Poco/DOM/Text.h>
#include <Poco/XML/XMLWriter.h>

using namespace qrz;

/**
 * @brief Converts an XML string representation of a DXCC record to a DXCC object.
 *
 * This function uses the Poco XML parser to parse the XML string and then extracts the relevant data from it to
 * populate the DXCC object.
 *
 * @param xml_str The XML string representation of a DXCC record.
 *
 * @return Returns a DXCC object representing the XML data.
 *
 * @throws std::runtime_error If there is an error parsing the XML or if the XML is invalid.
 */
DXCC DXCCMarshaler::FromXml(const std::string& xml_str)
{
	Poco::XML::DOMParser parser;
	Poco::AutoPtr<Poco::XML::Document> pDoc;

	try
	{
		pDoc = parser.parseString(xml_str);
	}
	catch (Poco::Exception& e)
	{
		throw std::runtime_error(std::format("XML Parse error: {:s}", e.message()));
	}

	Poco::XML::Element* rootElement = pDoc->documentElement();
	if (rootElement->nodeName() != "QRZDatabase")
	{
		throw std::runtime_error("Invalid XML - root not is not QRZDatabase");
	}

	Poco::XML::Element* dxccElement = rootElement->getChildElement("DXCC");
	if (dxccElement == nullptr)
	{
		throw std::runtime_error("Invalid XML - no DXCC child");
	}

	Poco::XML::Node* currChild = dxccElement->firstChild();

	DXCC dxcc;

	while (currChild)
	{
		if (currChild->nodeType() == Poco::XML::Node::ELEMENT_NODE)
		{
			Poco::XML::Element *currentElement = static_cast<Poco::XML::Element *>(currChild);

			const std::string name = currentElement->nodeName();
			const std::string value = currentElement->innerText();

			if (!name.empty() && !value.empty())
			{
				if (name == "dxcc") dxcc.setDxcc(value);
				else if (name == "cc") dxcc.setCc(value);
				else if (name == "ccc") dxcc.setCcc(value);
				else if (name == "name") dxcc.setName(value);
				else if (name == "continent") dxcc.setContinent(value);
				else if (name == "ituzone") dxcc.setItuzone(value);
				else if (name == "cqzone") dxcc.setCqzone(value);
				else if (name == "timezone") dxcc.setTimezone(value);
				else if (name == "lat") dxcc.setLat(value);
				else if (name == "lon") dxcc.setLon(value);
				else if (name == "notes") dxcc.setNotes(value);
			}
		}

		currChild = currChild->nextSibling();
	}

	return dxcc;
}

/**
 * @brief Converts a vector of DXCC objects to XML string.
 *
 * This function takes a vector of DXCC objects and converts them into XML format using the POCO XML library.
 * Each DXCC object is represented as a separate XML element with its attributes as child elements.
 * The resulting XML structure has a root element named "QRZDatabase" and each DXCC object is nested under a "DXCC" element.
 *
 * @param dxccList The vector of DXCC objects to be converted.
 * @return The XML string representation of the DXCC objects.
 */
std::string DXCCMarshaler::ToXML(const std::vector<DXCC> &dxccList)
{
	Poco::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

	auto* pRoot = pDoc->createElement("QRZDatabase");
	pDoc->appendChild(pRoot);

	for(const DXCC &dxcc : dxccList)
	{
		auto* pDxccElement = pDoc->createElement("DXCC");
		pRoot->appendChild(pDxccElement);

		pDxccElement->appendChild(pDoc->createElement("dxcc"))->appendChild(pDoc->createTextNode(dxcc.getDxcc()));
		pDxccElement->appendChild(pDoc->createElement("cc"))->appendChild(pDoc->createTextNode(dxcc.getCc()));
		pDxccElement->appendChild(pDoc->createElement("ccc"))->appendChild(pDoc->createTextNode(dxcc.getCcc()));
		pDxccElement->appendChild(pDoc->createElement("name"))->appendChild(pDoc->createTextNode(dxcc.getName()));
		pDxccElement->appendChild(pDoc->createElement("continent"))->appendChild(pDoc->createTextNode(dxcc.getContinent()));
		pDxccElement->appendChild(pDoc->createElement("ituzone"))->appendChild(pDoc->createTextNode(dxcc.getItuzone()));
		pDxccElement->appendChild(pDoc->createElement("cqzone"))->appendChild(pDoc->createTextNode(dxcc.getCqzone()));
		pDxccElement->appendChild(pDoc->createElement("timezone"))->appendChild(pDoc->createTextNode(dxcc.getTimezone()));
		pDxccElement->appendChild(pDoc->createElement("lat"))->appendChild(pDoc->createTextNode(dxcc.getLat()));
		pDxccElement->appendChild(pDoc->createElement("lon"))->appendChild(pDoc->createTextNode(dxcc.getLon()));
		pDxccElement->appendChild(pDoc->createElement("notes"))->appendChild(pDoc->createTextNode(dxcc.getNotes()));
	}

	std::ostringstream stream;
	Poco::XML::DOMWriter writer;
	writer.setOptions(Poco::XML::XMLWriter::Options::WRITE_XML_DECLARATION|Poco::XML::XMLWriter::Options::PRETTY_PRINT);
	writer.setIndent("    ");
	writer.writeNode(stream, pDoc);

	return stream.str();
}