#ifndef QRZ_DXCCJSONRENDERER_H
#define QRZ_DXCCJSONRENDERER_H

#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>

#include "../model/DXCC.h"

namespace qrz::render
{
	class DXCCJSONRenderer : public Renderer<DXCC>
	{
	public:
		void Render(const std::vector<DXCC> &dxccList) override
		{
			std::string output = generateTable(dxccList);

			std::cout << output << std::endl;
		}

	private:
		static std::string generateTable(const std::vector<DXCC> &dxccList)
		{
			Poco::JSON::Array root;
			for (const DXCC &dxcc: dxccList)
			{
				Poco::JSON::Object currValue;

				currValue.set("dxcc", dxcc.getDxcc());
				currValue.set("name", dxcc.getName());
				currValue.set("continent", dxcc.getContinent());
				currValue.set("cc", dxcc.getCc());
				currValue.set("ccc", dxcc.getCcc());
				currValue.set("ituzone", dxcc.getItuzone());
				currValue.set("cqzone", dxcc.getCqzone());
				currValue.set("timezone", dxcc.getTimezone());
				currValue.set("lat", dxcc.getLat());
				currValue.set("lon", dxcc.getLon());
				currValue.set("notes", dxcc.getNotes());

				root.add(currValue);
			}

			std::stringstream out;

			root.stringify(out, 4);

			return out.str();
		}
	};
}

#endif //QRZ_DXCCJSONRENDERER_H
