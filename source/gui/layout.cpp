#include "gui/layout.h"

namespace TURBO
{
    namespace GUI
    {
        LayoutContainer::LayoutContainer(Object *parent)
            : Object(parent)
        {
            object_type = OBJECT_TYPE::LAYOUT;
        }

        std::vector<Object *> LayoutContainer::getChildren()
        {
            return children;
        }

        void LayoutContainer::draw(VIDEO::Renderer *renderer)
        {
            for(const auto & child : children)
            {
                child->draw(renderer);
            }
        }

        Box::Box(Object *parent, ORIENTATION orientation)
            : LayoutContainer(parent), orientation(orientation)
        {

        }

        Box *Box::addWidget(Object *object, int index)
        {
            if(index == -1)
            {
                children.push_back(object);
            }
            else
            {
                children.insert(children.begin() + index, object);
            }
            update();
            return this;
        }

        Box *Box::removeWidget(Object *object)
        {
            children.erase(std::find(children.begin(), children.end(), object));
            update();
            return this;
        }

        Box *Box::removeWidget(int index)
        {
            children.erase(children.begin() + index);
            update();
            return this;
        }

        Box *Box::update()
        {
            MATH::Rect children_space = space;
            if(orientation == ORIENTATION::HORIZONTAL)
            {
                children_space.div(0, 0, static_cast<Sint32>(children.size()), 0);
            }
            else if(orientation == ORIENTATION::VERTICAL)
            {
                children_space.div(0, 0, 0, static_cast<Sint32>(children.size()));
            }

            for(auto & child : children)
            {
                child->setSpace(children_space);
                child->setSize(children_space);
                child->setPosition(children_space.topLeft());
                if(orientation == ORIENTATION::HORIZONTAL)
                {
                    children_space.add(children_space.w, 0, 0, 0);
                }
                else if(orientation == ORIENTATION::VERTICAL)
                {
                    children_space.add(0, children_space.h, 0, 0);
                }
                child->update();
            }
        }

        Grid::Grid(Object *parent, Uint8 cols, Uint8 rows)
            : LayoutContainer(parent), cols(cols), rows(rows), cell_width(size.w / cols), cell_height(size.h / 2)
        {

        }

        Grid *Grid::addWidget(Object *object, Uint8 x, Uint8 y, Uint8 w, Uint8 h)
        {
            children[std::pair<Uint8, Uint8>(x, y)] = object;

            Sint32 x_pos = space.x + x * cell_width;
            Sint32 y_pos = space.y + x * cell_height;
            object->setSpace(MATH::Rect(x_pos, y_pos, w * cell_width, h * cell_height));
            object->setSize(object->getSpace());
            return this;
        }

        Grid *Grid::removeWidget(Object *object)
        {
            //children.erase(std::find(children.begin(), children.end(), object));
            return this;
        }

        Grid *Grid::removeWidget(Uint8 x, Uint8 y)
        {
            //children.erase(children.begin(), std::pair<Uint8, Uint8>(x, y));
            return this;
        }

        Grid *Grid::update()
        {
            cell_width = size.w / cols;
            cell_height = size.h / rows;
        }

        void Grid::draw(VIDEO::Renderer *renderer)
        {
            for(auto const & child : children)
            {
                child.second->draw(renderer);
            }
        }
    }
}