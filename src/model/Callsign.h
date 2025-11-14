#ifndef QRZ_CALLSIGN_H
#define QRZ_CALLSIGN_H

#include <string>

namespace qrz
{
	/**
	 * @class Callsign
	 *
	 * @brief The Callsign class represents a radio callsign.
	 *
	 * A callsign is a unique identifier assigned to a radio station or operator.
	 * This class provides methods to get and set the various properties of a callsign.
	 */
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
		 * This function sets the other callsigns that resolve to this record to the given value.
		 *
		 * @param aliases A reference to a string containing the the other callsigns that resolve to this record.
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
		 * @param dxcc A reference to a string containing the DXCC value to be set.
		 *
		 * @return None.
		 */
		void setDxcc(const std::string &dxcc)
		{
			m_dxcc = dxcc;
		}

		/**
		 * @brief Returns the value of the First name
		 *
		 * This function returns a constant reference to the First name.
		 *
		 * @return const std::string& for the First name.
		 */
		const std::string &getFname() const
		{
			return m_fname;
		}

		/**
		 * @brief Sets the first name.
		 *
		 * This function sets the first name to the given value.
		 *
		 * @param fname A reference to a string containing the first name to be set.
		 */
		void setFname(const std::string &fname)
		{
			m_fname = fname;
		}

		/**
		 * @brief Returns the value of the Last name
		 *
		 * This function returns a constant reference to the Last name.
		 *
		 * @return const std::string& for the Last name.
		 */
		const std::string &getName() const
		{
			return m_name;
		}

		/**
		 * @brief Sets the last name.
		 *
		 * This function sets the last name to the given value.
		 *
		 * @param name A reference to a string containing the last name to be set.
		 */
		void setName(const std::string &name)
		{
			m_name = name;
		}

		/**
		 * @brief Returns the value of the Address line 1
		 *
		 * This function returns a constant reference to the Address line 1 (i.e. house # and street).
		 *
		 * @return const std::string& for the Address line 1.
		 */
		const std::string &getAddr1() const
		{
			return m_addr1;
		}

		/**
		 * @brief Sets the Address line 1.
		 *
		 * This function sets the Address line 1 (i.e. house # and street) to the given value.
		 *
		 * @param fname A reference to a string containing the Address line 1 to be set.
		 */
		void setAddr1(const std::string &addr1)
		{
			m_addr1 = addr1;
		}

		/**
		 * @brief Returns the value of the Address line 2.
		 *
		 * This function returns a constant reference to the Address line 2 (i.e, city name).
		 *
		 * @return const std::string& for the Address line 2.
		 */
		const std::string &getAddr2() const
		{
			return m_addr2;
		}

		/**
		 * @brief Sets the Address line 2.
		 *
		 * This function sets the Address line 2 (i.e, city name) to the given value.
		 *
		 * @param fname A reference to a string containing the Address line 2 to be set.
		 */
		void setAddr2(const std::string &addr2)
		{
			m_addr2 = addr2;
		}

		/**
		 * @brief Returns the value of the Address line 2.
		 *
		 * This function returns a constant reference to the Address line 2 (i.e, city name).
		 *
		 * @return const std::string& for the Address line 2.
		 */
		const std::string &getCity() const
		{
			return m_city;
		}

		/**
		 * @brief Sets the Address line 2.
		 *
		 * This function sets the Address line 2 (i.e, city name) to the given value.
		 *
		 * @param fname A reference to a string containing the Address line 2 to be set.
		 */
		void setCity(const std::string &city)
		{
			m_city = city;
		}

		/**
		 * @brief Returns the value of the State.
		 *
		 * This function returns a constant reference to the State (USA Only).
		 *
		 * @return const std::string& for the the State.
		 */
		const std::string &getState() const
		{
			return m_state;
		}

		/**
		 * @brief Sets the State.
		 *
		 * This function sets the State (USA Only).
		 *
		 * @param fname A reference to a string containing the State to be set.
		 */
		void setState(const std::string &state)
		{
			m_state = state;
		}

		/**
		 * @brief Returns the value of the Zip/postal code.
		 *
		 * This function returns a constant reference to the Zip/postal code.
		 *
		 * @return const std::string& The Zip/postal code.
		 */
		const std::string &getZip() const
		{
			return m_zip;
		}

