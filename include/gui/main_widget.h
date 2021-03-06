#ifndef TURBO_MAIN_WIDGET_H
#define TURBO_MAIN_WIDGET_H

#include "gui/widget.h"
#include "video/video.h"

namespace TURBO
{
    namespace GUI
    {
        class MainWidget final
            : public Widget
        {
        protected:
            VIDEO::Window   &window;
            VIDEO::Renderer &renderer;

        public:
            MainWidget(VIDEO::Window &window, VIDEO::Renderer &renderer);
            VIDEO::Renderer &getRenderer();
        };
    }
}

#endif //TURBO_WINDOW_H
