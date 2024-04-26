#ifndef QRZ_CALLSIGNCONSOLERENDERER_H
#define QRZ_CALLSIGNCONSOLERENDERER_H

#include "Renderer.h"

#include <vector>

#include <tabulate/table.hpp>

#include "../model/Callsign.h"


namespace qrz::render
{
	/**
	 * @class CallsignConsoleRenderer
	 * @brief The CallsignConsoleRenderer class is responsible for rendering Callsign objects to the console.
	 *
	 * This class is derived from the Renderer<Callsign> class and provides an implementation for rendering Callsign objects.
	 * It generates a table based on the provided Callsign objects and displays it on the console.
	 */
	class CallsignConsoleRenderer : public Renderer<Callsign>
	{
	public:
		/**
		 * Renders the given vector of Callsign objects to the console.
		 *
		 * @param callsigns - The vector of Callsign objects to be rendered.
		 */
		void Render(const std::vector<Callsign> &callsigns) override
		{
			tabulate::Table output = generateTable(callsigns);

			std::cout << output << std::endl;
		}

	private:
		/**
		 * @brief Generates a table based on the provided Callsign objects.
		 *
		 * This function takes a vector of Callsign objects and generates a table with the following columns:
		 * - Callsign
		 * - Name
		 * - Class
		 * - Address
		 * - City
		 * - County
		 * - State
		 * - Zip
		 * - Country
		 * - Grid
		 *
		 * Each Callsign object in the vector will be added as a row in the table.
		 * The header cells of the table will be centered and styled with bold font.
		 *
		 * @param callsignList The vector of Callsign objects.
		 * @return A table containing the Callsign data.
		 */
		tabulate::Table generateTable(const std::vector<Callsign> &callsignList)
		{
			tabulate::Table output;

			output.add_row({
								   "Callsign",
								   "Name",
								   "Class",
								   "Address",
								   "City",
								   "County",
								   "State",
								   "Zip",
								   "Country",
								   "Grid"
						   });

			for (const Callsign &callsign: callsignList)
			{
				output.add_row({
									   callsign.getCall(),
									   callsign.getNameFmt(),
									   callsign.getClass(),
									   callsign.getAddr1(),
									   callsign.getAddr2(),
									   callsign.getCounty(),
									   callsign.getState(),
									   callsign.getZip(),
									   callsign.getCountry(),
									   callsign.getGrid()
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

#endif //QRZ_CALLSIGNCONSOLERENDERER_H