		/**
		 * @brief Sets the Zip/postal code.
		 *
		 * This function sets the Zip/postal code.
		 *
		 * @param fname A reference to a string containing the Zip/postal code to be set.
		 */
		void setZip(const std::string &zip)
		{
			m_zip = zip;
		}

		/**
		 * @brief Returns the value of the country name.
		 *
		 * This function returns a constant reference to the Country name for the QSL mailing address.
		 *
		 * @return const std::string& The country name.
		 */
		const std::string &getCountry() const
		{
			return m_country;
		}

		/**
		 * @brief Sets the Country name.
		 *
		 * This function sets the Country name for the QSL mailing address.
		 *
		 * @param fname A reference to a string containing the Country name to be set.
		 *
		 * @return void
		 */
		void setCountry(const std::string &country)
		{
			m_country = country;
		}

		/**
		 * @brief Retrieves the DXCC entity code.
		 *
		 * This function returns a constant reference to the dxcc entity code for the mailing address country.
		 *
		 * @return const std::string& The dxcc entity code string.
		 */
		const std::string &getCcode() const
		{
			return m_ccode;
		}

		/**
		 * @brief Sets the DXCC entity code.
		 *
		 * This function sets the DXCC entity code.
		 *
		 * @param ccode A reference to a string containing the DXCC entity code.
		 *
		 * @return void
		 */
		void setCcode(const std::string &ccode)
		{
			m_ccode = ccode;
		}

		/**
		 * @brief Retrieves the latitude of address.
		 *
		 * This function returns a constant reference to the Latitude of address (signed decimal) S < 0 > N.
		 *
		 * @return const std::string& The latitude string.
		 */
		const std::string &getLat() const
		{
			return m_lat;
		}

		/**
		 * Sets the latitude value.
		 *
		 * @param lat The latitude value to be set.
		 *
		 * @return void
		 */
		void setLat(const std::string &lat)
		{
			m_lat = lat;
		}

		/**
		 * @brief Retrieves the longitude of address.
		 *
		 * This function returns a constant reference to the Longitude of address (signed decimal) W < 0 > E.
		 *
		 * @return const std::string& The longitude string.
		 */
		const std::string &getLon() const
		{
			return m_lon;
		}

		/**
		 * Sets the longitude value.
		 *
		 * @param lon The longitude value to be set.
		 *
		 * @return void
		 */
		void setLon(const std::string &lon)
		{
			m_lon = lon;
		}

		/**
		 * @brief Retrieves the grid locator.
		 *
		 * This function returns a constant reference to the maidenhead grid locator.
		 *
		 * @return const std::string& The grid locator string.
		 */
		const std::string &getGrid() const
		{
			return m_grid;
		}

		/**
		 * Sets the maidenhead grid value.
		 *
		 * @param grid The maidenhead grid value to be set.
		 *
		 * @return void
		 */
		void setGrid(const std::string &grid)
		{
			m_grid = grid;
		}

		/**
		 * @brief Retrieves the county name.
		 *
		 * This function returns a constant reference to the county name.
		 *
		 * @return const std::string& The county name string.
		 */
		const std::string &getCounty() const
		{
			return m_county;
		}

		/**
		 * Sets the county value.
		 *
		 * @param county The county value to be set.
		 *
		 * @return void
		 */
		void setCounty(const std::string &county)
		{
			m_county = county;
		}


		/**
		 * @brief Retrieves the FIPS country identifier.
		 *
		 * This function returns a constant reference to the FIPS country identifier.
		 *
		 * @return const std::string& The FIPS country identifier string.
		 */
		const std::string &getFips() const
		{
			return m_fips;
		}

		/**
		 * Sets the FIPS country identifier value.
		 *
		 * @param filps The FIPS country identifier value to be set.
		 *
		 * @return void
		 */
		void setFips(const std::string &fips)
		{
			m_fips = fips;
		}

		/**
		 * @brief Retrieves the XCC country name.
		 *
		 * This function returns a constant reference to the XCC country name of the callsign.
		 *
		 * @return const std::string& The XCC country name string.
		 */
		const std::string &getLand() const
		{
			return m_land;
		}

