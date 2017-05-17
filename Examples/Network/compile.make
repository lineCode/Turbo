#======================================================================================
# Check OS
#======================================================================================

ifeq ($(OS),Windows_NT)
    CCFLAGS                  = -D WIN32
    SYSTEM                  := WINDOWS
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
    	ARCHITECTURE        := AMD64
        CCFLAGS              = -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            ARCHITECTURE    := AMD64
            CCFLAGS          = -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            ARCHITECTURE    := IA32
            CCFLAGS          = -D IA32
        endif
    endif
else
    SYSTEM 	:= UNDEFINED
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    	SYSTEM              := LINUX
        CCFLAGS              = -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
    	SYSTEM              := OSX
        CCFLAGS              = -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
    	ARCHITECTURE        := AMD64
        CCFLAGS              = -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
    	ARCHITECTURE        := IA32
        CCFLAGS              = -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
    	ARCHITECTURE        := ARM
        CCFLAGS              = -D ARM
    endif
endif

ifeq ($(SYSTEM), WINDOWS)
	LIB 		:= -LC:/Libs/SDL/lib -LC:/Libs/Python/libs
	INC 		+= -I./include -IC:/Libs/SDL/include -IC:/Libs/Python/include
	LINK += -lpython34 -lmingw32
else
	LIB		:= -L/usr/lib
	INC		+= -I./include -I/usr/include/SDL2 -I/usr/include/python3.5
	LINK += -lpython3.5m
endif

INC         += -I../../Turbo/include/
LINK		+= -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

OBJECTS		= obj/Debug/script/script.o obj/Debug/extern/parser.o obj/Debug/extern/directory.o obj/Debug/extern/extern.o obj/Debug/extern/time.o obj/Debug/net/net.o obj/Debug/turbo/default.o obj/Debug/turbo/application.o obj/Debug/geometry/geometry.o obj/Debug/utils/log.o obj/Debug/gui/gui.o obj/Debug/gui/gui_widget.o obj/Debug/gui/gui_object.o obj/Debug/event/event_listener.o obj/Debug/event/event_device.o obj/Debug/audio/audio.o obj/Debug/system/system.o 
OBJECTS		:= $(foreach d, $(OBJECTS), $(addprefix ../../Turbo/,$(d)))

server: $(OBJECTS) server.o
	@g++ $(OBJECTS) server.o -o Server $(INC) $(LIB) $(LINK)
	@echo Done: Server
	
server.o: server.cpp
	@g++ -std=c++11 -c server.cpp $(INC) -o server.o


client: $(OBJECTS) client.o
	@g++ $(OBJECTS) client.o -o Client $(INC) $(LIB) $(LINK)
	@echo Done: Client
	
client.o: client.cpp
	@g++ -std=c++11 -c client.cpp $(INC) -o client.o
