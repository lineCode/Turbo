#include "util/ini.h"

namespace TURBO
{
    namespace UTIL
    {
        std::string INI::getValue(const std::string key, const std::string caption)
        {
            return kvp[caption][key];
        }

        int INI::getValueAsInt(const std::string key, const std::string caption)
        {
            return stoi(getValue(key, caption));
        }

        float INI::getValueAsFloat(const std::string key, const std::string caption)
        {
            return stof(getValue(key, caption));
        }

        void INI::setValue(const std::string key, const std::string value, const std::string caption)
        {
            kvp[caption][key] = value;
        }

        bool INI::isEmpty()
        {
            return kvp.empty();
        }

        void INI::printINI()
        {
            for(const auto & caption : kvp)
            {
                if(!caption.first.empty())
                {
                    std::cout << '[' << caption.first << ']' << "\n";
                }
                for(const auto & kvp : caption.second)
                {
                    std::cout << kvp.first << " = " << kvp.second << "\n";
                }
            }
        }

        INIParser::INIParser(const std::string file)
            : filename(file)
        {
            ini = read(filename);
        }

        INI INIParser::read(const std::string file)
        {
            filename = file;
            std::string line;
            std::string caption;
            std::ifstream in(filename, std::ios::in);
            INI ini;

            while(std::getline(in, line))
            {
                line = trim(line);
                char symbol;
                std::string option, value;
                std::stringstream ss(line);

                if(line.empty())
                {
                    caption = "";
                    continue;
                }
                else if(line[0] == ';' || line[0] == '#')
                {
                    continue;
                }
                else
                {
                    if(line[0] == '[' && line[line.length() - 1] == ']')
                    {
                        ss >> caption;
                        caption = caption.substr(1, caption.length() - 2);
                        continue;
                    }
                    ss >> option >> symbol >> value;
                    ini.setValue(option, value, caption);
                }
            }
            return ini;
        }

        bool INIParser::update()
        {
            return write(filename, ini);
        }

        bool INIParser::write(const std::string & file, INI ini, const std::ios::openmode flags)
        {
            bool success = false;

            std::ofstream out(file, flags);

            for(const auto & caption : ini.kvp)
            {
                if(!caption.first.empty())
                {
                    out << '[' << caption.first << ']' << "\n";
                }
                for(const auto & kvp : caption.second)
                {
                    out << kvp.first << " = " << kvp.second << "\n";
                }
                success = true;
            }
            return success;
        }

        INI INIParser::getINI()
        {
            return ini;
        }
    }
}