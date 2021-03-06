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

        void LayoutContainer::pollEvent(SDL_Event *event)
        {
            Object::pollEvent(event);

            for(auto & child : children)
            {
                child->pollEvent(event);
            }
        }

        Object *LayoutContainer::setChild(Object *object)
        {
            return this;
        }

        Box::Box(Object *parent, ORIENTATION orientation)
            : LayoutContainer(parent), orientation(orientation)
        {

        }

        Box *Box::setOrientation(ORIENTATION orientation)
        {
            this->orientation = orientation;
            update();
            return this;
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
            Object::update();

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
            for(auto i : MATH::range<Uint8>(x, x+w, 1))
            {
                for(auto j : MATH::range<Uint8>(y, y+h, 1))
                {
                    removeWidget(i, j);
                }
            }

            children[std::pair<Uint8, Uint8>(x, y)] = object;

            Sint32 x_pos = space.x + x * cell_width;
            Sint32 y_pos = space.y + y * cell_height;
            object->setSpace(MATH::Rect(x_pos, y_pos, w * cell_width, h * cell_height));
            object->setSize(object->getSpace());
            object->setContent(object->getSpace());
            object->setBackgroundTextureRect(object->getSpace());
            return this;
        }

        Grid *Grid::removeWidget(Object *object)
        {
            //children.erase(std::find(children.begin(), children.end(), object));
            return this;
        }

        Grid *Grid::removeWidget(Uint8 x, Uint8 y)
        {
            children.erase(std::pair<Uint8, Uint8>(x, y));
            return this;
        }

        Grid *Grid::update()
        {
            Object::update();

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

        void Grid::pollEvent(SDL_Event *event)
        {
            Object::pollEvent(event);

            for(auto & child : children)
            {
                child.second->pollEvent(event);
            }
        }
    }
}