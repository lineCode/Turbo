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

        bool Dir::isType(const std::string name, const std::string type)
        {
            bool success = false;
            if(Dir::isFile(name))
            {
                if(name.substr(name.rfind('.') + 1, name.length() - name.rfind('.') - 1) == toLower(type))
                {
                    success = true;
                }
            }
            return success;
        }

        bool Dir::hasFilter(const std::string name, const std::string filter)
        {
            bool success = false;

            if(filter.find(',') != std::string::npos)
            {
                success = Dir::hasFilter(name, explode(filter, ','));
            }
            else
            {
                success = Dir::isType(name, filter);
            }
            return success;
        }

        bool Dir::hasFilter(const std::string name, const std::vector<std::string> filter)
        {
            bool success = false;

            for(std::string s : filter)
            {
                if(Dir::isType(name, s))
                {
                    success = true;
                }
            }
            return success;
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