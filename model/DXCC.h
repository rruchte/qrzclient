#ifndef HAMILTON_DXCC_H
#define HAMILTON_DXCC_H

#include <string>

namespace qrz
{
	class DXCC
	{
	public:
		DXCC() = default;

		const std::string &getDxcc() const
		{
			return m_dxcc;
		}

		void setDxcc(const std::string &dxcc)
		{
			m_dxcc = dxcc;
		}

		const std::string &getCc() const
		{
			return m_cc;
		}

		void setCc(const std::string &cc)
		{
			m_cc = cc;
		}

		const std::string &getCcc() const
		{
			return m_ccc;
		}

		void setCcc(const std::string &cc)
		{
			m_cc = cc;
		}

		const std::string &getName() const
		{
			return m_name;
		}

		void setName(const std::string &name)
		{
			m_name = name;
		}

		const std::string &getContinent() const
		{
			return m_continent;
		}

		void setContinent(const std::string &continent)
		{
			m_continent = continent;
		}

		const std::string &getItuzone() const
		{
			return m_ituzone;
		}

		void setItuzone(const std::string &ituzone)
		{
			m_ituzone = ituzone;
		}

		const std::string &getCqzone() const
		{
			return m_cqzone;
		}

		void setCqzone(const std::string &cqzone)
		{
			m_cqzone = cqzone;
		}

		const std::string &getTimezone() const
		{
			return m_timezone;
		}

		void setTimezone(const std::string &timezone)
		{
			m_timezone = timezone;
		}

		const std::string &getLat() const
		{
			return m_lat;
		}

		void setLat(const std::string &lat)
		{
			m_lat = lat;
		}

		const std::string &getLon() const
		{
			return m_lon;
		}

		void setLon(const std::string &lon)
		{
			m_lon = lon;
		}

		const std::string &getNotes() const
		{
			return m_notes;
		}

		void setNotes(const std::string &notes)
		{
			m_notes = notes;
		}

	private:
		// DXCC entity number for this record
		std::string m_dxcc;

		// 2-letter country code (ISO-3166)c;
		std::string m_cc;

		// 3-letter country code (ISO-3166)
		std::string m_ccc;

		// long name
		std::string m_name;

		// 2-letter continent designator
		std::string m_continent;

		// ITU Zone;
		std::string m_ituzone;

		// CQ Zone;
		std::string m_cqzone;

		// UTC timezone offset +/-
		std::string m_timezone;

		// Latitude (approx.)zone;
		std::string m_lat;

		// Longitude (approx.)
		std::string m_lon;

		// Special notes and/or exceptions
		std::string m_notes;
	};
}

#endif //HAMILTON_DXCC_H
