#ifndef TURBO_TYPE_H
#define TURBO_TYPE_H

#include "util/util_def.h"

namespace TURBO
{
    namespace UTIL
    {
        template<typename T>
        std::string typeName()
        {
            std::string type_name = __PRETTY_FUNCTION__;
            size_t signature_length = 12;
            size_t temp_offset = 10;
            size_t temp_start = type_name.find('[', signature_length);
            size_t temp_end = type_name.find(';', temp_start);
            std::string type = type_name.substr(temp_start + temp_offset, temp_end - temp_start - temp_offset);
            return type;
        }

        template<typename T>
        std::string rawTypeName()
        {
            std::string type_name = typeName<T>();
            std::string type = type_name.substr(type_name.find_last_of(':') + 1);
            return type;
        }
    }
}

#endif //TURBO_TYPE_H
