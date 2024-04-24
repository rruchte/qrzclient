#include <gtest/gtest.h>
#include "../src/model/Callsign.h"
#include "../src/model/DXCC.h"
#include "../src/render/RendererFactory.h"

namespace qrz
{
	namespace
	{
		class RendererTests : public testing::Test
		{
		protected:
			// You can remove any or all of the following functions if their bodies would
			// be empty.

			RendererTests() = default;

			~RendererTests() override = default;

			void SetUp() override {
				// Save cout's buffer...
				sbuf = std::cout.rdbuf();
				// Redirect cout to our stringstream buffer or any other ostream
				std::cout.rdbuf(buffer.rdbuf());
			}

			// Called after each unit test
			void TearDown() override {
				// When done redirect cout to its old self
				std::cout.rdbuf(sbuf);
				sbuf = nullptr;
			}

			// The following objects can be reused in each unit test

			// This can be an ofstream as well or any other ostream
			std::stringstream buffer{};
			// Save cout's buffer here
			std::streambuf *sbuf;

			std::string callsignCsvHeader = R"csv("call","xref","aliases","dxcc","fname","name","addr1","addr2","state","zip","country","ccode","lat","lon","grid","county","fips","land","efdate","expdate","p_call","class","codes","qslmgr","email","url","u_views","bio","biodate","image","imageinfo","serial","moddate","MSA","AreaCode","TimeZone","GMTOffset","DST","eqsl","mqsl","cqzone","ituzone","born","user","lotw","iota","geoloc","attn","nickname","name_fmt")csv";
			std::string callsignCsvPayload = R"csv("W1AW","","","291","","ARRL HQ OPERATORS CLUB","225 MAIN ST","NEWINGTON","CT","06111","United States","HAB","41.714775","-72.727260","FN31pr","Hartford","09003","United States","2020-12-08","2031-02-26","","C","HAB","US STATIONS PLEASE QSL VIA LOTW OR DIRECT WITH SASE.","W1AW@ARRL.ORG","","4970576","2144","2023-06-01 19:15:16","https://cdn-xml.qrz.com/w/w1aw/W1AW.jpg","168:250:20359","","2021-10-18 16:09:52","3280","860","Eastern","-5","Y","0","1","5","8","","","1","","user","JOSEPH P CARCIA III","","ARRL HQ OPERATORS CLUB")csv";

			std::string dxccCsvHeader = R"csv("DXCC Code","DXCC Name","Continent","County Code (2)","County Code (3)","ITU Zone","CQ Zone","Timezone","Latitude","Longitude","Notes")csv";
			std::string dxccCsvPayload = R"csv("291","United States","NA","USA","","0","0","-5","37.701207","-97.316895","")csv";

			std::string callsignMDW1AW = R"md(| Callsign |          Name          | Class |   Address   |    City   |  County  | State |  Zip  |    Country    |  Grid  |
|   :---:  |          :---:         | :---: |    :---:    |   :---:   |   :---:  | :---: | :---: |     :---:     |  :---: |
| W1AW     | ARRL HQ OPERATORS CLUB | C     | 225 MAIN ST | NEWINGTON | Hartford | CT    | 06111 | United States | FN31pr |

)md";
			std::string dxccMD291 = R"md(| DXCC Code |   DXCC Name   | Continent | County Code (2) | County Code (3) | ITU Zone | CQ Zone | Timezone |  Latitude |  Longitude | Notes |
|   :---:   |     :---:     |   :---:   |      :---:      |      :---:      |   :---:  |  :---:  |   :---:  |   :---:   |    :---:   | :---: |
| 291       | United States | NA        | USA             |                 | 0        | 0       | -5       | 37.701207 | -97.316895 |       |

)md";

