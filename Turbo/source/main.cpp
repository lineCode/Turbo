#include "turbo/application.h"

using TURBO::Application;
using namespace GUI;
using namespace GEOMETRY;
using namespace AUDIO;
using namespace SCRIPT;

int main(int argc, char ** argv)
{
    Application app = Application();

    return app.run();
}