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
	void ToUpper(std::string &input)
	{
		std::for_each(std::begin(input), std::end(input), [](char &c)
		{
			c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
		});
	}

	void ToLower(std::string &input)
	{
		std::for_each(std::begin(input), std::end(input), [](char &c)
		{
			c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		});
	}

	void SetStdinEcho(bool enable = true)
	{
#ifdef WIN32
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);

		if( !enable )using namespace qrz;
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