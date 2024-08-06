#pragma once

#include <string>
#include <regex>

#include "game/Character.h"

namespace util
{
    namespace MapleTool
    {
        using byte = unsigned char;

        bool isNameLegal(std::string const& name)
        {
            if (name.length() < 3 || name.length() > 12)
            {
                return false;
            }
            std::regex pattern("[a-zA-Z0-9]{3,12}");
            return std::regex_match(name, pattern);
        }

        bool canCreateCharacter(std::string const& name, int world)
        {
            return isNameLegal(name) && !Character::getCharacterIdByName(name, world);
        }
        
        bool hasSymbols(std::string name)
        {
            std::vector<char> symbols =
            {
                '`','~','!','@','#','$','%','^','&','*','(',')','_','-','=','+','{','[',']','}','|',';',':','\'',',','<','>','.','?','/'
            };

            for (byte s = 0; s < symbols.size(); s++)
            {
                if (name.find(symbols[s]) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
        }
    }
}