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
            if(Dir::isFile(name))
            {
                if(toLower(name.substr(name.rfind('.') + 1, name.length() - name.rfind('.') - 1)) == toLower(type))
                {
                    return true;
                }
            }
            return false;
        }

        bool File::hasFilter(const std::string name, const std::string filter)
        {
            if(filter.find(',') != std::string::npos)
            {
                return File::hasFilter(name, explode(filter, ','));
            }
            else
            {
                return File::isType(name, filter);
            }
        }

        bool File::hasFilter(const std::string name, const std::vector<std::string> filter)
        {
            for(auto & s : filter)
            {
                if(File::isType(name, s))
                {
                    return true;
                }
            }
            return false;
        }
    }
}