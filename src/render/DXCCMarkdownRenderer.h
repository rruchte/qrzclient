#ifndef QRZ_DXCCMARKDOWNRENDERER_H
#define QRZ_DXCCMARKDOWNRENDERER_H

#include "Renderer.h"

#include <tabulate/markdown_exporter.hpp>
#include <tabulate/table.hpp>

#include "../model/DXCC.h"

namespace qrz::render
{
	/**
	 * @class DXCCMarkdownRenderer
	 * @brief The DXCCMarkdownRenderer class is responsible for rendering DXCC objects in markdown format.
	 *
	 * This class inherits from Renderer<DXCC> and provides an implementation for rendering DXCC objects in markdown format.
	 */
	class DXCCMarkdownRenderer : public Renderer<DXCC>
	{
	public:
		/**
		 * @brief Renders the given DXCC objects in markdown format.
		 *
		 * This function takes a vector of DXCC objects and generates a markdown table and prints it to the console.
		 *
		 * @param dxccList The vector of DXCC objects to render.
		 */
		void Render(const std::vector<DXCC> &dxccList) override
		{
			tabulate::Table output = generateMarkdown(dxccList);

			tabulate::MarkdownExporter exporter;
			auto markdown = exporter.dump(output);

			std::cout << markdown << std::endl;
		}

	private:
		/**
		 * @brief Generates a markdown table from a vector of DXCC objects.
		 *
		 * This function takes a vector of DXCC objects and generates a markdown table with the following columns:
		 * - DXCC Code
		 * - DXCC Name
		 * - Continent
		 * - County Code (2)
		 * - County Code (3)
		 * - ITU Zone
		 * - CQ Zone
		 * - Timezone
		 * - Latitude
		 * - Longitude
		 * - Notes
		 *
		 * @param dxccList The vector of DXCC objects to generate the markdown table from.
		 * @return The generated markdown table as a tabulate::Table object.
		 */
		static tabulate::Table generateMarkdown(const std::vector<DXCC> &dxccList)
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


#endif //QRZ_DXCCMARKDOWNRENDERER_H
