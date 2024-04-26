#ifndef QRZ_DXCC_H
#define QRZ_DXCC_H

#include <string>

namespace qrz
{
	class DXCC
	{
	public:
		DXCC() = default;

		/**
		 * @brief Get the DXCC entity number.
		 *
		 * This function returns the DXCC entity number for the record.
		 *
		 * @return const std::string& The DXCC entity number.
		 */
		const std::string &getDxcc() const
		{
			return m_dxcc;
		}

		/**
		 * @brief Set the DXCC entity number.
		 *
		 * This function sets the DXCC entity number for the record.
		 *
		 * @param dxcc The DXCC entity number to set.
		 */
		void setDxcc(const std::string &dxcc)
		{
			m_dxcc = dxcc;
		}

		/**
		 * @brief Get the 2-letter country code (ISO-3166).
		 *
		 * This function returns the 2-letter country code.
		 * The country code is based on ISO-3166 standards.
		 *
		 * @return const std::string& The 2-letter country code.
		 */
		const std::string &getCc() const
		{
			return m_cc;
		}

		/**
		 * @brief Set the 2-letter country code (ISO-3166).
		 *
		 * This function sets the 2-letter country code (ISO-3166).
		 *
		 * @param cc The 2-letter country code to set.
		 */
		void setCc(const std::string &cc)
		{
			m_cc = cc;
		}

		/**
		 * @brief Get the 3-letter country code (ISO-3166).
		 *
		 * This function returns the 3-letter country code.
		 * The country code is based on ISO-3166 standards.
		 *
		 * @return const std::string& The 3-letter country code.
		 */
		const std::string &getCcc() const
		{
			return m_ccc;
		}

		/**
		 * @brief Set the 3-letter country code (ISO-3166).
		 *
		 * This function sets the 3-letter country code (ISO-3166).
		 *
		 * @param cc The 3-letter country code to set.
		 */
		void setCcc(const std::string &cc)
		{
			m_cc = cc;
		}

		/**
		 * @brief Get the name.
		 *
		 * This function returns the name.
		 *
		 * @return const std::string& The name.
		 */
		const std::string &getName() const
		{
			return m_name;
		}

		/**
		 * @brief Set the name.
		 *
		 * This function sets the name.
		 *
		 * @param name The name to set.
		 */
		void setName(const std::string &name)
		{
			m_name = name;
		}

		/**
		 * @brief Get the continent.
		 *
		 * This function returns the continent.
		 * The continent is represented by a 2-letter designator.
		 *
		 * @return const std::string& The continent.
		 */
		const std::string &getContinent() const
		{
			return m_continent;
		}

		/**
		 * @brief Set the continent.
		 *
		 * This function sets the continent.
		 *
		 * @param continent The continent to set.
		 */
		void setContinent(const std::string &continent)
		{
			m_continent = continent;
		}

		/**
		 * @brief Get the ITU Zone.
		 *
		 * This function returns the ITU Zone.
		 *
		 * @return const std::string& The ITU Zone.
		 */
		const std::string &getItuzone() const
		{
			return m_ituzone;
		}

		/**
		 * @brief Set the ITU Zone.
		 *
		 * This function sets the ITU Zone.
		 *
		 * @param ituzone The ITU Zone to set.
		 */
		void setItuzone(const std::string &ituzone)
		{
			m_ituzone = ituzone;
		}

		/**
		 * @brief Get the CQ Zone.
		 *
		 * This function returns the CQ Zone.
		 *
		 * @return const std::string& The CQ Zone.
		 */
		const std::string &getCqzone() const
		{
			return m_cqzone;
		}

		/**
		 * @brief Set the CQ Zone.
		 *
		 * This function sets the CQ Zone.
		 *
		 * @param cqzone The CQ Zone to set.
		 */
		void setCqzone(const std::string &cqzone)
		{
			m_cqzone = cqzone;
		}

		/**
		 * @brief Get the UTC timezone offset.
		 *
		 * This function returns the UTC timezone offset.
		 * The offset represents the time difference between UTC and the local time in the DXCC entity.
		 *
		 * @return const std::string& The UTC timezone offset.
		 */
		const std::string &getTimezone() const
		{
			return m_timezone;
		}

		/**
		 * @brief Set the UTC timezone offset.
		 *
		 * This function sets the UTC timezone offset.
		 * The offset represents the time difference between UTC and the local time in the DXCC entity.
		 *
		 * @param timezone The UTC timezone offset to set.
		 */
		void setTimezone(const std::string &timezone)
		{
			m_timezone = timezone;
		}

		/**
		 * @brief Get the latitude.
		 *
		 * This function returns the latitude.
		 * The latitude is an approximate value.
		 *
		 * @return const std::string& The latitude.
		 */
		const std::string &getLat() const
		{
			return m_lat;
		}

		/**
		 * @brief Set the latitude.
		 *
		 * This function sets the latitude. The latitude is represented as a string and is used to store an approximate value.
		 *
		 * @param lat The latitude to set.
		 */
		void setLat(const std::string &lat)
		{
			m_lat = lat;
		}

		/**
		 * @brief Get the longitude.
		 *
		 * This function returns the longitude.
		 * The longitude is an approximate value.
		 *
		 * @return const std::string& The longitude.
		 */
		const std::string &getLon() const
		{
			return m_lon;
		}

		/**
		 * @brief Set the longitude.
		 *
		 * This function sets the longitude. The longitude is represented as a string and is used to store an approximate value.
		 *
		 * @param lon The longitude to set.
		 */
		void setLon(const std::string &lon)
		{
			m_lon = lon;
		}

		/**
		 * @brief Get the special notes and/or exceptions.
		 *
		 * This function returns the special notes and/or exceptions.
		 *
		 * @return const std::string& The special notes and/or exceptions.
		 */
		const std::string &getNotes() const
		{
			return m_notes;
		}

		/**
		 * @brief Set the special notes and/or exceptions.
		 *
		 * This function sets the special notes and/or exceptions.
		 *
		 * @param notes The special notes and/or exceptions to set.
		 */
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

#endif //QRZ_DXCC_H
