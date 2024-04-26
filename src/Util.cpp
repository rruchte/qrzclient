#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace qrz
{
	/**
	 * @brief Converts all characters in a given string to uppercase.
	 *
	 * This function takes a string as input and converts all its characters to uppercase.
	 * It uses the std::for_each function to iterate over each character in the string and
	 * applies a lambda function that converts each character to uppercase using std::toupper.
	 *
	 * @param input The string to be converted to uppercase.
	 */
	void ToUpper(std::string &input)
	{
		std::for_each(std::begin(input), std::end(input), [](char &c)
		{
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		});
	}

	/**
	 * @brief Converts all characters in a given string to lowercase.
	 *
	 * This function takes a string as input and converts all its characters to lowercase.
	 * It uses the std::for_each function to iterate over each character in the string and
	 * applies a lambda function that converts each character to lowercase using std::tolower.
	 *
	 * @param input The string to be converted to lowercase.
	 */
	void ToLower(std::string &input)
	{
		std::for_each(std::begin(input), std::end(input), [](char &c)
		{
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		});
	}

	/**
	 * @brief Sets whether to echo input from stdin.
	 *
	 * This function allows you to control whether input from stdin is echoed or not.
	 * By default, input from stdin is echoed.
	 *
	 * @param enable A boolean value indicating whether to enable or disable echoing of input from stdin. Default value is true.
	 *
	 * @note This function is platform-dependent. On Windows, it uses the WinAPI to modify the console mode to enable/disable echo input. On non-Windows systems, it uses termios to modify the terminal settings to enable/disable echo input.
	 */
	void SetStdinEcho(bool enable = true)
	{
#ifdef WIN32
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);

		if( !enable )
			mode &= ~ENABLE_ECHO_INPUT;
		else
			mode |= ENABLE_ECHO_INPUT;

		SetConsoleMode(hStdin, mode );

#else
		struct termios tty;
		tcgetattr(STDIN_FILENO, &tty);
		if (!enable)
			tty.c_lflag &= ~ECHO;
		else
			tty.c_lflag |= ECHO;

		(void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
	}

	/**
	 * @brief Convert a vector of strings to a comma-separated value (CSV) string.
	 *
	 * This function takes a vector of strings and converts it into a single string in comma-separated value format.
	 * Each element of the vector is enclosed in double quotes, and if any element contains a double quote character,
	 * it is escaped by doubling it. The resulting string is then returned.
	 *
	 * @param vec The vector of strings to convert to CSV format.
	 * @return std::string The string in CSV format.
	 */
	std::string VectorToCSV(const std::vector<std::string>& vec)
	{
		std::stringstream ss;

		for(size_t i = 0; i < vec.size(); ++i)
		{
			std::string field = vec[i];

			// Check if the string contains a " character
			size_t find_result = field.find("\"");

			// If a " character is found, replace it in the string
			while(find_result != std::string::npos)
			{
				field.replace(find_result, 1, "\"\"");
				find_result = field.find("\"", find_result + 2);
			}

			// Enclose fields in double quotes
			ss << '\"' << field << '\"';

			if(i != vec.size() - 1)  // do not add a comma after the last element
				ss << ',';
		}

		return ss.str();
	}
}