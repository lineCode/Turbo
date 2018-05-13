######################################################################
# Automatically generated by qmake (3.0) Mi. Dez. 6 16:43:26 2017
######################################################################

TEMPLATE = app
TARGET = Turbo
CONFIG = console c++11

#LIBS += \
# `mysql_config --cflags --libs`
# `sdl2-config --cflags --libs`

LIBS += -L/usr/lib/ \
    -lpthread \
    -lsqlite3 \
    -lmysqlclient \
    -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2_net \
    -llua5.2 \
    -lpython3.5m \
    -lGLEW -lGL

INCLUDEPATH += include \
    /usr/include \
    /usr/include/SDL2 \
    /usr/include/lua5.2 \
    /usr/include/python3.5

OBJECTS_DIR = obj

# Input
HEADERS += include/turbo.h \
           include/turbo_def.h \
           include/audio/audio.h \
           include/audio/audio_def.h \
           include/audio/music.h \
           include/audio/chunk.h \
           include/audio/media_player.h \
           include/gui/button.h \
           include/gui/gui.h \
           include/gui/gui_def.h \
           include/gui/layout.h \
           include/gui/main_widget.h \
           include/gui/object.h \
           include/gui/widget.h \
           include/gui/text_widget.h \
           include/gui/style_properties.h \
           include/input/controller.h \
           include/input/input.h \
           include/input/input_def.h \
           include/input/keyboard.h \
           include/input/mouse.h \
           include/math/math.h \
           include/math/math_def.h \
           include/math/point.h \
           include/math/rect.h \
           include/math/vector.h \
           include/net/net.h \
           include/net/net_def.h \
           include/net/socket.h \
           include/net/tcp.h \
           include/net/udp.h \
           include/script/lua.h \
           include/script/python.h \
           include/script/script.h \
           include/script/script_def.h \
           include/system/cmd.h \
           include/system/sdl.h \
           include/system/system.h \
           include/system/system_def.h \
           include/system/time.h \
           include/util/db.h \
           include/util/dir.h \
           include/util/file.h \
           include/util/ini.h \
           include/util/json.h \
           include/util/log.h \
           include/util/number.h \
           include/util/save.h \
           include/util/string.h \
           include/util/util.h \
           include/util/util_def.h \
           include/util/xml.h \
           include/util/parser.h \
           include/video/color.h \
           include/video/font.h \
           include/video/opengl.h \
           include/video/renderer.h \ \
           include/video/surface.h \ \
           include/video/texture.h \
           include/video/video.h \
           include/video/video_def.h \
           include/video/window.h
SOURCES += test/test.cpp \
           source/turbo.cpp \
           source/audio/music.cpp \
           source/audio/chunk.cpp \
           source/audio/media_player.cpp \
           source/gui/button.cpp \
           source/gui/layout.cpp \
           source/gui/main_widget.cpp \
           source/gui/object.cpp \
           source/gui/widget.cpp \
           source/gui/text_widget.cpp \
           source/gui/style_properties.cpp \
           source/input/controller.cpp \
           source/input/keyboard.cpp \
           source/input/mouse.cpp \
           source/math/math.cpp \
           source/math/point.cpp \
           source/math/rect.cpp \
           source/math/vector.cpp \
           source/net/socket.cpp \
           source/net/tcp.cpp \
           source/net/udp.cpp \
           source/script/lua.cpp \
           source/script/python.cpp \
           source/system/cmd.cpp \
           source/system/sdl.cpp \
           source/system/time.cpp \
           source/util/db.cpp \
           source/util/dir.cpp \
           source/util/file.cpp \
           source/util/ini.cpp \
           source/util/json.cpp \
           source/util/log.cpp \
           source/util/number.cpp \
           source/util/save.cpp \
           source/util/string.cpp \
           source/util/xml.cpp \
           source/util/parser.cpp \
           source/video/color.cpp \
           source/video/font.cpp \
           source/video/opengl.cpp \
           source/video/renderer.cpp \
           source/video/surface.cpp \
           source/video/texture.cpp \
           source/video/window.cpp
