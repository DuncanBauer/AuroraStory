#pragma once

#include "Core.h"
#include "bcrypt/BCrypt.hpp"

namespace util
{
	AURORA_SERVER_API inline std::string generateHash(const std::string& password)
	{
		return BCrypt::generateHash(password);
	}

	AURORA_SERVER_API inline bool verifyPassword(const std::string& password, const std::string& hash)
	{
		return BCrypt::validatePassword(password, hash);
	}
}