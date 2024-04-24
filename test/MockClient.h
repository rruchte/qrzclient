#ifndef QRZ_MOCKCLIENT_H
#define QRZ_MOCKCLIENT_H

#include "../src/QRZClient.h"

namespace qrz
{
	class MockClient : public QRZClient
	{
	public:
		MockClient() = default;

		explicit MockClient(Configuration &config)
		{
			setUsername(config.getCallsign());
			setPassword(config.getPassword());
			setSessionKey(config.getSessionKey());
			setSessionExpiration(config.getSessionExpiration());
		}

		QrzResponse sendRequest(Poco::URI &uri) override
		{
			std::string path = Poco::format("/xml/%s/", m_apiVersion);
			uri.setPath(path);
			uri.addQueryParameter("agent", m_userAgent);

			// Create a session
			const Poco::Net::Context::Ptr ptrContext = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "", "", "", Poco::Net::Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort(), ptrContext);

			// Prepare a GET request
			Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.toString());

			// Get the response
			Poco::Net::HTTPResponse response;
			response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

			std::string body;

			Poco::URI::QueryParameters params = uri.getQueryParameters();

			std::string action;
			std::string term;

			for(std::pair<std::string, std::string> currPair : params)
			{
				if(currPair.first == "callsign" || currPair.first == "dxcc" || currPair.first == "html" || currPair.first == "password")
				{
					action = currPair.first;
					term = currPair.second;

					break;
				}
			}

			ToUpper(term);

			if(action == "callsign")
			{
				if(term == "W1AW")
				{
					body = callsignXmlW1AW;
				}
				else if(term == "W5YI")
				{
					body = callsignXmlW5YI;
				}
			}
			else if(action == "html")
			{
				if(term == "W1AW")
				{
					body = bioHtmlW1AW;
				}
				else if(term == "W5YI")
				{
					body = bioHtmlW5YI;
				}
			}
			else if(action == "dxcc")
			{
				if(term == "191")
				{
					body = dxccXml191;
				}
				else if(term == "291")
				{
					body = dxccXml291;
				}
			}
			else if(action == "password")
			{
				body = sessionResponse;
			}

			QrzResponse output{response, body};

			return output;
		}

		bool testValidateResponse(const std::string &responseBody)
		{
			try
			{
				validateResponse(responseBody);

				return true;
			}
			catch(std::exception &e){}

			return false;
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
	<Session>
		<Key>d0cf9d7b3b937ed5f5de28ddf5a0122d</Key>
		<Count>12</Count>
		<SubExp>Wed Jan 13 13:59:00 2013</SubExp>
		<GMTime>Mon Oct 12 22:33:56 2012</GMTime>
	</Session>
</QRZDatabase>
)xml";

		std::string callsignXmlW5YI=R"xml(
<QRZDatabase>
    <Callsign>
        <call>W5YI</call>
        <xref/>
        <aliases>W5VE</aliases>
        <dxcc>291</dxcc>
        <fname/>
        <name>THE W5YI VEC</name>
        <addr1>2000 E RANDOL MILL RD 608A</addr1>
        <addr2>ARLINGTON</addr2>
        <state>TX</state>
        <zip>76011</zip>
        <country>United States</country>
        <ccode>HVBD</ccode>
        <lat>32.756259</lat>
        <lon>-97.084801</lon>
        <grid>EM12ks</grid>
        <county>Tarrant</county>
        <fips>48439</fips>
        <land>United States</land>
        <efdate>2022-04-06</efdate>
        <expdate>2032-04-27</expdate>
        <p_call/>
        <class>C</class>
        <codes>HVBD</codes>
        <qslmgr/>
        <email>admin@w5yi.org</email>
        <url/>
        <u_views>19024</u_views>
        <bio>241</bio>
        <biodate>2015-07-16 00:30:17</biodate>
        <image>https://cdn-xml.qrz.com/i/w5yi/picture51_1_.png</image>
        <imageinfo>267:210:19076</imageinfo>
        <serial/>
        <moddate>2022-04-07 12:30:04</moddate>
        <MSA>2800</MSA>
        <AreaCode>817</AreaCode>
        <TimeZone>Central</TimeZone>
        <GMTOffset>-6</GMTOffset>
        <DST>Y</DST>
        <eqsl>1</eqsl>
        <mqsl>1</mqsl>
        <cqzone>3</cqzone>
        <ituzone>0</ituzone>
        <born>1984</born>
        <user/>
        <lotw>1</lotw>
        <iota/>
        <geoloc>user</geoloc>
        <attn>LARRY P POLLOCK</attn>
        <nickname/>
        <name_fmt>THE W5YI VEC</name_fmt>
    </Callsign>
	<Session>
		<Key>d0cf9d7b3b937ed5f5de28ddf5a0122d</Key>
		<Count>12</Count>
		<SubExp>Wed Jan 13 13:59:00 2013</SubExp>
		<GMTime>Mon Oct 12 22:33:56 2012</GMTime>
	</Session>
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
	<Session>
		<Key>d0cf9d7b3b937ed5f5de28ddf5a0122d</Key>
		<Count>12</Count>
		<SubExp>Wed Jan 13 13:59:00 2013</SubExp>
		<GMTime>Mon Oct 12 22:33:56 2012</GMTime>
	</Session>