			std::string callsignJSONW1AW = R"json([
    {
        "AreaCode": "860",
        "DST": "Y",
        "GMTOffset": -5,
        "MSA": "3280",
        "TimeZone": "Eastern",
        "addr1": "225 MAIN ST",
        "addr2": "NEWINGTON",
        "aliases": "",
        "attn": "JOSEPH P CARCIA III",
        "bio": 2144,
        "biodate": "2023-06-01 19:15:16",
        "born": "",
        "call": "W1AW",
        "ccode": "HAB",
        "class": "C",
        "codes": "HAB",
        "country": "United States",
        "county": "Hartford",
        "cqzone": 5,
        "dxcc": "291",
        "efdate": "2020-12-08",
        "email": "W1AW@ARRL.ORG",
        "eqsl": "0",
        "expdate": "2031-02-26",
        "fips": "09003",
        "fname": "",
        "geoloc": "user",
        "grid": "FN31pr",
        "image": "https://cdn-xml.qrz.com/w/w1aw/W1AW.jpg",
        "imageinfo": "168:250:20359",
        "iota": "",
        "ituzone": 8,
        "land": "United States",
        "lat": "41.714775",
        "lon": "-72.727260",
        "lotw": "1",
        "moddate": "2021-10-18 16:09:52",
        "mqsl": "1",
        "name": "ARRL HQ OPERATORS CLUB",
        "name_fmt": "ARRL HQ OPERATORS CLUB",
        "nickname": "",
        "p_call": "",
        "qslmgr": "US STATIONS PLEASE QSL VIA LOTW OR DIRECT WITH SASE.",
        "serial": "",
        "state": "CT",
        "u_views": 4970576,
        "url": "",
        "user": "",
        "xref": "",
        "zip": "06111"
    }
]
)json";

			std::string dxccJSON291 = R"json([
    {
        "cc": "USA",
        "ccc": "",
        "continent": "NA",
        "cqzone": "0",
        "dxcc": "291",
        "ituzone": "0",
        "lat": "37.701207",
        "lon": "-97.316895",
        "name": "United States",
        "notes": "",
        "timezone": "-5"
    }
]
)json";

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

		TEST_F(RendererTests, TestCallsignRenderXML)
		{
			auto renderer = render::RendererFactory::createCallsignRenderer(OutputFormat::XML);

			Callsign testCallsign = CallsignMarshaler::FromXml(callsignXmlW1AW);

			renderer->Render(std::vector<Callsign> {testCallsign});

			std::string renderedXML{buffer.str()};

			Callsign remarshaledCallsign = CallsignMarshaler::FromXml(renderedXML);

			const char *expectedCall = "W1AW";
			const char *expectedName = "ARRL HQ OPERATORS CLUB";
			const char *expectedEmail = "W1AW@ARRL.ORG";

			ASSERT_STREQ(expectedCall, remarshaledCallsign.getCall().c_str()) << "Call should be " << expectedCall;
			ASSERT_STREQ(expectedName, remarshaledCallsign.getName().c_str()) << "Name should be " << expectedName;
			ASSERT_STREQ(expectedEmail, remarshaledCallsign.getEmail().c_str()) << "Email should be " << expectedEmail;
		}

		TEST_F(RendererTests, TestDXCCRenderXML)
		{
			auto renderer = render::RendererFactory::createDXCCRenderer(OutputFormat::XML);

			DXCC testDXCC = DXCCMarshaler::FromXml(dxccXml291);

			renderer->Render(std::vector<DXCC> {testDXCC});

			std::string renderedXML{buffer.str()};

			DXCC remarshaledDXCC = DXCCMarshaler::FromXml(renderedXML);

			const char *expectedDxcc = "291";
			const char *expectedCc = "USA";
			const char *expectedName = "United States";

			ASSERT_STREQ(expectedDxcc, remarshaledDXCC.getDxcc().c_str()) << "DXCC should be " << expectedDxcc;
			ASSERT_STREQ(expectedCc, remarshaledDXCC.getCc().c_str()) << "CC should be " << expectedCc;
			ASSERT_STREQ(expectedName, remarshaledDXCC.getName().c_str()) << "Name should be " << expectedName;
		}

		TEST_F(RendererTests, TestCallsignRenderCSV)
		{
			auto renderer = render::RendererFactory::createCallsignRenderer(OutputFormat::CSV);

			Callsign testCallsign = CallsignMarshaler::FromXml(callsignXmlW1AW);

			renderer->Render(std::vector<Callsign> {testCallsign});

			std::string renderedCSV{buffer.str()};

			bool headerFound = renderedCSV.starts_with(callsignCsvHeader);
			bool payloadFound = (renderedCSV.find(callsignCsvPayload) != std::string::npos);

			ASSERT_TRUE(headerFound) << "Output should begin with header";
			ASSERT_TRUE(payloadFound) << "Output should end with expected data";
		}

		TEST_F(RendererTests, TestDXCCRenderCSV)
		{
			auto renderer = render::RendererFactory::createDXCCRenderer(OutputFormat::CSV);

			DXCC testDXCC = DXCCMarshaler::FromXml(dxccXml291);

			renderer->Render(std::vector<DXCC> {testDXCC});

			std::string renderedCSV{buffer.str()};

			bool headerFound = renderedCSV.starts_with(dxccCsvHeader);
			bool payloadFound = (renderedCSV.find(dxccCsvPayload) != std::string::npos);

			ASSERT_TRUE(headerFound) << "Output should begin with header";
			ASSERT_TRUE(payloadFound) << "Output should end with expected data";
		}

		TEST_F(RendererTests, TestCallsignRenderJSON)
		{
			auto renderer = render::RendererFactory::createCallsignRenderer(OutputFormat::JSON);

			Callsign testCallsign = CallsignMarshaler::FromXml(callsignXmlW1AW);

			renderer->Render(std::vector<Callsign> {testCallsign});

			std::string renderedJSON{buffer.str()};

			ASSERT_STREQ(callsignJSONW1AW.c_str(), renderedJSON.c_str()) << "Output should match expectation";
		}

		TEST_F(RendererTests, TestDXCCRenderJSON)
		{
			auto renderer = render::RendererFactory::createDXCCRenderer(OutputFormat::JSON);

			DXCC testDXCC = DXCCMarshaler::FromXml(dxccXml291);

			renderer->Render(std::vector<DXCC> {testDXCC});

			std::string renderedJSON{buffer.str()};

			ASSERT_STREQ(dxccJSON291.c_str(), renderedJSON.c_str()) << "Output should match expectation";
		}

		TEST_F(RendererTests, TestCallsignRenderMarkdown)
		{
			auto renderer = render::RendererFactory::createCallsignRenderer(OutputFormat::MD);

			Callsign testCallsign = CallsignMarshaler::FromXml(callsignXmlW1AW);

			renderer->Render(std::vector<Callsign> {testCallsign});

			std::string renderedMD{buffer.str()};

			ASSERT_STREQ(callsignMDW1AW.c_str(), renderedMD.c_str()) << "Output should match expectation";
		}

		TEST_F(RendererTests, TestDXCCRenderMarkdown)
		{
			auto renderer = render::RendererFactory::createDXCCRenderer(OutputFormat::MD);

			DXCC testDXCC = DXCCMarshaler::FromXml(dxccXml291);

			renderer->Render(std::vector<DXCC> {testDXCC});

			std::string renderedMD{buffer.str()};

			ASSERT_STREQ(dxccMD291.c_str(), renderedMD.c_str()) << "Output should match expectation";
		}
	}
}