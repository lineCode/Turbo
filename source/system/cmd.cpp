#include "system/cmd.h"

namespace TURBO
{
    namespace SYSTEM
    {
        CMDParser::CMDParser(int argc, char ** argv)
            : argc(argc), argv(argv)
        {
            setOption("-h", "--help", 0, false, {}, "prints this information");
        }

        bool CMDParser::checkArgs()
        {
            bool valid = true;
            trace = "";
            app_name = argv[0];

            // Arguments
            for(int i = 1; i < argc; ++i)
            {
                std::string arg = argv[i];
                if(arg.substr(0, 2) == "--")
                {
                    arg = arg.substr(1, 2);
                }

                if(options.count(arg) == 0)
                {
                    trace += "- unrecognized option '" + arg + "' found\n";
                }
                else
                {
                    // Parameters
                    int params = 0;
                    std::stringstream ss(options[arg]["params"]);
                    ss >> params;

                    if(params > 0)
                    {
                        int param = 0;

                        while(param < params)
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
                                std::string val = (params - param == 1) ? "value" : "values";
                                trace += "- missing " + val += " for command " + options[arg]["long"] += "\n";
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
            for(auto & option : options)
            {
                if(option.second["required"] == "true")
                {
                    if(!args.count(option.second["short"]))
                    {
                        trace += "- missing command " + option.second["long"] + "\n";
                        valid = false;
                    }
                }
            }
            return valid;
        }

        bool CMDParser::setOption(const std::string short_option, const std::string long_option, const Uint8 params,
                                  const bool required, std::vector<std::string> defaults, const std::string info)
        {
            if(options.count(short_option) > 0)
            {
                return false;
            }
            if(!std::regex_match(short_option, std::regex("-[a-zA-Z]")))
            {
                return false;
            }
            if(!std::regex_match(long_option, std::regex("--[a-zA-Z]+[a-zA-Z-]*")))
            {
                return false;
            }
            if(short_option != long_option.substr(1, 2))
            {
                return false;
            }

            Uint64 arg_len = long_option.length() + 1;
            if(arg_len > largest_option)
            {
                largest_option = static_cast<Uint8>(arg_len);
            }

            options[short_option]["short"] = short_option;
            options[short_option]["long"] = long_option;
            options[short_option]["params"] = std::to_string(params);
            options[short_option]["required"] = (required) ? "true" : "false";
            options[short_option]["defaults"] = UTIL::implode(defaults, ",");
            options[short_option]["info"] = info;

            return true;
        }

        std::map<std::string, std::string> CMDParser::getOption(std::string option)
        {
            if(std::regex_match(option, std::regex("--[a-zA-Z]+[a-zA-Z-]*")))
            {
                option = option.substr(1, 2);
            }

            if(options.count(option) > 0)
            {
                return options[option];
            }
            else
            {
                return {};
            }
        }

        bool CMDParser::isSet(std::string argument)
        {
            return (args.count(argument) == 1);
        }

        std::vector<std::string> CMDParser::getArgument(const std::string argument)
        {
            if(isSet(argument))
            {
                return args[argument];
            }
            return {};
        }

        std::string CMDParser::getTrace()
        {
            return trace;
        }

        void CMDParser::printTrace()
        {
            if(!trace.empty())
            {
                std::string head = "Issues while parsing arguments for ";
                std::cout << head << app_name << "\n" << getTrace() << "\n";
            }
        }

        std::string CMDParser::getHelp()
        {
            std::ostringstream help;
            help << "\nUsage:\n    -command [parameter list]\n\nCommands:\n";
            for(auto & option : options)
            {
                help << "  " << std::left << std::setfill(' ') << option.second["short"] << ' '
                     << std::setw(largest_option) << option.second["long"];

                int params = 0;
                std::stringstream ss(option.second["params"]);
                ss >> params;

                if(params > 0)
                {
                    std::string param_string = "[param0";
                    if(params > 1)
                    {
                        param_string += " param1";
                    }
                    if(params > 1 && params < 3)
                    {
                        param_string += " param2";
                    }
                    else if(params > 3)
                    {
                        param_string += " ... param";
                        param_string += std::to_string(params);
                    }
                    help << std::left << std::setfill(' ') << std::setw(27) << (param_string + "]");
                }
                else
                {
                    help << std::left << std::setfill(' ') << std::setw(27) << "";
                }

                if(option.second["required"] == "true")
                {
                    help << std::left << std::setfill(' ') << std::setw(19) << "(command required)";
                }
                else
                {
                    help << std::left << std::setfill(' ') << std::setw(19) << "";
                }
                help << "" << option.second["info"] << "\n";
            }
            return help.str();
        }

        void CMDParser::printHelp()
        {
            std::cout << getHelp() << "\n";
        }
    }
}