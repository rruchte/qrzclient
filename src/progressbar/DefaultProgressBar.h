//
// Created by rob on 4/22/24.
//

#ifndef QRZ_DEFAULTPROGRESSBAR_H
#define QRZ_DEFAULTPROGRESSBAR_H

#include "ProgressBar.h"

#include "indicators/progress_bar.hpp"

namespace qrz
{
	/**
	 * @class DefaultProgressBar
	 * @brief Represents a default progress bar implementation.
	 *
	 * This class provides a default implementation of a progress bar using the indicators library.
	 */
	class DefaultProgressBar : public ProgressBar
	{
	public:
		DefaultProgressBar() :
				bar{
						indicators::option::Stream{std::cerr},
						indicators::option::BarWidth{80},
						indicators::option::Start{"["},
						indicators::option::Fill{"="},
						indicators::option::Lead{">"},
						indicators::option::Remainder{" "},
						indicators::option::End{"]"},
						indicators::option::ForegroundColor{indicators::Color::white}  ,
						indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
				}
		{}

		/**
		 * @brief Sets the progress of the DefaultProgressBar.
		 *
		 * This function sets the progress of the DefaultProgressBar to the specified value.
		 *
		 * @param new_progress The new progress value to set.
		 */
		void setProgress(size_t new_progress) override
		{
			bar.set_progress(new_progress);
		}

		/**
		 * @fn void setOption(const indicators::details::Setting<std::string, indicators::details::ProgressBarOption::postfix_text> &setting)
		 *
		 * @brief Sets an option for the DefaultProgressBar.
		 *
		 * This function sets an option for the DefaultProgressBar using the given setting parameter.
		 *
		 * @param setting The setting to apply to the DefaultProgressBar.
		 *
		 * @see `indicators::details::Setting`, `indicators::details::ProgressBarOption::postfix_text`
		 */
		void setOption(const indicators::details::Setting<std::string, indicators::details::ProgressBarOption::postfix_text> &setting) override
		{
			bar.set_option(setting);
		}

	private:
		indicators::ProgressBar bar;
	};
}
#endif //QRZ_DEFAULTPROGRESSBAR_H
