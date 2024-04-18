#ifndef HAMILTON_CALLSIGNMARSHALER_H
#define HAMILTON_CALLSIGNMARSHALER_H

#include <vector>

#include <tabulate/table.hpp>

#include "Callsign.h"

namespace qrz
{
	class CallsignMarshaler
	{
	public:
		static Callsign FromXml(const std::string &xml_str);
		static std::string ToXML(const std::vector<Callsign> &callsign);
	};
}

#endif //HAMILTON_CALLSIGNMARSHALER_H
