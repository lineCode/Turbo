#ifndef TURBO_FILE_H
#define TURBO_FILE_H

#include <fstream>
#include <string>

#include "util/util_def.h"

namespace TURBO
{
    namespace UTIL
    {
        class File
        {
        public:
            static std::string getFileContents(std::string filename);
            static void putFileContents(std::string filename, std::string content);
        };
    }
}

#endif //TURBO_FILE_H
