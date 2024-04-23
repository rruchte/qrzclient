//
// Created by rob on 4/22/24.
//

#ifndef QRZ_BLOCKPROGRESSBAR_H
#define QRZ_BLOCKPROGRESSBAR_H

#include "ProgressBar.h"

#include "indicators/block_progress_bar.hpp"

namespace qrz
{
	class BlockProgressBar : public ProgressBar
	{
	public:
		BlockProgressBar() :
				bar{
						indicators::option::Stream{std::cerr},
						indicators::option::BarWidth{80},
						indicators::option::Start{"["},
						indicators::option::End{"]"},
						indicators::option::ForegroundColor{indicators::Color::white}  ,
						indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
				}
		{}

		void setProgress(size_t new_progress) override
		{
			bar.set_progress(new_progress);
		}

		void setOption(const indicators::details::Setting<std::string, indicators::details::ProgressBarOption::postfix_text> &setting) override
		{
			bar.set_option(setting);
		}

	private:
		indicators::BlockProgressBar bar;
	};
}
#endif //QRZ_BLOCKPROGRESSBAR_H
