#ifndef QRZ_DXCCCONSOLERENDERER_H
#define QRZ_DXCCCONSOLERENDERER_H

#include "Renderer.h"

#include <tabulate/table.hpp>

#include "../model/DXCC.h"

namespace qrz::render
{
	/**
	 * @class DXCCConsoleRenderer
	 * @brief A class for rendering DXCC objects to the console.
	 *
	 * This class provides a rendering functionality for DXCC objects and outputs them to the console
	 * using the tabulate library. It inherits from the Renderer class.
	 */
	class DXCCConsoleRenderer : public Renderer<DXCC>
	{
	public:
		/**
		 * @brief Renders a list of DXCC objects to the console.
		 *
		 * This method takes a vector of DXCC objects and generates a table representation of the data using the tabulate library.
		 * The generated table consists of the following columns: DXCC Code, DXCC Name, Continent, County Code (2),
		 * County Code (3), ITU Zone, CQ Zone, Timezone, Latitude, Longitude, and Notes.
		 *
		 * @param dxccList The vector of DXCC objects to render.
		 */
		void Render(const std::vector<DXCC> &dxccList) override
		{
			tabulate::Table output = generateTable(dxccList);

			std::cout << output << std::endl;
		}

	private:
		/**
		 * @brief Generates a table representation of a list of DXCC objects.
		 *
		 * This function takes a vector of DXCC objects and generates a table representation of the data.
		 * The table consists of the following columns: DXCC Code, DXCC Name, Continent, County Code (2),
		 * County Code (3), ITU Zone, CQ Zone, Timezone, Latitude, Longitude, and Notes.
		 *
		 * @param dxccList The vector of DXCC objects to generate the table from.
		 * @return A tabulate::Table object representing the generated table.
		 */
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
