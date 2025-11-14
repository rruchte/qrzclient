#ifndef QRZ_CALLSIGNMARKDOWNRENDERER_H
#define QRZ_CALLSIGNMARKDOWNRENDERER_H

#include "Renderer.h"

#include <vector>

#include <tabulate/table.hpp>
#include <tabulate/markdown_exporter.hpp>

#include "../model/Callsign.h"
#include "../model/CallsignMarshaler.h"

namespace qrz::render
{
	/**
	 * @class CallsignMarkdownRenderer
	 * @brief The CallsignMarkdownRenderer class is responsible for rendering Callsign objects as markdown.
	 *
	 * This class derives from the Renderer base class and provides an implementation for rendering Callsign objects as markdown.
	 * It generates a markdown table with the Callsign object properties and outputs the table to the console.
	 */
	class CallsignMarkdownRenderer : public Renderer<Callsign>
	{
	public:
		/**
		 * @brief Renders a list of Callsign objects as markdown.
		 *
		 * This function takes a vector of Callsign objects and generates a markdown table
		 * with the Callsign object properties. It uses the generateMarkdown function to
		 * create the markdown table and the MarkdownExporter class to convert the table
		 * to markdown format. The markdown table is then printed to the console.
		 *
		 * @param callsignList A vector of Callsign objects to be rendered.
		 */
		void Render(const std::vector<Callsign> &callsignList) override
		{
			tabulate::Table output = generateMarkdown(callsignList);

			tabulate::MarkdownExporter exporter;
			auto markdown = exporter.dump(output);

			std::cout << markdown << std::endl;
		}

	private:
		/**
		 * @brief Generate a markdown table from a list of Callsign objects.
		 *
		 * This function takes a vector of Callsign objects and generates a markdown table with the Callsign object
		 * properties. The table has the following columns: Callsign, Name, Class, Address, City, County, State, Zip,
		 * Country, and Grid. The Callsign objects are displayed row by row in the table.
		 *
		 * @param callsignList A vector of Callsign objects.
		 * @return A markdown table with the Callsign object properties.
		 */
		tabulate::Table generateMarkdown(const std::vector<Callsign> &callsignList)
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
									   callsign.getCity(),
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


#endif //QRZ_CALLSIGNMARKDOWNRENDERER_H
