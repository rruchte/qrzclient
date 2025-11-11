<p align="center">
  <a href="https://github.com/rruchte/qrzclient/blob/master/LICENSE"><img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="license"></a>
  <img src="https://img.shields.io/badge/version-1.0-blue.svg?cacheSeconds=2592000" alt="version">
</p>

# QRZ Client

## Command line client for the QRZ.com XML API

#### Features
* Callsign lookups
* DXCC Lookups
* BIO Retreival
* Multiple lookups per call
* Output to console, CSV, JSON, XML, or Markdown

### Usage
```console
foo@bar:~$ qrz -h
Usage: qrz [--help] [--version] [--action VAR] [--format VAR] search

Positional arguments:
  search         Callsign or DXCC ID to fetch details for. [nargs: 0 or more] 

Optional arguments:
  -h, --help     shows help message and exits 
  -v, --version  prints version information and exits 
  -a, --action   Specify the action to perform. callsign[default]|bio|dxcc|login [nargs=0..1] [default: "callsign"]
  -f, --format   Specify the output format. Console[default]|CSV|JSON|XML|MD [nargs=0..1] [default: "console"]
```

### Callsign Lookups
Basic example:
```console
foo@bar:~$ qrz W1AW
+----------+------------------------+-------+-------------+-----------+----------+-------+-------+---------------+--------+
| Callsign |          Name          | Class |   Address   |    City   |  County  | State |  Zip  |    Country    |  Grid  |
+----------+------------------------+-------+-------------+-----------+----------+-------+-------+---------------+--------+
| W1AW     | ARRL HQ OPERATORS CLUB | C     | 225 MAIN ST | NEWINGTON | Hartford | CT    | 06111 | United States | FN31pr |
+----------+------------------------+-------+-------------+-----------+----------+-------+-------+---------------+--------+
```

Any number of callsigns can be searched in a single call
```console
foo@bar:~$ qrz K8MRD KC5HWB KI6NAZ KT1RUN
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
| Callsign |       Name       | Class |             Address             |    City    |    County   | State |  Zip  |    Country    |  Grid  |
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
| K8MRD    | MIKE R DAHLHOFER | E     | 1916 Rosewood Ln.               | Huntsville | Walker      | TX    | 77340 | United States | EM20fr |
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
| KC5HWB   | JASON P JOHNSTON | G     | 2100 W. Northwest Hwy #114-1163 | Grapevine  | Tarrant     | TX    | 76051 | United States | EM12kt |
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
| KI6NAZ   | Josh B Nass      | E     | PO BOX 5101                     | Cerritos   | Los Angeles | CA    | 90703 | United States | DM03xu |
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
| KT7RUN   | Gaston Gonzalez  | G     | 38400 N SCHOOLHOUSE RD #7606    | CAVE CREEK | Maricopa    | AZ    | 85331 | United States | DM33xv |
+----------+------------------+-------+---------------------------------+------------+-------------+-------+-------+---------------+--------+
```

Output can also be formatted in CSV, JSON, XML, and Markdown. All fields returned by the API are included in the non-console output formats.
```console
foo@bar:~$ qrz -f csv W1AW
"call","xref","aliases","dxcc","fname","name","addr1","addr2","state","zip","country","ccode","lat","lon","grid","county","fips","land","efdate","expdate","p_call","class","codes","qslmgr","email","url","u_views","bio","biodate","image","imageinfo","serial","moddate","MSA","AreaCode","TimeZone","GMTOffset","DST","eqsl","mqsl","cqzone","ituzone","born","user","lotw","iota","geoloc","attn","nickname","name_fmt"
"W1AW","","","291","","ARRL HQ OPERATORS CLUB","225 MAIN ST","NEWINGTON","CT","06111","United States","HAB","41.714775","-72.727260","FN31pr","Hartford","09003","United States","2020-12-08","2031-02-26","","C","HAB","US STATIONS PLEASE QSL VIA LOTW OR DIRECT WITH SASE.","W1AW@ARRL.ORG","","4969953","2144","2023-06-01 19:15:16","https://cdn-xml.qrz.com/w/w1aw/W1AW.jpg","168:250:20359","","2021-10-18 16:09:52","3280","860","Eastern","-5","Y","0","1","5","8","","","1","","user","JOSEPH P CARCIA III","","ARRL HQ OPERATORS CLUB"
```

```console
foo@bar:~$ qrz -f json W1AW
[
    {
        "AreaCode": 860,
        "DST": "Y",
        "GMTOffset": -5,
        "MSA": 3280,
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
        "u_views": 4969953,
        "url": "",
        "user": "",
        "xref": "",
        "zip": "06111"
    }
]
```

