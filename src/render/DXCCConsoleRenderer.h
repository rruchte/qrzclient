#ifndef QRZ_DXCCCONSOLERENDERER_H
#define QRZ_DXCCCONSOLERENDERER_H

#include "Renderer.h"

#include <tabulate/table.hpp>

#include "../model/DXCC.h"

namespace qrz::render
{
	class DXCCConsoleRenderer : public Renderer<DXCC>
	{
	public:
		void Render(const std::vector<DXCC> &dxccList) override
		{
			tabulate::Table output = generateTable(dxccList);

			std::cout << output << std::endl;
		}

	private:
		static tabulate::Table generateTable(const std::vector<DXCC> &dxccList)
		{
			tabulate::Table output;

			output.add_row({
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
				output.add_row({
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

			// center-align and color header cells
			for (size_t i = 0; i < output[0].size(); ++i)
			{
				output[0][i].format()
						.font_align(tabulate::FontAlign::center)
						.font_style({tabulate::FontStyle::bold});
			}

			return output;
		}
	};
}


#endif //QRZ_DXCCCONSOLERENDERER_H
