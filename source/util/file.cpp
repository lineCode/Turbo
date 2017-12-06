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
    }
}