		/**
		 * Sets the XCC country name value.
		 *
		 * @param land The XCC country name value to be set.
		 *
		 * @return void
		 */
		void setLand(const std::string &land)
		{
			m_land = land;
		}

		/**
		 * @brief Retrieves the License effective date (USA).
		 *
		 * This function returns a constant reference to the License effective date (USA).
		 *
		 * @return const std::string& The License effective date string.
		 */
		const std::string &getEfdate() const
		{
			return m_efdate;
		}

		/**
		 * Sets the License effective date value.
		 *
		 * @param efdate The License effective date (USA) value to be set.
		 *
		 * @return void
		 */
		void setEfdate(const std::string &efdate)
		{
			m_efdate = efdate;
		}

		/**
		 * @brief Retrieves the License expiration date (USA).
		 *
		 * This function returns a constant reference to the License expiration date (USA).
		 *
		 * @return const std::string& The License expiration date string.
		 */
		const std::string &getExpdate() const
		{
			return m_expdate;
		}

		/**
		 * Sets the License expiration date (USA) value.
		 *
		 * @param expdate The License expiration date (USA) value to be set.
		 *
		 * @return void
		 */
		void setExpdate(const std::string &expdate)
		{
			m_expdate = expdate;
		}

		/**
		 * @brief Retrieves the Previous callsign.
		 *
		 * This function returns a constant reference to the Previous callsign.
		 *
		 * @return const std::string& The Previous callsign string.
		 */
		const std::string &getPcall() const
		{
			return m_pcall;
		}

		/**
		 * Sets the previous callsign value.
		 *
		 * @param pcall The previous callsign value to be set.
		 *
		 * @return void
		 */
		void setPcall(const std::string &pcall)
		{
			m_pcall = pcall;
		}

		/**
		 * @brief Retrieves the License class.
		 *
		 * This function returns a constant reference to the License class.
		 *
		 * @return const std::string& The License class string.
		 */
		const std::string &getClass() const
		{
			return m_class;
		}

		/**
		 * Sets the license class value.
		 *
		 * @param licClass The license class value to be set.
		 *
		 * @return void
		 */
		void setClass(const std::string &licClass)
		{
			m_class = licClass;
		}

		/**
		 * @brief Retrieves the License type codes (USA).
		 *
		 * This function returns a constant reference to the License type codes (USA).
		 *
		 * @return const std::string& The License type codes string.
		 */
		const std::string &getCodes() const
		{
			return m_codes;
		}

		/**
		 * Sets the License type codes value.
		 *
		 * @param codes The License type codes value to be set.
		 *
		 * @return void
		 */
		void setCodes(const std::string &codes)
		{
			m_codes = codes;
		}

		/**
		 * @brief Retrieves the QSL manager info.
		 *
		 * This function returns a constant reference to the QSL manager info.
		 *
		 * @return const std::string& The QSL manager info string.
		 */
		const std::string &getQslmgr() const
		{
			return m_qslmgr;
		}

		/**
		 * Sets the QSL manager info value.
		 *
		 * @param qslmgr The QSL manager info value to be set.
		 *
		 * @return void
		 */
		void setQslmgr(const std::string &qslmgr)
		{
			m_qslmgr = qslmgr;
		}

		/**
		 * @brief Retrieves the email address.
		 *
		 * This function returns a constant reference to the email address.
		 *
		 * @return const std::string& The email address string.
		 */
		const std::string &getEmail() const
		{
			return m_email;
		}

		/**
		 * Sets the email address value.
		 *
		 * @param email The email address value to be set.
		 *
		 * @return void
		 */
		void setEmail(const std::string &email)
		{
			m_email = email;
		}

		/**
		 * @brief Retrieves the web page address.
		 *
		 * This function returns a constant reference to the web page address.
		 *
		 * @return const std::string& The web page address string.
		 */
		const std::string &getUrl() const
		{
			return m_url;
		}

		/**
		 * Sets the web page address value.
		 *
		 * @param url The web page address value to be set.
		 *
		 * @return void
		 */
		void setUrl(const std::string &url)
		{
			m_url = url;
		}

		/**
		 * @brief Get the UViews value.
		 *
		 * This function returns the QRZ web page views.
		 *
		 * @return int The UViews value.
		 */
		const int getUViews() const
		{
			return m_u_views;
		}

