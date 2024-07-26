#pragma once

#include "bcrypt/BCrypt.hpp"

namespace util
{
	std::string generateHash(const std::string& password)
	{
		return BCrypt::generateHash(password);
	}

	bool verifyPassword(const std::string& password, const std::string& hash)
	{
		return BCrypt::validatePassword(password, hash);
	}
}