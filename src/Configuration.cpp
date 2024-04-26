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

/**
 * @class Configuration
 *
 * The Configuration class represents a configuration file manager. It allows
 * reading and writing configuration values from a file. Configuration values
 * include callsign, password, session key, and session expiration.
 *
 * Example Usage:
 *
 * Configuration config;
 * config.setCallsign("ABCD123");
 * config.setPassword("mypassword");
 * config.saveConfig();
 *
 * std::string callsign = config.getCallsign();
 * std::string password = config.getPassword();
 *
 * Note: The configuration file is stored in the user's home directory under
 * the `.config/qrz` directory on POSIX systems, and on Windows, in the user's AppData directory in a dir named .qrz.
 *
 * The file name is `qrz.cfg`.
 */
Configuration::Configuration()
{
	loadConfig();
}

Configuration::Configuration(const std::string &configDirPath) : configDirPath(configDirPath)
{
	loadConfig();
}

/**
 * @brief Returns the callsign value from the configuration.
 *
 * This function retrieves the callsign value from the configuration.
 *
 * @return The callsign value as a string.
 */
std::string Configuration::getCallsign()
{
	return getValue(f_callsign);
}

/**
* @brief Retrieves the password value from the configuration.
*
* This function retrieves the password value from the configuration file.
*
* @return The password value as a string.
*/
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

/**
 * @brief Retrieves the session key value from the configuration.
 *
 * This function retrieves the session key value from the configuration file.
 *
 * @return The session key value as a string.
 */
std::string Configuration::getSessionKey()
{
	return getValue(f_sessionKey);
}

/**
 * @brief Retrieves the session expiration value from the configuration file.
 *
 * This function retrieves the session expiration value from the configuration
 * file using the key "session_expiration". Session expiration represents the
 * duration of time in which a session remains valid.
 *
 * @return The session expiration value as a string.
 */
std::string Configuration::getSessionExpiration()
{
	return getValue(f_sessionExpiration);
}

/**
 * @brief Sets the callsign value in the configuration.
 *
 * This function sets the callsign value in the configuration.
 *
 * @param callsign The callsign value as a string.
 */
void Configuration::setCallsign(const std::string& callsign)
{
	setValue(f_callsign, callsign);
}

/**
   * @brief Sets the password value in the configuration.
   *
   * This function sets the password value in the configuration by encrypting it and
   * storing it in the configuration file.
   *
   * @param password The password value as a string.
   */
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

/**
* @brief Sets the session key value in the configuration.
*
* This function sets the session key value in the configuration by updating
* the corresponding field in the configuration file.
*
* @param sessionKey The session key value as a string.
*/
void Configuration::setSessionKey(const std::string& sessionKey)
{
	setValue(f_sessionKey, sessionKey);
}

/**
* @brief Sets the session expiration value in the configuration.
*
* This function sets the session expiration value in the configuration by updating
* the corresponding field in the configuration file.
*
* @param sessionExpiration The session expiration value as a string.
*/
void Configuration::setSessionExpiration(const std::string& sessionExpiration)
{
	setValue(f_sessionExpiration, sessionExpiration);
}

/**
* @brief Checks if the configuration has a callsign value.
*
* This function checks if the configuration has a callsign value by calling the hasValue() function using the callsign key.
*
* @return True if the configuration has a callsign value, false otherwise.
*/
bool Configuration::hasCallsign()
{
	return hasValue(f_callsign);
}

/**
* @brief Checks if the configuration has a password value.
*
* This function checks if the configuration has a password value by calling the hasValue() function using the password key.
*
* @return True if the configuration has a password value, false otherwise.
*/
bool Configuration::hasPassword()
{
	return hasValue(f_password);
}

/**
 * @brief Checks if the configuration has a session key value.
 *
 * This function checks if the configuration has a session key value by calling the hasValue() function using the session key key.
 *
 * @return True if the configuration has a session key value, false otherwise.
 */
bool Configuration::hasSessionKey()
{
	return hasValue(f_sessionKey);
}

/**
 * @brief Checks if the configuration has a session expiration value.
 *
 * This function checks if the configuration has a session expiration value by calling the hasValue() function using the session expiration key.
 *
 * @return True if the configuration has a session expiration value, false otherwise.
 */
bool Configuration::hasSessionExpiration()
{
	return hasValue(f_sessionExpiration);
}

#ifdef WIN32
/**
 * @brief Retrieves the path to the configuration directory.
 *
 * This function retrieves the path to the configuration directory. The configuration directory is where the configuration file is stored.
 *
 * @return The path to the configuration directory as a string.
 */
