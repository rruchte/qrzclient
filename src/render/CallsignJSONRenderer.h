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
	class CallsignJSONRenderer : public Renderer<Callsign>
	{
	public:
		void Render(const std::vector<Callsign> &callsigns) override
		{
			std::string output = generateTable(callsigns);

			std::cout << output << std::endl;
		}

	private:
		std::string generateTable(const std::vector<Callsign> &callsignList)
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
