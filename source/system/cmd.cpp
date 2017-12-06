#include "system/cmd.h"

namespace TURBO
{
    namespace SYSTEM
    {
        CMDParser::CMDParser(int argc, char ** argv)
            : argc(argc), argv(argv)
        {

        }

        bool CMDParser::checkArgs()
        {
            bool valid = true;
            trace = "";

            for(int i = 1; i < argc; ++i)
            {
                std::string arg = argv[i];
                if(options.count(arg))
                {
                    // Parameters
                    if(options[arg][0] > 0)
                    {
                        int param = 0;
                        while(param < options[arg][0])
                        {
                            if(i != argc - 1 && param != argc - 1 && argv[i+1][0] != '-')
                            {
                                std::string val = argv[++i];
                                if(args[arg].empty())
                                {
                                    args[arg] = std::vector<std::string>{val};
                                }
                                else
                                {
                                    args[arg].push_back(val);
                                }
                            }
                            else
                            {
                                args[arg] = std::vector<std::string>{""};
                                std::string war = (options[arg][0] - param == 1) ? "value" : "values";
                                trace += "missing " + war += " for command " + arg += "\n";
                                valid = false;
                                break;
                            }
                            param++;
                        }
                    }
                    else
                    {
                        args[arg] = std::vector<std::string>{""};
                    }
                }
            }
            for(auto option : options)
            {
                if(option.second[1])
                {
                    if(!args.count(option.first))
                    {
                        trace += "missing command " + option.first + "\n";
                        valid = false;
                    }
                }
            }
            return valid;
        }

        void CMDParser::setOption(const std::string option, const Uint8 params, const bool required, const std::string info)
        {
            if(option.length() > largest_option)
                largest_option = static_cast<Uint8>(option.length() + 1);
            if(params * 8 + 3 > largest_params)
                largest_params = static_cast<Uint8>(params * 8 + 4);

            options[option] = std::vector<Uint8>{params, static_cast<Uint8>(required)};
            option_info[option] = info;
        }

        std::vector<std::string> CMDParser::getOption(std::string option)
        {
            if(option[0] != '-')
                option = '-' + option;
            return args[option];
        }

        bool CMDParser::isSet(std::string option)
        {
            return (args.count(option) == 1);
        }

        std::string CMDParser::getTrace()
        {
            return trace;
        }

        void CMDParser::printTrace()
        {
            std::cout << getTrace() << std::endl;
        }

        std::string CMDParser::getHelp()
        {
            std::ostringstream help;
            help << "\nUsage:\n    -command [argument list]\n\nCommands:\n";
            for(auto option : options)
            {
                help << "    " << std::left << std::setfill(' ') << std::setw(largest_option) << option.first;
                if(option.second.at(0))
                {
                    std::string params = "[";
                    for(int i = 0; i < option.second.at(0); ++i)
                    {
                        params += "param" + std::to_string(i);
                        if(i != option.second.at(0) - 1)
                        {
                            params += " ";
                        }
                    }
                    help << std::left << std::setfill(' ') << std::setw(largest_params) << (params + "]");
                }
                else
                {
                    help << std::left << std::setfill(' ') << std::setw(largest_params) << "";
                }
                if(option.second.at(1))
                {
                    help << std::left << std::setfill(' ') << std::setw(19) << "(command required)";
                }
                else
                {
                    help << std::left << std::setfill(' ') << std::setw(19) << "";
                }
                help << option_info[option.first] + "\n";
            }
            return help.str();
        }

        void CMDParser::printHelp()
        {
            std::cout << getHelp() << std::endl;
        }
    }
}