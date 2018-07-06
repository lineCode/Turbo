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

/* Python call */

void python(int argc, char ** argv)
{
    TC::Python::addModule("Turbo", TC::PyInit_Turbo);
    TC::Python::setProgramName(argv[0]);
    TC::Python::initialize();
    TS::Platform::setEnvironment("PYTHONPATH", "./resources/script/python/", true);

    PyObject * moduleMain = TC::Python::importModule(TC::Python::toUnicode("__main__"));

    TC::Python::runString(
        "def mul(a, b):\n"
            "    return a * b\n");

    TC::Python::runString(
        "import Turbo \n"
            "c = Turbo.Point(x=99,y=16)\n"
            "print(c.x, c.y)\n");

    PyObject * f    = TC::Python::getAttritbuteFromString(moduleMain, "mul");
    PyObject * args = TC::Python::toTuple(2, TC::Python::toFloat(3.0), TC::Python::toFloat(4.0));

    PyObject * result = TC::Python::callObject(f, args);

    printf("mul(3,4): %.2f\n", TC::Python::asDouble(result));
}
