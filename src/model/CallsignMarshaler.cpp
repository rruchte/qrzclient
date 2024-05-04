#include "CallsignMarshaler.h"

#include <format>
#include <sstream>

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
 * @brief Converts an XML string representation of a callsign to a Callsign object using the POCO XML library.
 *
 * @param xml_str The XML string representation of a callsign.
 *
 * @return Returns a Callsign object representing the XML data.
 *
 * @throws std::runtime_error If there is an error parsing the XML or if the XML is invalid.
 */
Callsign CallsignMarshaler::FromXml(const std::string &xml_str)
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

	Poco::XML::Element* dxccElement = rootElement->getChildElement("Callsign");
	if (dxccElement == nullptr)
	{
		throw std::runtime_error("Invalid XML - no Callsign child");
	}

	Poco::XML::Node* currChild = dxccElement->firstChild();

	Callsign callsign;

	while (currChild != nullptr)
	{
		if (currChild->nodeType() == Poco::XML::Node::ELEMENT_NODE)
		{
			Poco::XML::Element *currentElement = static_cast<Poco::XML::Element *>(currChild);

			const std::string name = currentElement->nodeName();
			const std::string value = currentElement->innerText();

			if (!name.empty() && !value.empty())
			{
				if (name == "call") callsign.setCall(value);
				else if (name == "xref") callsign.setXref(value);
				else if (name == "aliases") callsign.setAliases(value);
				else if (name == "dxcc") callsign.setDxcc(value);
				else if (name == "fname") callsign.setFname(value);
				else if (name == "name") callsign.setName(value);
				else if (name == "addr1") callsign.setAddr1(value);
				else if (name == "addr2") callsign.setAddr2(value);
				else if (name == "state") callsign.setState(value);
				else if (name == "zip") callsign.setZip(value);
				else if (name == "country") callsign.setCountry(value);
				else if (name == "ccode") callsign.setCcode(value);
				else if (name == "lat") callsign.setLat(value);
				else if (name == "lon") callsign.setLon(value);
				else if (name == "grid") callsign.setGrid(value);
				else if (name == "county") callsign.setCounty(value);
				else if (name == "fips") callsign.setFips(value);
				else if (name == "land") callsign.setLand(value);
				else if (name == "efdate") callsign.setEfdate(value);
				else if (name == "expdate") callsign.setExpdate(value);
				else if (name == "p_call") callsign.setPcall(value);
				else if (name == "class") callsign.setClass(value);
				else if (name == "codes") callsign.setCodes(value);
				else if (name == "qslmgr") callsign.setQslmgr(value);
				else if (name == "email") callsign.setEmail(value);
				else if (name == "url") callsign.setUrl(value);
				else if (name == "u_views") callsign.setUViews(atoi(value.c_str()));
				else if (name == "bio") callsign.setBio(atoi(value.c_str()));
				else if (name == "biodate") callsign.setBiodate(value);
				else if (name == "image") callsign.setImage(value);
				else if (name == "imageinfo") callsign.setImageinfo(value);
				else if (name == "serial") callsign.setSerial(value);
				else if (name == "moddate") callsign.setModdate(value);
				else if (name == "MSA") callsign.setMsa(value);
				else if (name == "AreaCode") callsign.setAreaCode(value);
				else if (name == "TimeZone") callsign.setTimeZone(value);
				else if (name == "GMTOffset") callsign.setGmtOffset(atoi(value.c_str()));
				else if (name == "DST") callsign.setDst(value);
				else if (name == "eqsl") callsign.setEqsl(value);
				else if (name == "mqsl") callsign.setMqsl(value);
				else if (name == "cqzone") callsign.setCqzone(atoi(value.c_str()));
				else if (name == "ituzone") callsign.setItuzone(atoi(value.c_str()));
				else if (name == "born") callsign.setBorn(value);
				else if (name == "user") callsign.setUser(value);
				else if (name == "lotw") callsign.setLotw(value);
				else if (name == "iota") callsign.setIota(value);
				else if (name == "geoloc") callsign.setGeoloc(value);
				else if (name == "attn") callsign.setAttn(value);
				else if (name == "nickname") callsign.setNickname(value);
				else if (name == "name_fmt") callsign.setNameFmt(value);
			}
		}

		currChild = currChild->nextSibling();
	}

	return callsign;
}

