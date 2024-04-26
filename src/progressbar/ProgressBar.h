//
// Created by rob on 4/22/24.
//

#ifndef QRZ_PROGRESSBAR_H
#define QRZ_PROGRESSBAR_H

#include <string>

#include "indicators/setting.hpp"

namespace qrz
{
	/**
	 * @class ProgressBar
	 * @brief Represents a progress bar.
	 *
	 * This class provides an interface for implementing progress bars.
	 */
	class ProgressBar
	{
	public:
		virtual ~ProgressBar() = default;
		virtual void setProgress(size_t new_progress) = 0;
		virtual void setOption(const indicators::details::Setting<std::string, indicators::details::ProgressBarOption::postfix_text> &setting) = 0;
	};
}
#endif //QRZ_PROGRESSBAR_H
