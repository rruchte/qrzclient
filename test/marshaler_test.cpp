#include <gtest/gtest.h>
#include "../src/model/DXCCMarshaler.h"
#include "../src/model/DXCC.h"
#include "../src/model/CallsignMarshaler.h"

namespace qrz
{
	namespace
	{
		class MarshalerTests : public testing::Test
		{
		protected:
			// You can remove any or all of the following functions if their bodies would
			// be empty.

			MarshalerTests() = default;

			~MarshalerTests() override = default;

			void SetUp() override
			{
			}

			void TearDown() override
			{
			}

			std::string callsignXmlW1AW=R"xml(
<QRZDatabase>
    <Callsign>
        <call>W1AW</call>
        <xref/>
        <aliases/>
        <dxcc>291</dxcc>
        <fname/>
        <name>ARRL HQ OPERATORS CLUB</name>
        <addr1>225 MAIN ST</addr1>
        <addr2>NEWINGTON</addr2>
        <state>CT</state>
        <zip>06111</zip>
        <country>United States</country>
        <ccode>HAB</ccode>
        <lat>41.714775</lat>
        <lon>-72.727260</lon>
        <grid>FN31pr</grid>
        <county>Hartford</county>
        <fips>09003</fips>
        <land>United States</land>
        <efdate>2020-12-08</efdate>
        <expdate>2031-02-26</expdate>
        <p_call/>
        <class>C</class>
        <codes>HAB</codes>
        <qslmgr>US STATIONS PLEASE QSL VIA LOTW OR DIRECT WITH SASE.</qslmgr>
        <email>W1AW@ARRL.ORG</email>
        <url/>
        <u_views>4970576</u_views>
        <bio>2144</bio>
        <biodate>2023-06-01 19:15:16</biodate>
        <image>https://cdn-xml.qrz.com/w/w1aw/W1AW.jpg</image>
        <imageinfo>168:250:20359</imageinfo>
        <serial/>
        <moddate>2021-10-18 16:09:52</moddate>
        <MSA>3280</MSA>
        <AreaCode>860</AreaCode>
        <TimeZone>Eastern</TimeZone>
        <GMTOffset>-5</GMTOffset>
        <DST>Y</DST>
        <eqsl>0</eqsl>
        <mqsl>1</mqsl>
        <cqzone>5</cqzone>
        <ituzone>8</ituzone>
        <born/>
        <user/>
        <lotw>1</lotw>
        <iota/>
        <geoloc>user</geoloc>
        <attn>JOSEPH P CARCIA III</attn>
        <nickname/>
        <name_fmt>ARRL HQ OPERATORS CLUB</name_fmt>
    </Callsign>
</QRZDatabase>
)xml";

			std::string dxccXml291=R"xml(
<QRZDatabase>
    <DXCC>
        <dxcc>291</dxcc>
        <cc>USA</cc>
        <ccc/>
        <name>United States</name>
        <continent>NA</continent>
        <ituzone>0</ituzone>
        <cqzone>0</cqzone>
        <timezone>-5</timezone>
        <lat>37.701207</lat>
        <lon>-97.316895</lon>
        <notes/>
    </DXCC>
</QRZDatabase>
)xml";
		};

		TEST_F(MarshalerTests, TestCallsignMarshal)
		{
			CallsignMarshaler marshaler;
			Callsign testCallsign = marshaler.FromXml(callsignXmlW1AW);

			const char *expectedCall = "W1AW";
			const char *expectedName = "ARRL HQ OPERATORS CLUB";
			const char *expectedEmail = "W1AW@ARRL.ORG";

			ASSERT_STREQ(expectedCall, testCallsign.getCall().c_str()) << "Call should be " << expectedCall;
			ASSERT_STREQ(expectedName, testCallsign.getName().c_str()) << "Name should be " << expectedName;
			ASSERT_STREQ(expectedEmail, testCallsign.getEmail().c_str()) << "Email should be " << expectedEmail;

			std::string exportedXml = marshaler.ToXML(std::vector<Callsign> {testCallsign});
			Callsign remarshaledCallsign = marshaler.FromXml(exportedXml);

			ASSERT_STREQ(expectedCall, remarshaledCallsign.getCall().c_str()) << "Call should be " << expectedCall;
			ASSERT_STREQ(expectedName, remarshaledCallsign.getName().c_str()) << "Name should be " << expectedName;
			ASSERT_STREQ(expectedEmail, remarshaledCallsign.getEmail().c_str()) << "Email should be " << expectedEmail;
		}

		TEST_F(MarshalerTests, TestDXCCMarshal)
		{
			DXCCMarshaler marshaler;
			DXCC testDXCC = marshaler.FromXml(dxccXml291);

			const char *expectedDxcc = "291";
			const char *expectedCc = "USA";
			const char *expectedName = "United States";

			ASSERT_STREQ(expectedDxcc, testDXCC.getDxcc().c_str()) << "DXCC should be " << expectedDxcc;
			ASSERT_STREQ(expectedCc, testDXCC.getCc().c_str()) << "CC should be " << expectedCc;
			ASSERT_STREQ(expectedName, testDXCC.getName().c_str()) << "Name should be " << expectedName;

			std::string exportedXml = marshaler.ToXML(std::vector<DXCC> {testDXCC});
			DXCC remarshaledDXCC = marshaler.FromXml(exportedXml);

			ASSERT_STREQ(expectedDxcc, remarshaledDXCC.getDxcc().c_str()) << "DXCC should be " << expectedDxcc;
			ASSERT_STREQ(expectedCc, remarshaledDXCC.getCc().c_str()) << "CC should be " << expectedCc;
			ASSERT_STREQ(expectedName, remarshaledDXCC.getName().c_str()) << "Name should be " << expectedName;
		}
	}
}