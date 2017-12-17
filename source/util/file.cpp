#include "util/file.h"

namespace TURBO
{
    namespace UTIL
    {
        std::string File::getFileContents(const std::string filename)
        {
            std::ifstream ifs(filename);
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                                 (std::istreambuf_iterator<char>()    ) );
            return content;
        }

        void File::putFileContents(const std::string filename, const std::string content)
        {
            std::ofstream out(filename);
            out << content;
            out.close();
        }

        bool File::isType(const std::string name, const std::string type)
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

        bool File::hasFilter(const std::string name, const std::string filter)
        {
            bool success = false;

            if(filter.find(',') != std::string::npos)
            {
                success = File::hasFilter(name, explode(filter, ','));
            }
            else
            {
                success = File::isType(name, filter);
            }
            return success;
        }

        bool File::hasFilter(const std::string name, const std::vector<std::string> filter)
        {
            bool success = false;

            for(std::string s : filter)
            {
                if(File::isType(name, s))
                {
                    success = true;
                }
            }
            return success;
        }
    }
}