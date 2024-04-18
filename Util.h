#ifndef QRZ_UTIL_H
#define QRZ_UTIL_H

#include <string>
#include <vector>

namespace qrz
{
	extern void SetStdinEcho(bool enable = true);
	extern void ToLower(std::string &input);
	extern void ToUpper(std::string &input);
	extern std::string VectorToCSV(const std::vector<std::string> &vec);
}

#endif //QRZ_UTIL_H
