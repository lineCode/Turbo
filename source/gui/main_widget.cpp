#include "gui/main_widget.h"

namespace TURBO
{
    namespace GUI
    {
        MainWidget::MainWidget(VIDEO::Window & window, VIDEO::Renderer & renderer)
            : Widget(nullptr), window(window), renderer(renderer)
        {
            MATH::Rect window_size = window.getSize();
            setGeometry(MATH::Rect(0, 0, window_size.w, window_size.h));
            setSize(MATH::Rect(0, 0, window_size.w, window_size.h));
        }
    }
}