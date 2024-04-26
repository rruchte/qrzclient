#ifndef QRZ_OUTPUTFORMAT_H
#define QRZ_OUTPUTFORMAT_H

namespace qrz
{
	/**
	 * @brief Define the possible output formats that the AppController supports
	 */
	enum OutputFormat
	{
		CONSOLE,
		CSV,
		JSON,
		MD,
		XML
	};
}

#endif //QRZ_OUTPUTFORMAT_H