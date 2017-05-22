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

ifeq ($(SYSTEM),WINDOWS)
	OUTFILE	:= exe
	RM      := del -f
	RMDIR	:= rmdir
	RRMDIR  := rmdir /s
	MKDIR	:= mkdir
	OS_LIB	:= -lmingw32 
else
	OUTFILE	:= out
	RM      := rm
	RMDIR	:= rmdir
	RRMDIR  := rmdir -r
	MKDIR	:= mkdir -p
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

MDLS 		:= $(patsubst %/,%,$(patsubst ../../Turbo/obj/Debug/%,%,$(dir $(wildcard ../../Turbo/obj/Debug/*/))))
OBJD 		:= $(addprefix ../../Turbo/obj/Debug/, $(MDLS))
OBJECTS		:= $(foreach d, $(OBJD), $(wildcard $(d)/*.o))


#====================================================================================

target_1 	:= server
target_1_o 	:= Server.$(OUTFILE)
target_2 	:= client
target_2_o 	:= Client.$(OUTFILE)

#====================================================================================

$(target_1): $(OBJECTS) $(target_1).o
	@g++ $(OBJECTS) $(target_1).o -o $(target_1_o) $(INC) $(LIB) $(LINK)
	@echo Done: $(target_1_o)
	
$(target_1).o: $(target_1).cpp
	@g++ -std=c++11 -c $(target_1).cpp $(INC) -o $(target_1).o


$(target_2): $(OBJECTS) $(target_2).o
	@g++ $(OBJECTS) $(target_2).o -o $(target_2_o) $(INC) $(LIB) $(LINK)
	@echo Done: $(target_2_o)
	
$(target_2).o: $(target_2).cpp
	@g++ -std=c++11 -c $(target_2).cpp $(INC) -o $(target_2).o