		/**
		 * Sets the UViews value.
		 *
		 * @param mUViews The UViews value to be set.
		 *
		 * @return void
		 */
		void setUViews(int mUViews)
		{
			m_u_views = mUViews;
		}

		/**
		 * @brief Get the Approximate length of the bio HTML in bytes.
		 *
		 * This function returns the Approximate length of the bio HTML in bytes.
		 *
		 * @return int The bio bytes value.
		 */
		int getBio() const
		{
			return m_bio;
		}

		/**
		 * Sets the bio bytes value.
		 *
		 * @param ${param_name} The approximate length of the bio HTML in bytes value to be set.
		 *
		 * @return void
		 */
		void setBio(int bio)
		{
			m_bio = bio;
		}

		/**
		 * @brief Retrieves the Date of the last bio update.
		 *
		 * This function returns a constant reference to the Date of the last bio update.
		 *
		 * @return const std::string& The Date of the last bio update string.
		 */
		const std::string &getBiodate() const
		{
			return m_biodate;
		}

		/**
		 * Sets the date of the last bio update.
		 *
		 * @param biodate The date of the last bio update value to be set.
		 *
		 * @return void
		 */
		void setBiodate(const std::string &biodate)
		{
			m_biodate = biodate;
		}

		/**
		 * @brief Retrieves the Full URL of the callsign's primary image.
		 *
		 * This function returns a constant reference to the Full URL of the callsign's primary image.
		 *
		 * @return const std::string& The Full URL of the callsign's primary image string.
		 */
		const std::string &getImage() const
		{
			return m_image;
		}

		/**
		 * Sets the full URL of the callsign's primary image.
		 *
		 * @param image The full URL of the callsign's primary image value to be set.
		 *
		 * @return void
		 */
		void setImage(const std::string &image)
		{
			m_image = image;
		}

		/**
		 * @brief Retrieves the height:width:size in bytes, of the image file.
		 *
		 * This function returns height:width:size in bytes, of the image file.
		 *
		 * @return const std::string& The height:width:size in bytes, of the image file string.
		 */
		const std::string &getImageinfo() const
		{
			return m_imageinfo;
		}

		void setImageinfo(const std::string &imageinfo)
		{
			m_imageinfo = imageinfo;
		}

		/**
		 * @brief Retrieves the QRZ db serial number.
		 *
		 * This function returns the QRZ db serial number.
		 *
		 * @return const std::string& The QRZ db serial number string.
		 */
		const std::string &getSerial() const
		{
			return m_serial;
		}

		/**
		 * Sets the ${variable_name} value.
		 *
		 * @param ${param_name} The ${variable_name} value to be set.
		 *
		 * @return void
		 */
		void setSerial(const std::string &serial)
		{
			m_serial = serial;
		}

		/**
		 * @brief Retrieves the QRZ callsign last modified date.
		 *
		 * This function returns the QRZ callsign last modified date.
		 *
		 * @return const std::string& The QRZ callsign last modified date string.
		 */
		const std::string &getModdate() const
		{
			return m_moddate;
		}

		/**
		 * Sets the QRZ callsign last modified date.
		 *
		 * @param moddate The last modified date value to be set.
		 *
		 * @return void
		 */
		void setModdate(const std::string &moddate)
		{
			m_moddate = moddate;
		}

		/**
		 * @brief Retrieves the Metro Service Area (USPS).
		 *
		 * This function returns the Metro Service Area (USPS).
		 *
		 * @return const std::string& The Metro Service Area (USPS) string.
		 */
		const std::string getMsa() const
		{
			return m_MSA;
		}

		/**
		 * Sets the Metro Service Area (USPS) value.
		 *
		 * @param mMsa The Metro Service Area (USPS) value to be set.
		 *
		 * @return void
		 */
		void setMsa(const std::string &mMsa)
		{
			m_MSA = mMsa;
		}

		/**
		 * @brief Retrieves the Telephone Area Code (USA).
		 *
		 * This function returns the Telephone Area Code (USA).
		 *
		 * @return const std::string& The Telephone Area Code (USA) string.
		 */
		const std::string getAreaCode() const
		{
			return m_AreaCode;
		}

