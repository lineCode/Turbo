#include "gui/main_widget.h"

namespace TURBO
{
    namespace GUI
    {
        MainWidget::MainWidget(VIDEO::Window & window, VIDEO::Renderer & renderer)
            : Widget(nullptr), window(window), renderer(renderer)
        {
            MATH::Rect window_size = window.getSize();
            setSpace(MATH::Rect(0, 0, window_size.w, window_size.h));
            setPosition(MATH::Point(0, 0));
            setSize(getSpace());
            setContent(getSpace());
        }

        VIDEO::Renderer &MainWidget::getRenderer()
        {
            return renderer;
        }
    }
}