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

static std::vector<std::string> cmd_buffer;
static int cmd_index = 0;

void my_quit(int s)
{
    std::cout << "\n";
    exit(1);
}

std::string getLine()
{
    std::string command;
    int c;

    while((c = std::cin.get()))
    {
        switch(c)
        {
            case 10:
            {
                return command;
            }
            default:
            {
                command += (char)c;
            }
        }
    }
    return command;
}

void python(int argc, char ** argv)
{
    TC::Python::addModule("Turbo", TC::PyInit_Turbo);
    TC::Python::setProgramName(argv[0]);
    TC::Python::initialize();
    TS::Platform::setEnvironment("PYTHONPATH", "./resources/script/python/", true);

    PyObject *moduleMain = TC::Python::importModule(TC::Python::toUnicode("__main__"));

    TS::SignalHandler::addSignal(SIGINT, my_quit);

    std::string input;
    input = getLine();

    while(input != "exit")
    {
        // print errors in bold red
        TU::Log::startFormat(TU::LOG_FORMAT::BOLD_ON);
        TU::Log::startFormat(TU::LOG_FORMAT::FG_LIGHT_RED);
        TC::Python::runString(input);
        TU::Log::clearFormat();

        // get next input
        input = getLine();
    }

    TC::Python::freeProgram(argv[0]);
}