		/**
		 * Sets the Telephone Area Code (USA) value.
		 *
		 * @param mAreaCode The Telephone Area Code (USA) value to be set.
		 *
		 * @return void
		 */
		void setAreaCode(const std::string &mAreaCode)
		{
			m_AreaCode = mAreaCode;
		}

		/**
		 * @brief Retrieves the Time Zone (USA).
		 *
		 * This function returns the Time Zone (USA).
		 *
		 * @return const std::string& The Time Zone (USA) string.
		 */
		const std::string &getTimeZone() const
		{
			return m_TimeZone;
		}

		/**
		 * Sets the Time Zone (USA) value.
		 *
		 * @param timeZone The Time Zone (USA) value to be set.
		 *
		 * @return void
		 */
		void setTimeZone(const std::string &timeZone)
		{
			m_TimeZone = timeZone;
		}

		/**
		 * @brief Retrieves the GMT Time Offset.
		 *
		 * This function returns the GMT Time Offset.
		 *
		 * @return const std::string& The GMT Time Offset string.
		 */
		int getGmtOffset() const
		{
			return m_GMTOffset;
		}

		/**
		 * Sets the GMT Time Offset value.
		 *
		 * @param mGmtOffset The GMT Time Offset value to be set.
		 *
		 * @return void
		 */
		void setGmtOffset(int mGmtOffset)
		{
			m_GMTOffset = mGmtOffset;
		}

		/**
		 * @brief Retrieves the Daylight Saving Time Observed value.
		 *
		 * This function returns the Daylight Saving Time Observed value.
		 *
		 * @return const std::string& Daylight Saving Time Observed string.
		 */
		const std::string &getDst() const
		{
			return m_DST;
		}

		/**
		 * Sets the Daylight Saving Time Observed value.
		 *
		 * @param dst The Daylight Saving Time Observed value to be set.
		 *
		 * @return void
		 */
		void setDst(const std::string &dst)
		{
			m_DST = dst;
		}

		/**
		 * @brief Retrieves the e-qsl flag.
		 *
		 * Will accept e-qsl (0/1 or blank if unknown).
		 *
		 * @return const std::string& e-qsl flag.
		 */
		const std::string &getEqsl() const
		{
			return m_eqsl;
		}

		/**
		 * Sets the e-qsl flag value.
		 *
		 * @param eqsl Will accept e-qsl (0/1 or blank if unknown).
		 *
		 * @return void
		 */
		void setEqsl(const std::string &eqsl)
		{
			m_eqsl = eqsl;
		}

		/**
		 * @brief Retrieves the m-qsl flag.
		 *
		 * Will return paper QSL (0/1 or blank if unknown).
		 *
		 * @return const std::string& m-qsl flag.
		 */
		const std::string &getMqsl() const
		{
			return m_mqsl;
		}

		/**
		 * Sets the ${variable_name} value.
		 *
		 * @param mqsl Will return paper QSL (0/1 or blank if unknown) value to be set.
		 *
		 * @return void
		 */
		void setMqsl(const std::string &mqsl)
		{
			m_mqsl = mqsl;
		}

		/**
		 * @brief Retrieves the CQ Zone identifier.
		 *
		 * This function returns the CQ Zone identifier.
		 *
		 * @return const std::string& CQ Zone identifier string.
		 */
		int getCqzone() const
		{
			return m_cqzone;
		}

		/**
		 * Sets the CQ Zone identifier value.
		 *
		 * @param mCqzone The CQ Zone identifier value to be set.
		 *
		 * @return void
		 */
		void setCqzone(int mCqzone)
		{
			m_cqzone = mCqzone;
		}

		/**
		 * @brief Retrieves the ITU Zone identifier.
		 *
		 * This function returns the ITU Zone identifier.
		 *
		 * @return const std::string& ITU Zone identifier string.
		 */
		int getItuzone() const
		{
			return m_ituzone;
		}

		/**
		 * Sets the ITU Zone identifier value.
		 *
		 * @param mItuzone The ITU Zone identifier value to be set.
		 *
		 * @return void
		 */
		void setItuzone(int mItuzone)
		{
			m_ituzone = mItuzone;
		}

