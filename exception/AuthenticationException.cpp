#include "AuthenticationException.h"

const char* qrz::AuthenticationException::what() const noexcept
{
	return m_message.c_str();
};