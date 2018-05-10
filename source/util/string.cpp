#include "util/string.h"

namespace TURBO
{
    namespace UTIL
    {
        std::string toUnicode(Uint16 code)
        {
            char chars[5];

            // 0x00 - 0x7F
            if(code <= 0x7F)
            {
                chars[0] = static_cast<char>(code & 0x7F);
                chars[1] = '\0';
            }
                // 0x080 - 0x7FF
            else if(code <= 0x7FF)
            {
                chars[1] = static_cast<char>(0x80 | (code & 0x3F));
                chars[0] = static_cast<char>(0xC0 | ((code >> 6) & 0x1F));
                chars[2] = '\0';
            }
                // 0x8000 - 0xFFFF
            else if(code <= 0xFFFF)
            {
                chars[2] = static_cast<char>(0x80 | (code & 0x3F));
                chars[1] = static_cast<char>(0x80 | ((code >> 6) & 0x3F));
                chars[0] = static_cast<char>(0xE0 | ((code >> 12) & 0xF));
                chars[3] = '\0';
            }
                // 0x10000 - 0x10FFFF
            else if(code <= 0x10FFFF)
            {
                chars[3] = static_cast<char>(0x80 | (code & 0x3F));
                chars[2] = static_cast<char>(0x80 | ((code >> 6) & 0x3F));
                chars[1] = static_cast<char>(0x80 | ((code >> 12) & 0x3F));
                chars[0] = static_cast<char>(0xF0 | ((code >> 18) & 0x7));
                chars[4] = '\0';
            }
            else
            {
                chars[0] = static_cast<char>(0x0);
                chars[1] = '\0';
            }

            return std::string(chars);
        }

        std::string trim(const std::string & str, const std::string & whitespace)
        {
            const auto strBegin = str.find_first_not_of(whitespace);

            if(strBegin == std::string::npos)
            {
                return "";
            }

            const auto strEnd = str.find_last_not_of(whitespace);
            const auto strRange = strEnd - strBegin + 1;

            return str.substr(strBegin, strRange);
        }

        std::string toLower(std::string haystack)
        {
            std::transform(haystack.begin(), haystack.end(), haystack.begin(), ::tolower);
            return haystack;
        }

        std::vector<std::string> explode(std::string haystack, char needle)
        {
            std::vector<std::string> result;
            std::istringstream iss(haystack);

            for(std::string token; std::getline(iss, token, needle); )
            {
                result.push_back(std::move(token));
            }
            return result;
        }

        std::string implode(std::vector<std::string> haystack, const std::string needle)
        {
            std::string result;

            for(const auto & s : haystack)
            {
                result += s + needle;
            }
            return result.substr(0, result.rfind(needle) - 1);
        }

        std::string replace(std::string haystack, char needle, char replace)
        {
            std::replace(haystack.begin(), haystack.end(), needle, replace);
            return haystack;
        }

        std::string removeSpaces(std::string &haystack)
        {
            haystack.erase(std::remove_if(haystack.begin(), haystack.end(), ::isspace), haystack.end());
            return haystack;
        }
    }
}