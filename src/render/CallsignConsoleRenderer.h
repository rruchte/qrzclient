#ifndef QRZ_CALLSIGNCONSOLERENDERER_H
#define QRZ_CALLSIGNCONSOLERENDERER_H

#include "Renderer.h"

#include <vector>

#include <tabulate/table.hpp>

#include "../model/Callsign.h"


namespace qrz::render
{
	class CallsignConsoleRenderer : public Renderer<Callsign>
	{
	public:
		void Render(const std::vector<Callsign> &callsigns) override
		{
			tabulate::Table output = generateTable(callsigns);

			std::cout << output << std::endl;
		}

	private:
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