		/**
		 * @brief Retrieves the Operator's year of birth.
		 *
		 * This function returns the Operator's year of birth.
		 *
		 * @return const std::string& Operator's year of birth string.
		 */
		const std::string &getBorn() const
		{
			return m_born;
		}

		/**
		 * Sets the operator's year of birth value.
		 *
		 * @param born The operator's year of birth value to be set.
		 *
		 * @return void
		 */
		void setBorn(const std::string &born)
		{
			m_born = born;
		}

		/**
		 * @brief Retrieves the callsign of the user who manages this callsign on QRZ.
		 *
		 * This function returns the callsign of the user who manages this callsign on QRZ.
		 *
		 * @return const std::string& Operator's year of birth string.
		 */
		const std::string &getUser() const
		{
			return m_user;
		}

		/**
		 * Sets the callsign of the user who manages this callsign on QRZ value.
		 *
		 * @param user The managing user callsign value to be set.
		 *
		 * @return void
		 */
		void setUser(const std::string &user)
		{
			m_user = user;
		}

		/**
		 * @brief Retrieves the LOTW flag.
		 *
		 * This function returns the flag indicating whether or not the operator will accept LOTW (0/1 or blank if unknown).
		 *
		 * @return const std::string& Operator's LOTW flag string.
		 */
		const std::string &getLotw() const
		{
			return m_lotw;
		}

		/**
		 * Sets the LOTW flag value.
		 *
		 * @param lotw The ${variable_name} LOTW value (0/1 or blank if unknown) to be set.
		 *
		 * @return void
		 */
		void setLotw(const std::string &lotw)
		{
			m_lotw = lotw;
		}

		/**
		 * @brief Retrieves the IOTA designator.
		 *
		 * This function returns the IOTA designator (blank if unknown).
		 *
		 * @return const std::string& IOTA Designator string.
		 */
		const std::string &getIota() const
		{
			return m_iota;
		}

		/**
		 * Sets the IOTA designator value (blank if unknown).
		 *
		 * @param iota The IOTA designator value (blank if unknown) to be set.
		 *
		 * @return void
		 */
		void setIota(const std::string &iota)
		{
			m_iota = iota;
		}

		/**
		 * @brief Retrieves the lat/long source.
		 *
		 * This function returns a reference to a string that describes source of lat/long data.
		 *
		 * @return const std::string& lat/long source string.
		 */
		const std::string &getGeoloc() const
		{
			return m_geoloc;
		}

		/**
		 * Sets the lat/long source value.
		 *
		 * @param geoloc The lat/long source value to be set.
		 *
		 * @return void
		 */
		void setGeoloc(const std::string &geoloc)
		{
			m_geoloc = geoloc;
		}

		/**
		 * @brief Retrieves the Attention address line.
		 *
		 * This function returns the Attention address line, this line should be prepended to the address.
		 *
		 * @return const std::string& Attention address line string.
		 */
		const std::string &getAttn() const
		{
			return m_attn;
		}

		/**
		 * Sets the Attention address line value.
		 *
		 * @param attn The Attention address line value to be set.
		 *
		 * @return void
		 */
		void setAttn(const std::string &attn)
		{
			m_attn = attn;
		}

		/**
		 * @brief Retrieves the nickname.
		 *
		 * This function returns a different or shortened name used on the air.
		 *
		 * @return const std::string& Nickname string.
		 */
		const std::string &getNickname() const
		{
			return m_nickname;
		}

		void setNickname(const std::string &nickname)
		{
			m_nickname = nickname;
		}

		/**
		 * @brief Retrieves the full name and nickname.
		 *
		 * This function returns a combined full name and nickname in the format used by QRZ. This format is subject to change.
		 *
		 * @return const std::string& Formatted full name string.
		 */
		const std::string &getNameFmt() const
		{
			return m_name_fmt;
		}

		/**
		 * Sets the full name and nickname value.
		 *
		 * @param nameFmt The full name and nickname value to be set.
		 *
		 * @return void
		 */
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

		// Address line 2 (QRZ XML uses this for the city, be we have a separate field for that, this will be unused)
		std::string m_addr2;

		// City
		std::string m_city;

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
		int m_u_views;

		// Approximate length of the bio HTML in bytes
		int m_bio;

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