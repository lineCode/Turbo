#include "gui/gui.h"

using namespace GUI;
using GEOMETRY::Rectangle;
using GEOMETRY::Point;
using EXTERN::XML;

Window::Window(string title, Rectangle dimension, Uint32 flags)
    : dimension(dimension)
{
    this->window = SDL_CreateWindow(title.c_str(),
                                    round(dimension.getX()), round(dimension.getY()),
                                    round(dimension.getWidth()), round(dimension.getLength()),
                                    flags);
}

SDL_Window * Window::getWindow()
{
    return this->window;
}

Window::~Window()
{
    if(this->window != nullptr)
    {
        SDL_DestroyWindow(this->window);
    }
}

IRenderer::IRenderer(Window & window, Uint32 flags)
{
    this->renderer = SDL_CreateRenderer(window.getWindow(), -1, flags);
}

SDL_Renderer * IRenderer::getRenderer()
{
    return this->renderer;
}

SDL_Color IRenderer::getResetColor()
{
    return this->reset_color;
}

void IRenderer::setDrawColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
}

//void IRenderer::draw(Texture & texture)
//{
//    SDL_RenderCopyEx(this->renderer, texture.getTexture(), NULL, NULL, 0, NULL, SDL_FLIP_NONE);
//}

void IRenderer::present()
{
    SDL_RenderPresent(this->renderer);
}

void IRenderer::clear()
{
    SDL_RenderClear(this->renderer);
}

IRenderer::~IRenderer()
{
    if(this->renderer != nullptr)
    {
        SDL_DestroyRenderer(this->renderer);
    }
}

/**
 * @brief Loads an image from the file system
 *
 * @param file_path the path to the image or path to xml file
 * @param is_xml    defines if file is from type xml
 */
Sprite::Sprite(string file_path, bool is_xml)
{
    if(is_xml)
    {
        if(EXTERN::Directory::isType(file_path, "xml"))
        {
            EXTERN::XMLParser parser(file_path);
            XML xml = parser.getXML();
            XML sp = xml.findTag("Sprite");
            if(!sp.isEmpty())
            {
                string rel_path = sp.getValue("relPath");
                if(rel_path != "")
                {
                    file_path = rel_path;
                }
            }
        }
    }
    this->file_path = file_path;

    if(EXTERN::Directory::hasFilter(file_path, TURBO::SDL_IMG_FILE_FILTER))
    {
        if(EXTERN::Directory::isFile(file_path))
        {
            this->surface = IMG_Load(file_path.c_str());
        }
    }
}

SDL_Surface * Sprite::getSurface()
{
    return this->surface;
}

Sprite::~Sprite()
{
    if(this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
    }
}

Font::Font(std::string file_path, bool is_xml)
{
    if(is_xml)
    {
        if(EXTERN::Directory::isType(file_path, "xml"))
        {
            EXTERN::XMLParser parser(file_path);
            XML xml = parser.getXML();
            XML sp = xml.findTag("Font");
            if(!sp.isEmpty())
            {
                string rel_path = sp.getValue("relPath");
                if(rel_path != "")
                {
                    file_path = rel_path;
                }
            }
        }
    }
    this->file_path = file_path;

    if(EXTERN::Directory::isType(file_path, "ttf"))
    {
        this->font = TTF_OpenFont(file_path.c_str(), 12);
    }
}

TTF_Font * Font::getFont()
{
    return this->font;
}

int Font::getHeight()
{
    return TTF_FontHeight(this->font);
}

void Font::setOutline(Uint8 outline)
{
    TTF_SetFontOutline(this->font, outline);
}

void Font::setKerning(Uint8 kerning)
{
    TTF_SetFontKerning(this->font, kerning);
}

void Font::setHinting(Uint8 hinting)
{
    TTF_SetFontHinting(this->font, hinting);
}

void Font::setFontStyle(Uint8 style)
{
    TTF_SetFontStyle(this->font, style);
}

Font::~Font()
{
    if(this->font != nullptr)
    {
        TTF_CloseFont(this->font);
    }
}
/*
Rectangle Text::getSize(string text, Font & font)
{
    Rectangle rect;
    int w = 0;
    int h = 0;

    if(TTF_SizeText(font, text.c_str(), &w, &h) == 0)
    {
        rect = Rectangle(0, 0, w, h);
    }
    else
    {
        Log::error(this->tag, TTF_GetError());
    }

    return rect;
}

Rectangle Text::getSizeUTF8(string text, Font & font)
{

}
*/
Texture::Texture(IRenderer & renderer, Sprite & sprite)
{
    if(sprite.getSurface() != nullptr)
    {
        this->texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), sprite.getSurface());
    }
}

bool Texture::setTextureFromText(IRenderer & renderer, Font & font, std::string text,
                                 RENDER_MODE mode, SDL_Color color_fg, SDL_Color color_bg)
{
    bool success = false;
    SDL_Surface * surface = nullptr;

    switch(mode)
    {
    case RENDER_MODE::SOLID:
        {
            surface = TTF_RenderUNICODE_Solid(font.getFont(), (Uint16 *)text.c_str(), color_fg);
            break;
        }
    case RENDER_MODE::SHADED:
        {
            surface = TTF_RenderUNICODE_Shaded(font.getFont(), (Uint16 *)text.c_str(), color_fg, color_bg);
            break;
        }
    case RENDER_MODE::BLENDED:
        {
            surface = TTF_RenderUNICODE_Blended(font.getFont(), (Uint16 *)text.c_str(), color_fg);
            break;
        }
    }
    if(surface != nullptr)
    {
        this->texture = SDL_CreateTextureFromSurface(renderer.getRenderer(), surface);
        SDL_FreeSurface(surface);
    }
    if(this->texture != nullptr)
    {
        success = true;
    }
    return success;
}

Texture::~Texture()
{
    if(this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
    }
}

GUIRenderer::GUIRenderer(Window & window, Rectangle dimension, Uint32 flags)
    : IRenderer(window, flags), dimension(dimension)
{

}

void GUIRenderer::draw(Texture texture)
{

}

GUIRenderer::~GUIRenderer()
{

}

GameRenderer::GameRenderer(Window & window, Uint32 flags)
    : IRenderer(window, flags)
{

}

void GameRenderer::draw(Texture texture)
{

}

GameRenderer::~GameRenderer()
{

}