</QRZDatabase>
)xml";

		std::string dxccXml191=R"xml(
<QRZDatabase>
    <DXCC>
        <dxcc>191</dxcc>
        <cc>NZL</cc>
        <ccc/>
        <name>North Cook Islands</name>
        <continent>OC</continent>
        <ituzone>62</ituzone>
        <cqzone>32</cqzone>
        <timezone>-11</timezone>
        <lat>-9.008330</lat>
        <lon>-157.958330</lon>
        <notes/>
    </DXCC>
	<Session>
		<Key>d0cf9d7b3b937ed5f5de28ddf5a0122d</Key>
		<Count>12</Count>
		<SubExp>Wed Jan 13 13:59:00 2013</SubExp>
		<GMTime>Mon Oct 12 22:33:56 2012</GMTime>
	</Session>
</QRZDatabase>
)xml";

	std::string bioHtmlW1AW=R"html(
<QRZDatabase version="1.36" xmlns="http://xmldata.qrz.com">
    <!DOCTYPE html
    PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
    <html xmlns="http://www.w3.org/1999/xhtml" lang="en-US" xml:lang="en-US">
    <head>
        <title>Untitled Document</title>
        <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1"/>
    </head>
    <body>
    <!-- QRZXML 1.36 W1AW -->
    <div id="biodata"><h1>PLEASE DO NOT SEND CARDS FOR W1AW/xx VOTA CONTACTS!</h1>
        <p>Additional Information about W1AW may be found on the web at:</p>
        <p><a href="http://www.arrl.org/w1aw">http://www.arrl.org/w1aw</a></p>
    </div>
    </body>
</html>
)html";

		std::string bioHtmlW5YI=R"html(
<QRZDatabase version="1.36" xmlns="http://xmldata.qrz.com">
<!DOCTYPE html
	PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
	 "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en-US" xml:lang="en-US">
<head>
<title>Untitled Document</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
</head>
<body>
<!-- QRZXML 1.36 W5YI -->
<div id="biodata">
	<p>W5VE is the Club Station Call Sign for the W5YI-VEC, located in Arlington, Texas.<br />
	The W5YI-VEC is a 501-C-3 non-profit organization volunteer examiner coordinator (VEC) appointed by the FCC.</p>
	<p>W5YI -&nbsp;sk 2012</p>
</div>
</body>
</html>

)html";

	std::string sessionResponse=R"xml(
<QRZDatabase version="1.34">
  <Session>
    <Key>2331uf894c4bd29f3923f3bacf02c532d7bd9</Key>
    <Count>123</Count>
    <SubExp>Wed Jan 1 12:34:03 2013</SubExp>
    <GMTime>Sun Aug 16 03:51:47 2012</GMTime>
  </Session>
</QRZDatabase>
)xml";
	};
}

#endif //QRZ_MOCKCLIENT_H
