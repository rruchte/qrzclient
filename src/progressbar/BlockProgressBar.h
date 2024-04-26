//
// Created by rob on 4/22/24.
//

#ifndef QRZ_BLOCKPROGRESSBAR_H
#define QRZ_BLOCKPROGRESSBAR_H

#include "ProgressBar.h"

#include "indicators/block_progress_bar.hpp"

namespace qrz
{
	/**
	 * @class BlockProgressBar
	 * @brief Represents a block-based progress bar.
	 *
	 * The BlockProgressBar class is a concrete implementation of the ProgressBar class.
	 * It uses the block progress bar from the indicators library to display progress.
	 */
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

		/**
		 * @brief Sets the progress of the BlockProgressBar.
		 *
		 * This function sets the progress of the BlockProgressBar to the specified value.
		 * It internally calls the set_progress() function of the underlying indicators::BlockProgressBar object.
		 *
		 * @param new_progress The new progress value.
		 */
		void setProgress(size_t new_progress) override
		{
			bar.set_progress(new_progress);
		}

		/**
		 * @brief Sets an option for the BlockProgressBar.
		 *
		 * This function sets an option for the BlockProgressBar. It uses the specified setting
		 * to set an option for the underlying indicators::BlockProgressBar object.
		 *
		 * @param setting The setting to be used to set the option.
		 */
		void setOption(const indicators::details::Setting<std::string, indicators::details::ProgressBarOption::postfix_text> &setting) override
		{
			bar.set_option(setting);
		}

	private:
		indicators::BlockProgressBar bar;
	};
}
#endif //QRZ_BLOCKPROGRESSBAR_H
