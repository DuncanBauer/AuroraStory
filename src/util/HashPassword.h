#pragma once


#include "bcrypt/BCrypt.hpp"

namespace util
{
	inline std::string generateHash(const std::string& password)
	{
		return BCrypt::generateHash(password);
	}

	inline bool verifyPassword(const std::string& password, const std::string& hash)
	{
		return BCrypt::validatePassword(password, hash);
	}
}