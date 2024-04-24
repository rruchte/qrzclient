#ifndef QRZ_CALLSIGN_H
#define QRZ_CALLSIGN_H

#include <string>

namespace qrz
{
	class Callsign
	{
	public:
		// Constructor
		Callsign() = default;


		/**
		 * @brief Gets the callsign.
		 *
		 * @return const std::string& The callsign.
		 *
		 * This function returns a constant reference to the callsign.
		 * This function returns a constant reference to the callsign.
		 */
		const std::string &getCall() const
		{
			return m_call;
		}


		/**
		 * @brief Sets the callsign.
		 *
		 * @param call The callsign to set.
		 *
		 * This function sets the callsign to the given value.
		 */
		void setCall(const std::string &call)
		{
			m_call = call;
		}

		/**
		 * @brief Gets the cross reference callsign.
		 *
		 * @return const std::string& The cross reference callsign.
		 *
		 * This function returns a constant reference to the cross reference callsign.
		 * The cross reference callsign is the query callsign that returned this record.
		 * If there is no cross reference callsign, an empty string is returned.
		 */
		const std::string &getXref() const
		{
			return m_xref;
		}

		/**
		 * @brief Sets the cross reference callsign.
		 *
		 * @param xref The cross reference callsign to set.
		 *
		 * This function sets the cross reference callsign to the given value.
		 * The cross reference callsign is the query callsign that returned this record.
		 */
		void setXref(const std::string &xref)
		{
			m_xref = xref;
		}

		/**
		 * @brief Get the other callsigns that resolve to this record.
		 *
		 * @return const std::string& The other callsigns.
		 *
		 * This function returns a constant reference to the other callsigns that resolve to this record.
		 */
		const std::string &getAliases() const
		{
			return m_aliases;
		}

		/**
		 * @brief Sets the other callsigns that resolve to this record.
		 *
		 * @param aliases The other callsigns to set.
		 *
		 * This function sets the other callsigns that resolve to this record to the given value.
		 */
		void setAliases(const std::string &aliases)
		{
			m_aliases = aliases;
		}

		/**
		 * @brief Getter function for the DXCC.
		 *
		 * This function returns a constant reference to the DXCC (DX Century Club) code.
		 *
		 * @return A constant reference to the DXCC code.
		 */
		const std::string &getDxcc() const
		{
			return m_dxcc;
		}

		/**
		 * @brief Sets the DXCC value.
		 *
		 * This function sets the DXCC value to the given value.
		 *
		 * @param dxcc The DXCC value to be set.
		 *
		 * @return None.
		 */
		void setDxcc(const std::string &dxcc)
		{
			m_dxcc = dxcc;
		}

		const std::string &getFname() const
		{
			return m_fname;
		}

		void setFname(const std::string &fname)
		{
			m_fname = fname;
		}

		const std::string &getName() const
		{
			return m_name;
		}

		void setName(const std::string &name)
		{
			m_name = name;
		}

		const std::string &getAddr1() const
		{
			return m_addr1;
		}

		void setAddr1(const std::string &addr1)
		{
			m_addr1 = addr1;
		}

		const std::string &getAddr2() const
		{
			return m_addr2;
		}

		void setAddr2(const std::string &addr2)
		{
			m_addr2 = addr2;
		}

		const std::string &getState() const
		{
			return m_state;
		}

		void setState(const std::string &state)
		{
			m_state = state;
		}

		const std::string &getZip() const
		{
			return m_zip;
		}

		void setZip(const std::string &zip)
		{
			m_zip = zip;
		}

		const std::string &getCountry() const
		{
			return m_country;
		}

		void setCountry(const std::string &country)
		{
			m_country = country;
		}

		const std::string &getCcode() const
		{
			return m_ccode;
		}