```console
foo@bar:~$ qrz -f xml W1AW
<?xml version="1.0" encoding="UTF-8"?>
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
        <u_views>4969953</u_views>
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
```

```console
foo@bar:~$ qrz -f md W1AW
| Callsign |          Name          | Class |   Address   |    City   |  County  | State |  Zip  |    Country    |  Grid  |
|   :---:  |          :---:         | :---: |    :---:    |   :---:   |   :---:  | :---: | :---: |     :---:     |  :---: |
| W1AW     | ARRL HQ OPERATORS CLUB | C     | 225 MAIN ST | NEWINGTON | Hartford | CT    | 06111 | United States | FN31pr |
```

Multiple lookups work for all formats:
```console
foo@bar:~$ qrz -f xml K8MRD KC5HWB KI6NAZ KT1RUN
<QRZDatabase>
    <Callsign>
        <call>K8MRD</call>
        <xref/>
        <aliases>KE8EPF</aliases>
        <dxcc>291</dxcc>
        <fname>MIKE R</fname>
        <name>DAHLHOFER</name>
        [...]
    </Callsign>
    <Callsign>
        <call>KC5HWB</call>
        <xref/>
        <aliases/>
        <dxcc>291</dxcc>
        <fname>JASON P</fname>
        <name>JOHNSTON</name>
        [...]
    </Callsign>
    <Callsign>
        <call>KI6NAZ</call>
        <xref/>
        <aliases>JOSH</aliases>
        <dxcc>291</dxcc>
        <fname>Josh B</fname>
        <name>Nass</name>
        [...]
    </Callsign>
    <Callsign>
        <call>KT7RUN</call>
        <xref>KT1RUN</xref>
        <aliases>KT1RUN</aliases>
        <dxcc>291</dxcc>
        <fname>Gaston</fname>
        <name>Gonzalez</name>
        [...]
    </Callsign>
</QRZDatabase>
```

### DXCC Lookups
DXCC lookups are also supported. DXCC entities may be searched by code, or by callsign.

```console
foo@bar:~$ qrz -a dxcc 291 
+-----------+---------------+-----------+-----------------+-----------------+----------+---------+----------+-----------+------------+-------+
| DXCC Code |   DXCC Name   | Continent | County Code (2) | County Code (3) | ITU Zone | CQ Zone | Timezone |  Latitude |  Longitude | Notes |
+-----------+---------------+-----------+-----------------+-----------------+----------+---------+----------+-----------+------------+-------+
| 291       | United States | NA        | US              | USA             | 0        | 0       | -5       | 37.701207 | -97.316895 |       |
+-----------+---------------+-----------+-----------------+-----------------+----------+---------+----------+-----------+------------+-------+
```

```console
foo@bar:~$ qrz -a dxcc RV3DW 
+-----------+-----------+-----------+-----------------+-----------------+----------+---------+----------+-----------+-----------+-------+
| DXCC Code | DXCC Name | Continent | County Code (2) | County Code (3) | ITU Zone | CQ Zone | Timezone |  Latitude | Longitude | Notes |
+-----------+-----------+-----------+-----------------+-----------------+----------+---------+----------+-----------+-----------+-------+
| 54        | Russia    | EU        | RU              | RUS             | 19       | 16      | 3        | 55.751849 | 37.529297 |       |
+-----------+-----------+-----------+-----------------+-----------------+----------+---------+----------+-----------+-----------+-------+
```

CSV, JSON, XML, and Markdown formats are also provided for DXCC lookups.

```console
foo@bar:~$ qrz -a dxcc -f json RV3DW 
[
    {
        "cc": "RU",
        "ccc": "RUS",
        "continent": "EU",
        "cqzone": "16",
        "dxcc": "54",
        "ituzone": "19",
        "lat": "55.751849",
        "lon": "37.529297",
        "name": "Russia",
        "notes": "",
        "timezone": "3"
    }
]
```

```console
foo@bar:~$ qrz -a dxcc -f xml 281 
<?xml version="1.0" encoding="UTF-8"?>
<QRZDatabase>
    <DXCC>
        <dxcc>281</dxcc>
        <cc>ES</cc>
        <ccc>ESP</ccc>
        <name>Spain</name>
        <continent>EU</continent>
        <ituzone>37</ituzone>
        <cqzone>14</cqzone>
        <timezone>1</timezone>
        <lat>40.380028</lat>
        <lon>-3.735352</lon>
        <notes/>
    </DXCC>
</QRZDatabase>
```

