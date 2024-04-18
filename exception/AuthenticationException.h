#ifndef QRZ_AUTHENTICATIONEXCEPTION_H
#define QRZ_AUTHENTICATIONEXCEPTION_H

#include <exception>
#include <string>

namespace qrz
{
	class AuthenticationException : public std::exception
	{
	public:
		explicit AuthenticationException(std::string_view message = "Authentication error") : m_message(message)
		{}

		const char *what() const noexcept override;

	private :
		std::string m_message;
	};
}
#endif //QRZ_AUTHENTICATIONEXCEPTION_H
