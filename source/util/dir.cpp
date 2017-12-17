#include "util/dir.h"

namespace TURBO
{
    namespace UTIL
    {
        Dir::Dir(std::string directory)
        {
            DIR   		  * dir 	= opendir(directory.c_str());
            struct dirent * entry;

            if(dir != NULL)
            {
                while((entry = readdir(dir)) != NULL)
                {
                    if(entry->d_name != (std::string)"." && entry->d_name != (std::string)"..")
                    {
                        std::string handle = entry->d_name;
                        if(this->isDir(entry->d_name))
                        {
                            this->dirs.push_back(handle);
                        }
                        else if(this->isFile(entry->d_name))
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

            if(dir != NULL)
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