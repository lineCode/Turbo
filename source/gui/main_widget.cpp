#include "gui/main_widget.h"

namespace TURBO
{
    namespace GUI
    {
        MainWidget::MainWidget(VIDEO::Window & window, VIDEO::Renderer & renderer)
            : Widget(nullptr), window(window), renderer(renderer)
        {
            setGeometry(window.getGeometry());
        }
    }
}