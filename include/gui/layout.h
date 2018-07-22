#ifndef TURBO_LAYOUT_H
#define TURBO_LAYOUT_H

#include <vector>
#include <algorithm>

#include "gui/object.h"

namespace TURBO
{
    namespace GUI
    {
        class LayoutContainer : public Object
        {
        protected:
            std::vector<Object*> children;
            
        public:
            explicit LayoutContainer(Object *parent);
            std::vector<Object*> getChildren();
            void draw(VIDEO::Renderer *renderer) override;
            void pollEvent(SDL_Event &event) override;
            Object* setChild(Object *object) override;
        };
        
        class Box : public LayoutContainer
        {
        protected:
            ORIENTATION orientation;

        public:
            explicit Box(Object *parent, ORIENTATION orientation = ORIENTATION::HORIZONTAL);
            Box *setOrientation(ORIENTATION orientation);
            Box *addWidget(Object *object, int index = -1);
            Box *removeWidget(Object *object);
            Box *removeWidget(int index);
            Box *update() override;
        };

        class Grid : public LayoutContainer
        {
        private:
            std::map<std::pair<Uint8, Uint8>, TURBO::GUI::Object*> children;
            Uint8 cols;
            Uint8 rows;
            Sint32 cell_width = 0;
            Sint32 cell_height = 0;

        public:
            explicit Grid(Object * parent, Uint8 cols, Uint8 rows);
            Grid *addWidget(Object *object, Uint8 x, Uint8 y, Uint8 w, Uint8 h);
            Grid *removeWidget(Object *object);
            Grid *removeWidget(Uint8 x, Uint8 y);
            Grid *update() override;
            void draw(VIDEO::Renderer *renderer) override;
            void pollEvent(SDL_Event &event) override;
        };
    }
}

#endif //TURBO_LAYOUT_H
