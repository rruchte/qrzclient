#ifndef QRZ_DXCCCSVRENDERER_H
#define QRZ_DXCCCSVRENDERER_H

#include "Renderer.h"

#include <iostream>
#include <sstream>

#include "../Util.h"
#include "../model/DXCC.h"

namespace qrz::render
{
	class DXCCCSVRenderer : public Renderer<DXCC>
	{
	public:
		void Render(const std::vector<DXCC> &dxccList) override
		{
			std::string output = generateCSV(dxccList);

			std::cout << output << std::endl;
		}

	private:
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