		void setCcode(const std::string &ccode)
		{
			m_ccode = ccode;
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

		const std::string &getGrid() const
		{
			return m_grid;
		}

		void setGrid(const std::string &grid)
		{
			m_grid = grid;
		}

		const std::string &getCounty() const
		{
			return m_county;
		}

		void setCounty(const std::string &county)
		{
			m_county = county;
		}

		const std::string &getFips() const
		{
			return m_fips;
		}

		void setFips(const std::string &fips)
		{
			m_fips = fips;
		}

		const std::string &getLand() const
		{
			return m_land;
		}

		void setLand(const std::string &land)
		{
			m_land = land;
		}

		const std::string &getEfdate() const
		{
			return m_efdate;
		}

		void setEfdate(const std::string &efdate)
		{
			m_efdate = efdate;
		}

		const std::string &getExpdate() const
		{
			return m_expdate;
		}

		void setExpdate(const std::string &expdate)
		{
			m_expdate = expdate;
		}

		const std::string &getPcall() const
		{
			return m_pcall;
		}

		void setPcall(const std::string &pcall)
		{
			m_pcall = pcall;
		}

		const std::string &getClass() const
		{
			return m_class;
		}

		void setClass(const std::string &licClass)
		{
			m_class = licClass;
		}

		const std::string &getCodes() const
		{
			return m_codes;
		}

		void setCodes(const std::string &codes)
		{
			m_codes = codes;
		}

		const std::string &getQslmgr() const
		{
			return m_qslmgr;
		}

		void setQslmgr(const std::string &qslmgr)
		{
			m_qslmgr = qslmgr;
		}

		const std::string &getEmail() const
		{
			return m_email;
		}

		void setEmail(const std::string &email)
		{
			m_email = email;
		}

		const std::string &getUrl() const
		{
			return m_url;
		}

		void setUrl(const std::string &url)
		{
			m_url = url;
		}

		const std::string getUViews() const
		{
			return m_u_views;
		}

		void setUViews(std::string mUViews)
		{
			m_u_views = mUViews;
		}

		const std::string getBio() const
		{
			return m_bio;
		}

		void setBio(std::string bio)
		{
			m_bio = bio;
		}

		const std::string &getBiodate() const
		{
			return m_biodate;
		}

		void setBiodate(const std::string &biodate)
		{
			m_biodate = biodate;
		}

		const std::string &getImage() const
		{
			return m_image;
		}

		void setImage(const std::string &image)
		{
			m_image = image;
		}

		const std::string &getImageinfo() const
		{
			return m_imageinfo;
		}

		void setImageinfo(const std::string &imageinfo)
		{
			m_imageinfo = imageinfo;
		}

		const std::string &getSerial() const
		{
			return m_serial;
		}

		void setSerial(const std::string &serial)
		{
			m_serial = serial;
		}

		const std::string &getModdate() const
		{
			return m_moddate;
		}

		void setModdate(const std::string &moddate)
		{
			m_moddate = moddate;
		}

		const std::string getMsa() const
		{
			return m_MSA;
		}

		void setMsa(std::string mMsa)
		{
			m_MSA = mMsa;
		}

		const std::string getAreaCode() const
		{
			return m_AreaCode;
		}

		void setAreaCode(std::string mAreaCode)
		{
			m_AreaCode = mAreaCode;
		}

		const std::string &getTimeZone() const
		{
			return m_TimeZone;
		}

		void setTimeZone(const std::string &timeZone)
		{
			m_TimeZone = timeZone;
		}

		int getGmtOffset() const
		{
			return m_GMTOffset;
		}

		void setGmtOffset(int mGmtOffset)
		{
			m_GMTOffset = mGmtOffset;
		}

		const std::string &getDst() const
		{
			return m_DST;
		}

		void setDst(const std::string &dst)
		{
			m_DST = dst;
		}

		const std::string &getEqsl() const
		{
			return m_eqsl;
		}

		void setEqsl(const std::string &eqsl)
		{
			m_eqsl = eqsl;
		}

		const std::string &getMqsl() const
		{
			return m_mqsl;
		}

		void setMqsl(const std::string &mqsl)
		{
			m_mqsl = mqsl;
		}

		int getCqzone() const
		{
			return m_cqzone;
		}

		void setCqzone(int mCqzone)
		{
			m_cqzone = mCqzone;
		}

		int getItuzone() const
		{
			return m_ituzone;
		}

		void setItuzone(int mItuzone)
		{
			m_ituzone = mItuzone;
		}

		const std::string &getBorn() const
		{
			return m_born;
		}

		void setBorn(const std::string &born)
		{
			m_born = born;
		}

		const std::string &getUser() const
		{
			return m_user;
		}

		void setUser(const std::string &user)
		{
			m_user = user;
		}

		const std::string &getLotw() const
		{
			return m_lotw;
		}

		void setLotw(const std::string &lotw)
		{
			m_lotw = lotw;
		}

		const std::string &getIota() const
		{
			return m_iota;
		}

		void setIota(const std::string &iota)
		{
			m_iota = iota;
		}

		const std::string &getGeoloc() const
		{
			return m_geoloc;
		}

		void setGeoloc(const std::string &geoloc)
		{
			m_geoloc = geoloc;
		}

		const std::string &getAttn() const
		{
			return m_attn;
		}

		void setAttn(const std::string &attn)
		{
			m_attn = attn;
		}

		const std::string &getNickname() const
		{
			return m_nickname;
		}

		void setNickname(const std::string &nickname)
		{
			m_nickname = nickname;
		}

		const std::string &getNameFmt() const
		{
			return m_name_fmt;
		}

		void setNameFmt(const std::string &nameFmt)
		{
			m_name_fmt = nameFmt;
		}

	private:
		// Callsign
		std::string m_call;

		// Cross reference: the query callsign that returned this record
		std::string m_xref;

		// Other callsigns that resolve to this record
		std::string m_aliases;

		// DXCC entity ID (country code) for the callsign
		std::string m_dxcc;

		// First name
		std::string m_fname;

		// Last name
		std::string m_name;

		// Address line 1 (i.e. house # and street)
		std::string m_addr1;

		// Address line 2 (i.e, city name)
		std::string m_addr2;

		// State (USA Only)
		std::string m_state;

		// Zip/postal code
		std::string m_zip;

		// Country name for the QSL mailing address
		std::string m_country;

		// dxcc entity code for the mailing address country
		std::string m_ccode;

		// Latitude of address (signed decimal) S < 0 > N
		std::string m_lat;

		// Longitude of address (signed decimal) W < 0 > E
		std::string m_lon;

		// Grid locator
		std::string m_grid;

		// County name (USA)
		std::string m_county;

		// FIPS county identifier (USA)
		std::string m_fips;

		// XCC country name of the callsign
		std::string m_land;

		// License effective date (USA)
		std::string m_efdate;

		// License expiration date (USA)
		std::string m_expdate;

		// Previous callsign
		std::string m_pcall;

		// License class
		std::string m_class;

		// License type codes (USA)
		std::string m_codes;

		// QSL manager info
		std::string m_qslmgr;

		// Email address
		std::string m_email;

		// Web page address
		std::string m_url;

		// QRZ web page views
		std::string m_u_views;

		// Approximate length of the bio HTML in bytes
		std::string m_bio;

		// Date of the last bio update
		std::string m_biodate;

		// Full URL of the callsign's primary image
		std::string m_image;

		// height:width:size in bytes, of the image file
		std::string m_imageinfo;

		// QRZ db serial number
		std::string m_serial;

		// QRZ callsign last modified date
		std::string m_moddate;

		// Metro Service Area (USPS)
		std::string m_MSA;

		// Telephone Area Code (USA)
		std::string m_AreaCode;

		// Time Zone (USA)
		std::string m_TimeZone;

		// GMT Time Offset
		int m_GMTOffset;

		// Daylight Saving Time Observed
		std::string m_DST;

		// Will accept e-qsl (0/1 or blank if unknown)
		std::string m_eqsl;

		// Will return paper QSL (0/1 or blank if unknown)
		std::string m_mqsl;

		// CQ Zone identifier
		int m_cqzone;

		// ITU Zone identifier
		int m_ituzone;

		// Operator's year of birth
		std::string m_born;

		// User who manages this callsign on QRZ
		std::string m_user;

		// Will accept LOTW (0/1 or blank if unknown)
		std::string m_lotw;

		// IOTA Designator (blank if unknown)
		std::string m_iota;

		// Describes source of lat/long data
		std::string m_geoloc;

		// Attention address line, this line should be prepended to the address
		std::string m_attn;

		// A different or shortened name used on the air
		std::string m_nickname;

		// Combined full name and nickname in the format used by QRZ. This format is subject to change.
		std::string m_name_fmt;
	};
}
#endif //QRZ_CALLSIGN_H