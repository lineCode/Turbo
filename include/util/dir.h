#ifndef TURBO_DIR_H
#define TURBO_DIR_H

#include "util/util.h"
#include "dirent.h"

namespace TURBO
{
    namespace UTIL
    {
        class Dir
        {
        private:
            std::vector<std::string> 	dirs;
            std::vector<std::string>	files;

        public:
            explicit Dir(std::string dir);
            static bool 				isDir(std::string name);
            static bool 				isFile(std::string name);
            static bool 				fileExists(std::string name);
            std::vector<std::string> 	getDirs();
            std::vector<std::string> 	getFiles();
        };
    }
}

#endif //TURBO_DIR_H
