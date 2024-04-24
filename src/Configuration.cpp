#include "Configuration.h"

#include <filesystem>
#include <format>
#include <iostream>

#ifdef WIN32
#include <userenv.h>
#endif

#include <Poco/Crypto/CipherFactory.h>
#include <Poco/Crypto/CipherKey.h>
#include <Poco/Crypto/CipherKeyImpl.h>

#include "Util.h"

using namespace qrz;

Configuration::Configuration()
{
	loadConfig();
}

Configuration::Configuration(const std::string &configDirPath) : configDirPath(configDirPath)
{
	loadConfig();
}

std::string Configuration::getCallsign()
{
	return getValue(f_callsign);
}

std::string Configuration::getPassword()
{
	if(hasPassword())
	{
		try
		{
			return decryptPassword(getValue(f_password));
		}
		catch (Poco::IOException &e)
		{
			std::cout << e.message() << std::endl;
		}
	}

	return "";
}

std::string Configuration::getSessionKey()
{
	return getValue(f_sessionKey);
}

std::string Configuration::getSessionExpiration()
{
	return getValue(f_sessionExpiration);
}

void Configuration::setCallsign(const std::string& callsign)
{
	setValue(f_callsign, callsign);
}

void Configuration::setPassword(const std::string& password)
{
	try
	{
		setValue(f_password, encryptPassword(password));
	}
	catch (Poco::IOException &e)
	{
		std::cout << e.message() << std::endl;
	}
}

void Configuration::setSessionKey(const std::string& sessionKey)
{
	setValue(f_sessionKey, sessionKey);
}

void Configuration::setSessionExpiration(const std::string& sessionExpiration)
{
	setValue(f_sessionExpiration, sessionExpiration);
}

bool Configuration::hasCallsign()
{
	return hasValue(f_callsign);
}

bool Configuration::hasPassword()
{
	return hasValue(f_password);
}

bool Configuration::hasSessionKey()
{
	return hasValue(f_sessionKey);
}

bool Configuration::hasSessionExpiration()
{
	return hasValue(f_sessionExpiration);
}

#ifdef WIN32

std::string Configuration::getConfigDirPath()
{expectedAction, expectedFormat, expectedTerms
	if (configDirPath.empty())
	{
		const char* homePath_p = getenv("USERPROFILE");

		if (!homePath_p)
		{
			throw libconfig::ConfigException {};
		}

		configDirPath = std::string{homePath_p};
	}

	return std::format("{:s}\\.qrz", configDirPath);
}

std::string Configuration::getConfigFilePath()
{
	const std::string configDirPath = getConfigDirPath();

	return format("{:s}\\{:s}", configDirPath, m_fileName);
}

#else

std::string Configuration::getConfigDirPath()
{
	if (configDirPath.empty())
	{
		const char* homePath_p = getenv("HOME");

		if (!homePath_p)
		{
			throw libconfig::ConfigException {};
		}

		configDirPath = std::string{homePath_p};
	}

	return std::format("{:s}/.config/qrz", configDirPath);
}

std::string Configuration::getConfigFilePath()
{
	const std::string configDirPath = getConfigDirPath();

	return format("{:s}/{:s}", configDirPath, m_fileName);
}

#endif

void Configuration::loadConfig()
{
	std::string configFilePath = getConfigFilePath();

	if(std::filesystem::exists(configFilePath))
	{
		m_cfg.readFile(configFilePath);
	}
}

void Configuration::saveConfig()
{
	std::string configDirPath = getConfigDirPath();
	std::string configFilePath = getConfigFilePath();

	if (!std::filesystem::exists(configDirPath))
	{
		std::filesystem::create_directories(configDirPath);
	}

	m_cfg.writeFile(configFilePath);
}

std::string Configuration::getValue(const std::string& key)
{
	std::string output;
	m_cfg.lookupValue(key, output);

	return output;
}

void Configuration::setValue(const std::string& key, const std::string& value)
{
	if(m_cfg.exists(key))
	{
		libconfig::Setting &setting = m_cfg.lookup(key);
		setting = value;
	}
	else
	{
		libconfig::Setting &root = m_cfg.getRoot();
		root.add(key, libconfig::Setting::TypeString) = value;
	}
}

bool Configuration::hasValue(const std::string& key)
{
	std::string value;
	if(m_cfg.lookupValue(key, value))
	{
		return (!value.empty());
	}

	return false;
}

std::string Configuration::encryptPassword(const std::string &password)
{
	Poco::Crypto::Cipher::Ptr cipher = createCipher();
	return cipher->encryptString(password, Poco::Crypto::Cipher::ENC_BASE64);
}

std::string Configuration::decryptPassword(const std::string &encrypted)
{
	Poco::Crypto::Cipher::Ptr cipher = createCipher();
	return cipher->decryptString(encrypted, Poco::Crypto::Cipher::ENC_BASE64);
}

Poco::Crypto::Cipher::Ptr Configuration::createCipher()
{
	std::string passkey = createPassKeyForDecryption();
	std::string ivStr = ivStr_.substr(0, 32);

	Poco::Crypto::Cipher::ByteVec iv{ivStr.begin(), ivStr.end()};
	Poco::Crypto::Cipher::ByteVec passwordKey{ passkey.begin(), passkey.end() };
	Poco::Crypto::CipherKey key("aes-256-cbc", passwordKey, iv);
	Poco::Crypto::Cipher::Ptr cipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(key);

	return cipher;
}

std::string Configuration::createPassKeyForDecryption()
{
	std::string passkey = getCallsign();
	while(passkey.size() < 64) {
		passkey.append(getCallsign());
	}
	return passkey.substr(0, 64);
}

const std::string Configuration::ivStr_ = "https://xmldata.qrz.com/xml/current/?username=%callsign%;password=%password%";