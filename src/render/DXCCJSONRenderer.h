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
	/**
	 * @class DXCCJSONRenderer
	 * @brief The DXCCJSONRenderer class is responsible for rendering DXCC objects into JSON format.
	 *
	 * This class inherits from the Renderer base class and provides custom rendering functionality for DXCC objects.
	 * It converts a vector of DXCC objects into a JSON string representation.
	 */
	class DXCCJSONRenderer : public Renderer<DXCC>
	{
	public:
		/**
		 * Renders a list of DXCC objects into a formatted table and prints it to the console.
		 *
		 * @param dxccList The vector of DXCC objects to be rendered.
		 */
		void Render(const std::vector<DXCC> &dxccList) override
		{
			std::string output = generateJSON(dxccList);

			std::cout << output << std::endl;
		}

	private:
		/**
		 * @class DXCCJSONRenderer
		 * @brief The DXCCJSONRenderer class renders DXCC objects into JSON format.
		 *
		 * This class provides functionality to convert a vector of DXCC objects into a JSON string representation.
		 */
		static std::string generateJSON(const std::vector<DXCC> &dxccList)
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
