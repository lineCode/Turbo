#ifndef TURBO_FILE_H
#define TURBO_FILE_H

#include <fstream>
#include <string>
#include <vector>

#include "util/util_def.h"
#include "util/dir.h"

namespace TURBO
{
    namespace UTIL
    {
        class File
        {
        public:
            static bool isType(std::string name, std::string type);
            static bool hasFilter(std::string name, std::string filter);
            static bool hasFilter(std::string name, std::vector<std::string> filter);
            static std::string getFileContents(std::string filename);
            static void putFileContents(std::string filename, std::string content);
        };
    }
}

#endif //TURBO_FILE_H
