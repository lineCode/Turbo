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
            DIR * dir = opendir(name.c_str());

            return dir != nullptr;
        }

        bool Dir::isFile(std::string name)
        {
            if(!Dir::isDir(name))
            {
                if(Dir::fileExists(name))
                {
                    return true;
                }
            }
            return false;
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