std::string Configuration::getConfigDirPath()
{
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

/**
 * @brief Retrieves the configuration file path.
 *
 * This function retrieves the file path of the configuration file.
 *
 * @return The file path of the configuration file as a string.
 */
std::string Configuration::getConfigFilePath()
{
	const std::string configDirPath = getConfigDirPath();

	return format("{:s}\\{:s}", configDirPath, m_fileName);
}

#else

/**
 * @brief Retrieves the path to the configuration directory.
 *
 * This function retrieves the path to the configuration directory. The configuration directory is where the configuration file is stored.
 *
 * @return The path to the configuration directory as a string.
 */
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

/**
 * @brief Retrieves the configuration file path.
 *
 * This function retrieves the file path of the configuration file.
 *
 * @return The file path of the configuration file as a string.
 */
std::string Configuration::getConfigFilePath()
{
	const std::string configDirPath = getConfigDirPath();

	return format("{:s}/{:s}", configDirPath, m_fileName);
}

#endif

/**
 * @brief Load the configuration file.
 *
 * This function reads the configuration file and stores the contents in the `m_cfg` object.
 * The file is located in the directory specified by `configDirPath` and has the name "qrz.cfg".
 * If the file does not exist, no action is taken.
 */
void Configuration::loadConfig()
{
	std::string configFilePath = getConfigFilePath();

	if(std::filesystem::exists(configFilePath))
	{
		m_cfg.readFile(configFilePath);
	}
}

/**
 * @brief Saves the current configuration settings to a file.
 *
 * This function saves the current configuration settings to a file. If the configuration
 * directory does not exist, it will be created. The configuration is written using the
 * libconfig library.
 */
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

/**
 * @brief Retrieves the value associated with the given key from the configuration.
 *
 * This function retrieves the value associated with the given key from the configuration file.
 *
 * @param key The key for which the value needs to be retrieved.
 * @return The value associated with the key as a string.
 */
std::string Configuration::getValue(const std::string& key)
{
	std::string output;
	m_cfg.lookupValue(key, output);

	return output;
}

/**
 * @brief Sets the value associated with the given key in the configuration.
 *
 * This function sets the value associated with the given key in the configuration file.
 * If the key already exists in the configuration, the value will be updated. If the key does not exist,
 * a new key-value pair will be added to the configuration.
 *
 * @param key The key for which the value needs to be set.
 * @param value The value to be associated with the key.
 */
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

/**
* @brief Checks if the configuration has a value associated with the given key.
*
* This function checks if the configuration has a value associated with the given key.
*
* @param key The key for which the value needs to be checked.
* @return True if the configuration has a value associated with the key, false otherwise.
*/
bool Configuration::hasValue(const std::string& key)
{
	std::string value;
	if(m_cfg.lookupValue(key, value))
	{
		return (!value.empty());
	}

	return false;
}

/**
 * @brief Encrypts a password using AES-256-CBC encryption and base64 encoding.
 *
 * This function takes a password as input and encrypts it using AES-256-CBC encryption.
 * The encrypted password is then encoded in base64 format and returned as a string.
 *
 * @param password The password to be encrypted as a string.
 * @return The encrypted password as a string.
 */
std::string Configuration::encryptPassword(const std::string &password)
{
	Poco::Crypto::Cipher::Ptr cipher = createCipher();
	return cipher->encryptString(password, Poco::Crypto::Cipher::ENC_BASE64);
}

/**
 * @brief Decrypts an encrypted password.
 *
 * This function takes an encrypted password as input and decrypts it using AES-256-CBC decryption
 * and base64 decoding. The decrypted password is then returned as a string.
 *
 * @param encrypted The encrypted password to be decrypted as a string.
 * @return The decrypted password as a string.
 */
std::string Configuration::decryptPassword(const std::string &encrypted)
{
	Poco::Crypto::Cipher::Ptr cipher = createCipher();
	return cipher->decryptString(encrypted, Poco::Crypto::Cipher::ENC_BASE64);
}

/**
 * @brief Creates an instance of Poco::Crypto::Cipher.
 *
 * This function creates an instance of Poco::Crypto::Cipher with the specified encryption algorithm, password key, and initialization vector.
 *
 * @return A pointer to the created instance of Poco::Crypto::Cipher.
 */
Poco::Crypto::Cipher::Ptr Configuration::createCipher()
{
	std::string passkey = createCryptoPassKey();
	std::string ivStr = ivStr_.substr(0, 32);

	Poco::Crypto::Cipher::ByteVec iv{ivStr.begin(), ivStr.end()};
	Poco::Crypto::Cipher::ByteVec passwordKey{ passkey.begin(), passkey.end() };
	Poco::Crypto::CipherKey key("aes-256-cbc", passwordKey, iv);
	Poco::Crypto::Cipher::Ptr cipher = Poco::Crypto::CipherFactory::defaultFactory().createCipher(key);

	return cipher;
}

/**
 * @brief Creates a passkey for encryption/decryption.
 *
 * This function creates a passkey for encryption/decryption by concatenating the callsign string multiple times.
 * The passkey is then truncated to a length of 64 characters before being returned.
 *
 * @return The passkey for decryption as a string.
 */
std::string Configuration::createCryptoPassKey()
{
	std::string passkey = getCallsign();
	while(passkey.size() < 64) {
		passkey.append(getCallsign());
	}
	return passkey.substr(0, 64);
}

/**
 * Initialization vector for the cipher
 * Lame attempt at security by obscurity
 */
const std::string Configuration::ivStr_ = "https://xmldata.qrz.com/xml/current/?username=%callsign%;password=%password%";