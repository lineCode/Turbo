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
        };
        
        class Box : public LayoutContainer
        {
        public:
            explicit Box(Object *parent, ORIENTATION orientation = ORIENTATION::HORIZONTAL);
            Box *addWidget(Object *object, int index = -1);
            Box *removeWidget(Object *object);
            Box *removeWidget(int index);
            Box *update() override;
        };
    }
}

#endif //TURBO_LAYOUT_H