```console
foo@bar:~$ qrz -a dxcc -f csv 270 
"DXCC Code","DXCC Name","Continent","County Code (2)","County Code (3)","ITU Zone","CQ Zone","Timezone","Latitude","Longitude","Notes"
"270","Tokelau Islands","OC","TK","TKL","62","31","-11","-9.210560","-171.958008",""
```

```console
foo@bar:~$ qrz -a dxcc -f md 181
| DXCC Code |  DXCC Name | Continent | County Code (2) | County Code (3) | ITU Zone | CQ Zone | Timezone |  Latitude  | Longitude | Notes |
|   :---:   |    :---:   |   :---:   |      :---:      |      :---:      |   :---:  |  :---:  |   :---:  |    :---:   |   :---:   | :---: |
| 181       | Mozambique | AF        | MZ              | MOZ             | 53       | 37      | 2        | -24.647017 | 32.827148 |       |
```

### Bio Retreival
Bio retrieval is supported. Bios are only provided in HTML format. Note that at this time, QRZ is including an XML declaration and QRZDatabase opening element, followed by an HTML document, with no /QRZDatabase. This is the direct output of the API. 

```console
foo@bar:~$ qrz -a bio W1AW 
<?xml version="1.0" encoding="utf-8" ?>
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

<style type="text/css"></style>

<!-- QRZXML 1.36 W1AW -->
<div id="biodata"><h1>PLEASE DO NOT SEND CARDS FOR W1AW/xx VOTA CONTACTS!</h1>

<h1>Please note there are <u>NO QSL cards</u> available for any of the <u>2023 W1AW/xx VOTA operations</u>.  All contacts will be confirmed <u>VIA LoTW</u> only.</h1>

<h1>If W1AW is active for IARU, or any other <u><strong>NON-VOTA</strong> operation</u> – such as an ARRL Division Convention, Pacificon, etc. – there will be QSL cards available as normal.</h1>

<p><strong><span style="font-size:18px">QSL cards for contacts made with Maxim Memorial Station W1AW in Newington, Connecticut are available as usual.</span></strong></p>

<p><img src="https://cdn-bio.qrz.com/w/w1aw/IMG_7521.JPG" style="height:900px; width:1200px"></p>

<h1> </h1>

<h1><span style="font-size:14px">The QSL Bureau system is OKAY for all other non-US QSL card requests.</span></h1>

<p>Additional Information about W1AW may be found on the web at:</p>

<p><a href="http://www.arrl.org/w1aw">http://www.arrl.org/w1aw</a></p>

<p> </p>

<p>W1AW Code Practice and Bulletin Transmission Equipment</p>

<p>Equipment used for daily practice/bulletin transmissions (as of 01/02/2023):</p>

<ul>
	<li>160 meters - Icom IC-7410 and Alpha 8410 amplifier</li>
	<li>80 meters - Icom IC-7300 and Acom 2000A amplifier</li>
	<li>40 meters - Icom IC-7300 and Acom 2000A amplifer</li>
	<li>20 meters - Icom IC-7300 and Acom 2000A amplifier</li>
	<li>17 meters - Icom IC-7300 and Acom 2000A amplifier</li>
	<li>15 meters - Icom IC-7300 and Acom 2000A amplifier</li>
	<li>10 meters - Yaesu FT-5000 and Icom IC-PW1 amplifier</li>
	<li>6 meters - Icom IC-756ProIII and converted Harris Platinum amplifier</li>
	<li>2 meters - Yaesu FT-2900 and converted Larcan amplifier</li>
</ul>

<p> </p>

<p>A list of the various W1AW/xx operations for 2023 Volunteers On The Air may be found in PDF form on the web at:</p>

<p><a href="https://contests.arrl.org/docs/2023-VOTA-State-Activations-Schedule.pdf">https://contests.arrl.org/docs/2023-VOTA-State-Activations-Schedule.pdf</a></p>

<p>PLEASE DO NOT SEND CARDS FOR W1AW/xx VOTA CONTACTS!</p>

<p> </p>

<p> </p>

<p> </p>
</div>

</body>
</html>
```
### Reset Login Details
Change your callsign and/or password
```console
foo@bar:~$ qrz -a login 
Are you sure you want to reset your login? [Y/n]: Y
Enter your callsign:
K4RWR
Login required. Enter the QRZ password for K4RWR:
Login details updated
```
### Notes
* An active qrz.com XML subscription is required. You will be prompted to enter your callsign and qrz.com password.
* Your password will be AES-256 encrypted and stored in a config file in your home directory.
* This project is in no way affiliated with qrz.com.

*DE K4RWR 73*
