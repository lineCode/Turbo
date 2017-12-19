#include "util/dir.h"

namespace TURBO
{
    namespace UTIL
    {
        Dir::Dir(std::string directory)
        {
            DIR   		  * dir 	= opendir(directory.c_str());
            struct dirent * entry;

            if(dir != nullptr)
            {
                while((entry = readdir(dir)) != nullptr)
                {
                    if(entry->d_name != (std::string)"." && entry->d_name != (std::string)"..")
                    {
                        std::string handle = directory + entry->d_name;
                        if(Dir::isDir(handle))
                        {
                            this->dirs.push_back(handle);
                        }
                        else if(Dir::isFile(handle))
                        {
                            this->files.push_back(handle);
                        }
                    }
                }
            }
        }

        bool Dir::isDir(std::string name)
        {
            bool success = false;
            DIR * dir = opendir(name.c_str());

            if(dir != nullptr)
            {
                success = true;
            }
            return success;
        }

        bool Dir::isFile(std::string name)
        {
            bool success = false;

            if(!Dir::isDir(name))
            {
                if(Dir::fileExists(name))
                {
                    success = true;
                }
            }
            return success;
        }

        bool Dir::fileExists(std::string name)
        {
            std::fstream f(name);
            return f.good();
        }

        std::vector<std::string> Dir::getDirs()
        {
            return this->dirs;
        }

        std::vector<std::string> Dir::getFiles()
        {
            return this->files;
        }

    }
}