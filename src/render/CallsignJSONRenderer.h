#ifndef QRZ_CALLSIGNJSONRENDERER_H
#define QRZ_CALLSIGNJSONRENDERER_H

#include "Renderer.h"

#include <sstream>
#include <vector>

#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>

#include "../model/Callsign.h"

namespace qrz::render
{
	/**
	 * @class CallsignJSONRenderer
	 * @brief The CallsignJSONRenderer class is responsible for rendering Callsign objects as JSON.
	 *
	 * This class inherits from the Renderer<Callsign> base class and provides custom rendering functionality for Callsign objects.
	 */
	class CallsignJSONRenderer : public Renderer<Callsign>
	{
	public:
		/**
		 * @brief Renders a vector of Callsign objects as JSON and outputs it to the console.
		 *
		 * This function takes a vector of Callsign objects and converts them into a JSON string representation using
		 * the generateJSON() function. The resulting JSON string is then output to the console using std::cout.
		 *
		 * @param callsigns A reference to a vector of Callsign objects.
		 */
		void Render(const std::vector<Callsign> &callsigns) override
		{
			std::string output = generateJSON(callsigns);

			std::cout << output << std::endl;
		}

	private:
		/**
		 * @brief Generates a JSON string from a list of Callsign objects.
		 *
		 * This function takes a vector of Callsign objects and converts them into a JSON string representation using
		 * the Poco::JSON library. Each Callsign object is converted into a JSON object with its properties as key-value
		 * pairs. The resulting JSON array is then stringified using the Poco::JSON::Array stringify function.
		 *
		 * @param callsignList A vector of Callsign objects.
		 * @return A string representation of the JSON.
		 */
		std::string generateJSON(const std::vector<Callsign> &callsignList)
		{
			Poco::JSON::Array root;

			for (const Callsign &callsign: callsignList)
			{
				Poco::JSON::Object currValue;

				currValue.set("call", callsign.getCall());
				currValue.set("xref", callsign.getXref());
				currValue.set("aliases", callsign.getAliases());
				currValue.set("dxcc", callsign.getDxcc());
				currValue.set("fname", callsign.getFname());
				currValue.set("name", callsign.getName());
				currValue.set("addr1", callsign.getAddr1());
				currValue.set("addr2", callsign.getAddr2());
				currValue.set("state", callsign.getState());
				currValue.set("zip", callsign.getZip());
				currValue.set("country", callsign.getCountry());
				currValue.set("ccode", callsign.getCodes());
				currValue.set("lat", callsign.getLat());
				currValue.set("lon", callsign.getLon());
				currValue.set("grid", callsign.getGrid());
				currValue.set("county", callsign.getCounty());
				currValue.set("fips", callsign.getFips());
				currValue.set("land", callsign.getLand());
				currValue.set("efdate", callsign.getEfdate());
				currValue.set("expdate", callsign.getExpdate());
				currValue.set("p_call", callsign.getPcall());
				currValue.set("class", callsign.getClass());
				currValue.set("codes", callsign.getCodes());
				currValue.set("qslmgr", callsign.getQslmgr());
				currValue.set("email", callsign.getEmail());
				currValue.set("url", callsign.getUrl());
				currValue.set("u_views", callsign.getUViews());
				currValue.set("bio", callsign.getBio());
				currValue.set("biodate", callsign.getBiodate());
				currValue.set("image", callsign.getImage());
				currValue.set("imageinfo", callsign.getImageinfo());
				currValue.set("serial", callsign.getSerial());
				currValue.set("moddate", callsign.getModdate());
				currValue.set("MSA", callsign.getMsa());
				currValue.set("AreaCode", callsign.getAreaCode());
				currValue.set("TimeZone", callsign.getTimeZone());
				currValue.set("GMTOffset", callsign.getGmtOffset());
				currValue.set("DST", callsign.getDst());
				currValue.set("eqsl", callsign.getEqsl());
				currValue.set("mqsl", callsign.getMqsl());
				currValue.set("cqzone", callsign.getCqzone());
				currValue.set("ituzone", callsign.getItuzone());
				currValue.set("born", callsign.getBorn());
				currValue.set("user", callsign.getUser());
				currValue.set("lotw", callsign.getLotw());
				currValue.set("iota", callsign.getIota());
				currValue.set("geoloc", callsign.getGeoloc());
				currValue.set("attn", callsign.getAttn());
				currValue.set("nickname", callsign.getNickname());
				currValue.set("name_fmt", callsign.getNameFmt());

				root.add(currValue);
			}

			std::ostringstream out;

			root.stringify(out, 4);

			return out.str();
		}
	};
}


#endif //QRZ_CALLSIGNJSONRENDERER_H
