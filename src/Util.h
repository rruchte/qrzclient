#ifndef QRZ_UTIL_H
#define QRZ_UTIL_H

#include <string>
#include <vector>

namespace qrz
{
	/**
	 * @brief Sets whether to echo input from stdin.
	 *
	 * This function allows you to control whether input from stdin is echoed or not.
	 * By default, input from stdin is echoed.
	 *
	 * @param enable A boolean value indicating whether to enable or disable echoing of input from stdin. Default value is true.
	 *
	 * @warning If this function is used to disable echo input, the input will not be visible in the console/terminal as it is typed.
	 */
	extern void SetStdinEcho(bool enable = true);

	/**
	 * @brief Convert a string to lowercase.
	 *
	 * This function modifies the input string by converting all characters to lowercase.
	 * The modification is done in-place, meaning that the original string is modified directly.
	 *
	 * @param[in,out] input The string to be converted to lowercase.
	 *
	 */
	extern void ToLower(std::string &input);

	/**
	 * @brief Convert a string to uppercase.
	 *
	 * This function modifies the input string by converting all characters to uppercase.
	 * The modification is done in-place, meaning that the original string is modified directly.
	 *
	 * @param[in,out] input The string to be converted to uppercase.
	 *
	 */
	extern void ToUpper(std::string &input);

	/**
	 * Convert a vector of strings to a CSV string.
	 *
	 * This function takes in a vector of strings and converts it into a CSV (Comma Separated Values) string. Each element in the vector is treated as a separate field, and the fields are separated by commas. If a field contains a double quote character, it is escaped by doubling it. The resulting CSV string is enclosed in double quotes.
	 *
	 * @param vec The vector of strings to convert to CSV.
	 * @return The CSV string representation of the vector.
	 */
	extern std::string VectorToCSV(const std::vector<std::string> &vec);
}

#endif //QRZ_UTIL_H
