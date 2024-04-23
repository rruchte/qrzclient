#ifndef QRZ_DXCCMARSHALER_H
#define QRZ_DXCCMARSHALER_H

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

#endif //QRZ_DXCCMARSHALER_H
