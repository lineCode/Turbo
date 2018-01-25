#include "util/string.h"

namespace TURBO
{
    namespace UTIL
    {
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
    }
}