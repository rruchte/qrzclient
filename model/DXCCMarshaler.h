#ifndef HAMILTON_DXCCMARSHALER_H
#define HAMILTON_DXCCMARSHALER_H

#include <vector>

#include "DXCC.h"

namespace qrz
{
	class DXCCMarshaler
	{
	public:
		static DXCC FromXml(const std::string &xml_str);
		static std::string ToXML(const std::vector<DXCC> &dxccList);
	};
}

#endif //HAMILTON_DXCCMARSHALER_H
