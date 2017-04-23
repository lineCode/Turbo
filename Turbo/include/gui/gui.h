#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

/**
*** @module     gui
*** @author     Christoph Zorn
*** @date       24.02.2017
***
*** @brief      The module gui contains
***
***
**/

#include "Turbo_main.h"
#include "geometry/geometry.h"
#include "extern/extern.h"
#include "extern/parser.h"
#include "extern/directory.h"

namespace GUI
{
    /**
    *** @enum RENDER_MODE
    **/
    enum class RENDER_MODE : Uint8
    {
        SOLID   = 0,
        SHADED  = 1,
        BLENDED = 2
    };

    /**
    *** @struct Animation
    **/
    struct Animation
    {
        std::string name            = "";
        Uint32      top_offset      = 0;
        Uint32      left_offset     = 0;
        Uint32      frames          = 0;
        Uint32      frame_time      = 0;
        Uint32      curr_frame      = 0;
        Uint32      frame_width     = 0;
        Uint32      frame_height    = 0;
        Uint32      frame_cols      = 0; //TODO better remove
    };

    /**
    *** @struct Color
    ***
    *** @brief
    **/
    struct Color
    {
        Uint8 r = 0;
        Uint8 g = 0;
        Uint8 b = 0;
        Uint8 a = 255;

        Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
        Color toGrayscale();
        SDL_Color toSDL_Color();
    };

    /**
    *** @class Window
    ***
    *** @var
    **/
    class Window
    {
    private:
        const std::string   TAG     = "Window";
        GEOMETRY::Rectangle dimension;
        SDL_Window        * window  = nullptr;

    protected:

    public:
        Window(std::string title, GEOMETRY::Rectangle dimension, Uint32 flags);
        SDL_Window        * getWindow();
        void                setBordered(bool bordered);
        bool                isBordered();
        void                setFulllscreen(bool fullscreen);
        bool                isFullscreen();
        void                setBrightness(float brightness);
        float               getBrightness();
        ~Window();
    };


    /**
    *** @class IRenderer
    ***
    *** @brief  The IRenderer class offers an interface for a renderer which will be
    ***         connected to a SDL_Window.
    ***
    *** @var
    **/
    class IRenderer
    {
    private:
        const std::string   TAG         = "IRenderer";
        SDL_Renderer      * renderer    = nullptr;
        Color               reset_color = {0, 0, 0, 255};
        Color               draw_color  = {0, 0, 0, 0};

    protected:
        //TODOstd::list<Texture>  scene_objects;

    public:
        IRenderer(Window & window, Uint32 flags);
        SDL_Renderer      * getRenderer();
        void                setResetColor(Color color);
        Color               getResetColor();
        Color               getDrawColor();
        void                setDrawColor(Color color);
        void                drawPoint(Point p, Color color);
        void                drawLine(Line l, Color color);
        void                drawTriangle(Triangle t, Color color);
        //void                drawFilledTriangle(Triangle t, Color color);
        void                drawRectangle(Rectangle r, Color color);
        void                drawFilledRectangle(Rectangle r, Color color);
        void                drawShape(IShape s, Color color);
        //void                drawFilledShape(IShape s, Color color);
        //TODOvirtual void        draw(Texture & texture);
        virtual void        present();
        virtual void        clear();
        ~IRenderer();
    };


    /**
    *** @class Sprite
    ***
    *** @brief  The Sprite class can load images from the file system. This image will
    ***         stored in a SDL_Surface and can be converted into a Texture.
    ***
    *** @var
    **/
    class Sprite
    {
    private:
        const std::string       TAG     = "Sprite";
        std::string             file_path;
        EXTERN::XML             xml;
        SDL_Surface           * surface = nullptr;
        std::vector<Animation>  animations;

    protected:

    public:
        Sprite(std::string      file_path);
        SDL_Surface           * getSurface();
        Sprite(std::string      file_path, bool xml = true);
        ~Sprite();
    };


    /**
    *** @class Font
    ***
    *** @var
    **/
    class Font
    {
    private:
        const std::string   TAG     = "Font";
        std::string         file_path;
        TTF_Font          * font    = nullptr;

    protected:

    public:
        Font(std::string file_path, bool xml = true);
        TTF_Font          * getFont();
        int                 getHeight();
        void                setOutline(Uint8 outline);
        void                setKerning(Uint8 kerning);
        void                setHinting(Uint8 hinting);
        void                setFontStyle(Uint8 style);
        ~Font();
    };

    //GEOMETRY::Rectangle   getSize(std::string text, Font & font);
    //GEOMETRY::Rectangle   getSizeUTF8(std::string text, Font & font);
    //GEOMETRY::Rectangle   getSizeUNICODE(std::string text, Font & font);


    /**
    *** @class  Texture
    ***
    *** @brief  The texture class holds a single SDL_Texture that is rendered via the GPU.
    ***
    *** @var
    **/
    class Texture
    {
    private:
        const std::string   TAG     = "Texture";
        SDL_Texture       * texture = nullptr;

    protected:

    public:
        Texture(IRenderer & renderer, Sprite & sprite);
        bool setTextureFromText(IRenderer & renderer, Font & font, std::string text,
                                RENDER_MODE mode, Color color_fg,
                                Color color_bg = {0, 0, 0, 0});
        ~Texture();
    };

    /**
    *** @class  Cursor
    ***
    *** @brief
    **/
    class Cursor
    {
    private:
        const string TAG = "Cursor";

        SDL_Cursor * cursor;

    protected:

    public:
        Cursor();
        void showCursor(bool show);
        ~Cursor();
    };



    /**
    *** @class GUIRenderer
    ***
    *** @var
    **/
    class GUIRenderer : public IRenderer
    {
    private:
        const std::string   TAG = "GUIRenderer";
        GEOMETRY::Rectangle dimension;

    protected:

    public:
        GUIRenderer(Window & window, GEOMETRY::Rectangle dimension, Uint32 flags);
        void draw(Texture texture);
        ~GUIRenderer();
    };


    /**
    *** @class GameRenderer
    ***
    *** @var
    **/
    class GameRenderer : public IRenderer
    {
    private:
        const std::string TAG = "GameRenderer";

    protected:

    public:
        GameRenderer(Window & window, Uint32 flags);
        void draw(Texture texture);
        ~GameRenderer();
    };

}

#endif // GUI_H_INCLUDED
