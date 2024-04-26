#ifndef QRZ_DXCCCSVRENDERER_H
#define QRZ_DXCCCSVRENDERER_H

#include "Renderer.h"

#include <iostream>
#include <sstream>

#include "../Util.h"
#include "../model/DXCC.h"

namespace qrz::render
{
	/**
	 * @class DXCCCSVRenderer
	 * @brief The DXCCCSVRenderer class is responsible for rendering objects of type DXCC to CSV format.
	 *
	 * This class derives from the Renderer class and provides a custom implementation to render DXCC objects to CSV
	 * format.
	 */
	class DXCCCSVRenderer : public Renderer<DXCC>
	{
	public:
		/**
		* @class DXCCCSVRenderer
		* @brief The DXCCCSVRenderer class is responsible for rendering objects of type DXCC to CSV format.
		*
		* This class derives from the Renderer class and provides a custom implementation to render DXCC objects to CSV
		* format.
		*/
		void Render(const std::vector<DXCC> &dxccList) override
		{
			std::string output = generateCSV(dxccList);

			std::cout << output << std::endl;
		}

	private:
		/**
		 * @brief Generates a CSV string from a vector of DXCC objects.
		 *
		 * This function takes a vector of DXCC objects and generates a CSV string representing the data.
		 *
		 * @param dxccList The vector of DXCC objects.
		 * @return The generated CSV string.
		 */
		static std::string generateCSV(const std::vector<DXCC> &dxccList)
		{
			std::vector<std::vector<std::string>> rows;

			rows.push_back({
								   "DXCC Code",
								   "DXCC Name",
								   "Continent",
								   "County Code (2)",
								   "County Code (3)",
								   "ITU Zone",
								   "CQ Zone",
								   "Timezone",
								   "Latitude",
								   "Longitude",
								   "Notes"
						   });

			for (const DXCC &dxcc: dxccList)
			{
				rows.push_back({
									   dxcc.getDxcc(),
									   dxcc.getName(),
									   dxcc.getContinent(),
									   dxcc.getCc(),
									   dxcc.getCcc(),
									   dxcc.getItuzone(),
									   dxcc.getCqzone(),
									   dxcc.getTimezone(),
									   dxcc.getLat(),
									   dxcc.getLon(),
									   dxcc.getNotes()
							   });
			}

			std::stringstream ss;

			for (const auto &row: rows)
			{
				ss << VectorToCSV(row) << '\n';
			}

			return ss.str();
		}
	};
}


#endif //QRZ_DXCCCSVRENDERER_H
