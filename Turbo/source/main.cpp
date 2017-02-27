#include "turbo/application.h"
#include "gui/gui_object.h"

using TURBO::Application;

int main(int argc, char ** argv)
{
    Application app = Application();
    return app.run();
}