#ifndef QRZ_CONFIGURATION_H
#define QRZ_CONFIGURATION_H

#include <string>

#include <libconfig.h++>
#include <Poco/AutoPtr.h>
#include <Poco/Crypto/Cipher.h>

namespace qrz
{
	class Configuration
	{
	public:
		Configuration();
		std::string getCallsign();
		std::string getPassword();
		std::string getSessionKey();
		std::string getSessionExpiration();
		void setCallsign(const std::string &callsign);
		void setPassword(const std::string &password);
		void setSessionKey(const std::string &sessionKey);
		void setSessionExpiration(const std::string &sessionExpiration);
		bool hasCallsign();
		bool hasPassword();
		bool hasSessionKey();
		bool hasSessionExpiration();
		void saveConfig();
	private:
		libconfig::Config m_cfg;

		static inline const char *m_fileName = "qrz.cfg";

		// Field names
		static inline const char *f_callsign = "callsign";
		static inline const char *f_password = "password";
		static inline const char *f_sessionKey = "session_key";
		static inline const char *f_sessionExpiration = "session_expiration";

		std::string getValue(const std::string &key);
		void setValue(const std::string &key, const std::string &value);
		bool hasValue(const std::string &key);
		void loadConfig();
		static std::string getConfigDirPath();
		static std::string getConfigFilePath();
		std::string encryptPassword(const std::string &password);
		std::string decryptPassword(const std::string &encrypted);
		Poco::AutoPtr<Poco::Crypto::Cipher> createCipher();
		std::string createPassKeyForDecryption();

		static const std::string ivStr_;
	};
}

#endif //QRZ_CONFIGURATION_H