/**
 * @brief Converts a vector of Callsign objects to XML string.
 *
 * This function takes a vector of Callsign objects and converts them into XML format using the POCO XML library.
 * Each Callsign object is represented as a separate XML element with its attributes as child elements.
 * The resulting XML structure has a root element named "QRZDatabase" and each Callsign object is nested under a "Callsign" element.
 *
 * @param callsigns The vector of Callsign objects to be converted.
 * @return The XML string representation of the Callsign objects.
 */
std::string CallsignMarshaler::ToXML(const std::vector<Callsign> &callsigns)
{
	Poco::AutoPtr<Poco::XML::Document> pDoc = new Poco::XML::Document;

	auto* pRoot = pDoc->createElement("QRZDatabase");
	pDoc->appendChild(pRoot);

	for (const Callsign &callsign: callsigns)
	{
		auto* pCallsignElement = pDoc->createElement("Callsign");
		pRoot->appendChild(pCallsignElement);

		pCallsignElement->appendChild(pDoc->createElement("call"))->appendChild(pDoc->createTextNode(callsign.getCall()));
		pCallsignElement->appendChild(pDoc->createElement("xref"))->appendChild(pDoc->createTextNode(callsign.getXref()));
		pCallsignElement->appendChild(pDoc->createElement("aliases"))->appendChild(pDoc->createTextNode(callsign.getAliases()));
		pCallsignElement->appendChild(pDoc->createElement("dxcc"))->appendChild(pDoc->createTextNode(callsign.getDxcc()));
		pCallsignElement->appendChild(pDoc->createElement("fname"))->appendChild(pDoc->createTextNode(callsign.getFname()));
		pCallsignElement->appendChild(pDoc->createElement("name"))->appendChild(pDoc->createTextNode(callsign.getName()));
		pCallsignElement->appendChild(pDoc->createElement("addr1"))->appendChild(pDoc->createTextNode(callsign.getAddr1()));
		pCallsignElement->appendChild(pDoc->createElement("addr2"))->appendChild(pDoc->createTextNode(callsign.getAddr2()));
		pCallsignElement->appendChild(pDoc->createElement("state"))->appendChild(pDoc->createTextNode(callsign.getState()));
		pCallsignElement->appendChild(pDoc->createElement("zip"))->appendChild(pDoc->createTextNode(callsign.getZip()));
		pCallsignElement->appendChild(pDoc->createElement("country"))->appendChild(pDoc->createTextNode(callsign.getCountry()));
		pCallsignElement->appendChild(pDoc->createElement("ccode"))->appendChild(pDoc->createTextNode(callsign.getCodes()));
		pCallsignElement->appendChild(pDoc->createElement("lat"))->appendChild(pDoc->createTextNode(callsign.getLat()));
		pCallsignElement->appendChild(pDoc->createElement("lon"))->appendChild(pDoc->createTextNode(callsign.getLon()));
		pCallsignElement->appendChild(pDoc->createElement("grid"))->appendChild(pDoc->createTextNode(callsign.getGrid()));
		pCallsignElement->appendChild(pDoc->createElement("county"))->appendChild(pDoc->createTextNode(callsign.getCounty()));
		pCallsignElement->appendChild(pDoc->createElement("fips"))->appendChild(pDoc->createTextNode(callsign.getFips()));
		pCallsignElement->appendChild(pDoc->createElement("land"))->appendChild(pDoc->createTextNode(callsign.getLand()));
		pCallsignElement->appendChild(pDoc->createElement("efdate"))->appendChild(pDoc->createTextNode(callsign.getEfdate()));
		pCallsignElement->appendChild(pDoc->createElement("expdate"))->appendChild(pDoc->createTextNode(callsign.getExpdate()));
		pCallsignElement->appendChild(pDoc->createElement("p_call"))->appendChild(pDoc->createTextNode(callsign.getPcall()));
		pCallsignElement->appendChild(pDoc->createElement("class"))->appendChild(pDoc->createTextNode(callsign.getClass()));
		pCallsignElement->appendChild(pDoc->createElement("codes"))->appendChild(pDoc->createTextNode(callsign.getCodes()));
		pCallsignElement->appendChild(pDoc->createElement("qslmgr"))->appendChild(pDoc->createTextNode(callsign.getQslmgr()));
		pCallsignElement->appendChild(pDoc->createElement("email"))->appendChild(pDoc->createTextNode(callsign.getEmail()));
		pCallsignElement->appendChild(pDoc->createElement("url"))->appendChild(pDoc->createTextNode(callsign.getUrl()));
		pCallsignElement->appendChild(pDoc->createElement("u_views"))->appendChild(pDoc->createTextNode(std::to_string(callsign.getUViews())));
		pCallsignElement->appendChild(pDoc->createElement("bio"))->appendChild(pDoc->createTextNode(std::to_string(callsign.getBio())));
		pCallsignElement->appendChild(pDoc->createElement("biodate"))->appendChild(pDoc->createTextNode(callsign.getBiodate()));
		pCallsignElement->appendChild(pDoc->createElement("image"))->appendChild(pDoc->createTextNode(callsign.getImage()));
		pCallsignElement->appendChild(pDoc->createElement("imageinfo"))->appendChild(pDoc->createTextNode(callsign.getImageinfo()));
		pCallsignElement->appendChild(pDoc->createElement("serial"))->appendChild(pDoc->createTextNode(callsign.getSerial()));
		pCallsignElement->appendChild(pDoc->createElement("moddate"))->appendChild(pDoc->createTextNode(callsign.getModdate()));
		pCallsignElement->appendChild(pDoc->createElement("MSA"))->appendChild(pDoc->createTextNode(callsign.getMsa()));
		pCallsignElement->appendChild(pDoc->createElement("AreaCode"))->appendChild(pDoc->createTextNode(callsign.getAreaCode()));
		pCallsignElement->appendChild(pDoc->createElement("TimeZone"))->appendChild(pDoc->createTextNode(callsign.getTimeZone()));
		pCallsignElement->appendChild(pDoc->createElement("GMTOffset"))->appendChild(pDoc->createTextNode(std::to_string(callsign.getGmtOffset())));
		pCallsignElement->appendChild(pDoc->createElement("DST"))->appendChild(pDoc->createTextNode(callsign.getDst()));
		pCallsignElement->appendChild(pDoc->createElement("eqsl"))->appendChild(pDoc->createTextNode(callsign.getEqsl()));
		pCallsignElement->appendChild(pDoc->createElement("mqsl"))->appendChild(pDoc->createTextNode(callsign.getMqsl()));
		pCallsignElement->appendChild(pDoc->createElement("cqzone"))->appendChild(pDoc->createTextNode(std::to_string(callsign.getCqzone())));
		pCallsignElement->appendChild(pDoc->createElement("ituzone"))->appendChild(pDoc->createTextNode(std::to_string(callsign.getItuzone())));
		pCallsignElement->appendChild(pDoc->createElement("born"))->appendChild(pDoc->createTextNode(callsign.getBorn()));
		pCallsignElement->appendChild(pDoc->createElement("user"))->appendChild(pDoc->createTextNode(callsign.getUser()));
		pCallsignElement->appendChild(pDoc->createElement("lotw"))->appendChild(pDoc->createTextNode(callsign.getLotw()));
		pCallsignElement->appendChild(pDoc->createElement("iota"))->appendChild(pDoc->createTextNode(callsign.getIota()));
		pCallsignElement->appendChild(pDoc->createElement("geoloc"))->appendChild(pDoc->createTextNode(callsign.getGeoloc()));
		pCallsignElement->appendChild(pDoc->createElement("attn"))->appendChild(pDoc->createTextNode(callsign.getAttn()));
		pCallsignElement->appendChild(pDoc->createElement("nickname"))->appendChild(pDoc->createTextNode(callsign.getNickname()));
		pCallsignElement->appendChild(pDoc->createElement("name_fmt"))->appendChild(pDoc->createTextNode(callsign.getNameFmt()));
	}

	std::ostringstream stream;
	Poco::XML::DOMWriter writer;
	writer.setOptions(Poco::XML::XMLWriter::Options::WRITE_XML_DECLARATION|Poco::XML::XMLWriter::Options::PRETTY_PRINT);
	writer.setIndent("    ");
	writer.writeNode(stream, pDoc);

	return stream.str();
}