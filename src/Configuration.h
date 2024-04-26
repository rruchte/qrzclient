#ifndef QRZ_CONFIGURATION_H
#define QRZ_CONFIGURATION_H

#include <string>

#include <libconfig.h++>
#include <Poco/AutoPtr.h>
#include <Poco/Crypto/Cipher.h>

namespace qrz
{
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
	class Configuration
	{
	public:
		Configuration();

		explicit Configuration(const std::string &configDirPath);

		/**
		 * @brief Returns the callsign value from the configuration.
		 *
		 * This function retrieves the callsign value from the configuration.
		 *
		 * @return The callsign value as a string.
		 */
		std::string getCallsign();

		/**
		 * @brief Retrieves the password value from the configuration.
		 *
		 * This function retrieves the password value from the configuration file.
		 *
		 * @return The password value as a string.
		 */
		std::string getPassword();

		/**
		 * @brief Retrieves the session key value from the configuration.
		 *
		 * This function retrieves the session key value from the configuration file.
		 *
		 * @return The session key value as a string.
		 */
		std::string getSessionKey();

		/**
		 * @brief Retrieves the session expiration value from the configuration file.
		 *
		 * This function retrieves the session expiration value from the configuration
		 * file using the key "session_expiration". Session expiration represents the
		 * duration of time in which a session remains valid.
		 *
		 * @return The session expiration value as a string.
		 */
		std::string getSessionExpiration();

		/**
		 * @brief Sets the callsign value in the configuration.
		 *
		 * This function sets the callsign value in the configuration.
		 *
		 * @param callsign The callsign value as a string.
		 */
		void setCallsign(const std::string &callsign);

		/**
		 * @brief Sets the password value in the configuration.
		 *
		 * This function sets the password value in the configuration by encrypting it and
		 * storing it in the configuration file.
		 *
		 * @param password The password value as a string.
		 */
		void setPassword(const std::string &password);

		/**
		 * @brief Sets the session key value in the configuration.
		 *
		 * This function sets the session key value in the configuration by updating
		 * the corresponding field in the configuration file.
		 *
		 * @param sessionKey The session key value as a string.
		 */
		void setSessionKey(const std::string &sessionKey);

		/**
		 * @brief Sets the session expiration value in the configuration.
		 *
		 * This function sets the session expiration value in the configuration by updating
		 * the corresponding field in the configuration file.
		 *
		 * @param sessionExpiration The session expiration value as a string.
		 */
		void setSessionExpiration(const std::string &sessionExpiration);

		/**
		 * @brief Checks if the configuration has a callsign value.
		 *
		 * This function checks if the configuration has a callsign value.
		 *
		 * @return True if the configuration has a callsign value, false otherwise.
		 */
		bool hasCallsign();

		/**
		* @brief Checks if the configuration has a password value.
		*
		* This function checks if the configuration has a password value.
		*
		* @return True if the configuration has a password value, false otherwise.
		*/
		bool hasPassword();

		/**
		 * @brief Checks if the configuration has a session key value.
		 *
		 * This function checks if the configuration has a session key value.
		 *
		 * @return True if the configuration has a session key value, false otherwise.
		 */
		bool hasSessionKey();

		/**
		 * @brief Checks if the configuration has a session expiration value.
		 *
		 * This function checks if the configuration has a session expiration value.
		 *
		 * @return True if the configuration has a session expiration value, false otherwise.
		 */
		bool hasSessionExpiration();

		/**
		 * @brief Saves the current configuration settings to a file.
		 *
		 * This function saves the current configuration settings to a file. If the configuration
		 * directory does not exist, it will be created.
		 */
		void saveConfig();
	private:
		// Name for the config file
		static inline const char *m_fileName = "qrz.cfg";

		// String to use as the initialization vector for password encryption
		static const std::string ivStr_;

		// libconfig Config instance
		libconfig::Config m_cfg;

		// Path to the directory that contains the config file
		std::string configDirPath;

		// Field names
		static inline const char *f_callsign = "callsign";
		static inline const char *f_password = "password";
		static inline const char *f_sessionKey = "session_key";
		static inline const char *f_sessionExpiration = "session_expiration";

		/**
		 * @brief Retrieves the value associated with the given key from the configuration.
		 *
		 * This function retrieves the value associated with the given key from the configuration file.
		 *
		 * @param key The key for which the value needs to be retrieved.
		 * @return The value associated with the key as a string.
		 */
		std::string getValue(const std::string &key);

		/**
		 * @brief Sets the value associated with the given key in the configuration.
		 *
		 * This function sets the value associated with the given key in the configuration file.
		 *
		 * @param key The key for which the value needs to be set.
		 * @param value The value to be associated with the key.
		 */
		void setValue(const std::string &key, const std::string &value);

		/**
		 * @brief Checks if the configuration has a value associated with the given key.
		 *
		 * This function checks if the configuration has a value associated with the given key.
		 *
		 * @param key The key for which the value needs to be checked.
		 * @return True if the configuration has a value associated with the key, false otherwise.
		 */
		bool hasValue(const std::string &key);

		/**
		 * @brief Load the configuration file.
		 *
		 * This function reads the configuration file and populates the configuration instance
		 */
		void loadConfig();

		/**
		 * @brief Retrieves the path to the configuration directory.
		 *
		 * This function retrieves the path to the configuration directory. The configuration directory is where the configuration file is stored.
		 *
		 * @return The path to the configuration directory as a string.
		 */
		std::string getConfigDirPath();

		/**
		 * @brief Retrieves the configuration file path.
		 *
		 * This function retrieves the file path of the configuration file.
		 *
		 * @return The file path of the configuration file as a string.
		 */
		std::string getConfigFilePath();

		/**
		 * @brief Encrypts a password using AES-256-CBC encryption and base64 encoding.
		 *
		 * This function takes a password as input and encrypts it using AES-256-CBC encryption.
		 * The encrypted password is then encoded in base64 format and returned as a string.
		 *
		 * @param password The password to be encrypted as a string.
		 * @return The encrypted password as a string.
		 */
		std::string encryptPassword(const std::string &password);

		/**
		 * @brief Decrypts an encrypted password.
		 *
		 * This function takes an encrypted password as input and decrypts it using AES-256-CBC decryption
		 * and base64 decoding. The decrypted password is then returned as a string.
		 *
		 * @param encrypted The encrypted password to be decrypted as a string.
		 * @return The decrypted password as a string.
		 */
		std::string decryptPassword(const std::string &encrypted);

		/**
		 * @brief Creates an instance of Poco::Crypto::Cipher.
		 *
		 * This function creates an instance of Poco::Crypto::Cipher with the appropriate configuration
		 *
		 * @return A pointer to the created instance of Poco::Crypto::Cipher.
		 */
		Poco::AutoPtr<Poco::Crypto::Cipher> createCipher();

		/**
		 * @brief Creates a passkey for encryption/decryption.
		 *
		 * This function creates a passkey for encryption/decryption
		 *
		 * @return The passkey for decryption as a string.
		 */
		std::string createCryptoPassKey();
	};
}

#endif //QRZ_CONFIGURATION_H
