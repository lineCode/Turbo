#include "turbo.h"

namespace TA = TURBO::AUDIO;
namespace TG = TURBO::GUI;
namespace TCH = TURBO::CHART;
namespace TV = TURBO::VIDEO;
namespace TI = TURBO::INPUT;
namespace TU = TURBO::UTIL;
namespace TM = TURBO::MATH;
namespace TN = TURBO::NET;
namespace TS = TURBO::SYSTEM;
namespace TC = TURBO::SCRIPT;

void cmdParser(int argc, char **argv)
{
    TS::CMDParser cmd_parser = TS::CMDParser(argc, argv);

    cmd_parser.setOption("-w", "--wasp", 2, false, {}, "bzzz");
    cmd_parser.setOption("-o", "--ouch", 99, false, {}, "muh");
    cmd_parser.setOption("-l", "--loop", 1, false, {}, "sets level of looping");
    cmd_parser.setOption("-p", "--pressure", 1, true, {}, "dummy");

    if(!cmd_parser.checkArgs())
    {
        std::cout << TU::Log::format(TU::LOG_FORMAT::FG_YELLOW, "Trace:\n" + cmd_parser.getTrace())
                  << "\n";
    }
    if(cmd_parser.isSet("-h"))
        cmd_parser.printHelp();

    for(const auto &arg : cmd_parser.getArgument("-w"))
    {
        std::cout << arg << " ";
    }
    std::cout << "\n";
}