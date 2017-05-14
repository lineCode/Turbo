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

#=======================================================================================
# Define Macros
#=======================================================================================

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

#=======================================================================================
# Define Variables
#=======================================================================================

CC              := g++
CFLAGS 		:= -c -Wall -Werror
CPPFLAGS 	:= -std=gnu++11 -std=c++11
LDFLAGS 	 = $(OS_LIB) -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

INCLUDEDIR	:= include
SOURCEDIR	:= source
OBJECTDIR	:= obj
ifeq ($(SYSTEM), WINDOWS)
	LIBD 		:= -LC:/Libs/SDL/lib -LC:/Libs/Python/libs
	INCD 		:= -I./include -IC:/Libs/SDL/include -IC:/Libs/Python/include
	LDFLAGS += -lpython34
else
	LIBD		:= -L/usr/lib
	INCD		:= -I./include -I/usr/include/SDL2 -I/usr/include/python3.5
	LDFLAGS += -lpython3.5m
endif

DEB 		:= Debug
REL 		:= Release
PROJECT		:= Turbo
TARGET 		:= $(DEB)

#=======================================================================================
# File and Path Variables
#=======================================================================================

MDLS 		:= $(patsubst %/,%,$(patsubst $(SOURCEDIR)/%,%,$(dir $(wildcard $(SOURCEDIR)/*/))))
SRCD 		:= $(foreach d, $(MDLS), $(addprefix $(SOURCEDIR)/, $(d))) $(SOURCEDIR)
HEAD 		:= $(foreach d, $(MDLS), $(addprefix $(INCLUDEDIR)/, $(d))) $(INCLUDEDIR)
OBJD 		:= $(addprefix $(OBJECTDIR)/$(TARGET)/, $(MDLS))

SOURCES		:= $(foreach d, $(SRCD), $(wildcard $(d)/*.cpp))
HEADERS		:= $(foreach d, $(HEAD), $(wildcard $(d)/*.h))
OBJECTS		:= $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJECTDIR)/$(TARGET)/%.o)
DEPENDS		:= $(OBJECTS:%.o=%.d)
OUT 		:= $(PROJECT)_$(TARGET).$(OUTFILE)

#=======================================================================================
# Build
#=======================================================================================

Release: all

Debug: all

all: $(OUT)

#Link
$(OUT): $(OBJECTS)
	@echo +=====================
	@echo [ Create taget file: ] $(OUT) for $(SYSTEM) on $(ARCHITECTURE)
	@echo ======================
	@$(CC) $(CPPFLAGS) $(CCFLAGS) $(OBJECTS) -o $(OUT) $(INCD) $(LIBD) $(LDFLAGS)
	@echo =======================
	@echo [ Successfully build: ] $(PROJECT)
	@echo =======================

#Compile
#-include $(DEPENDS)
#$(OBJECTDIR)/$(TARGET)/%.o: $(SOURCEDIR)/%.cpp $(INCLUDEDIR)/%.h
$(OBJECTDIR)/$(TARGET)/%.o: $(SOURCEDIR)/%.cpp
	@echo +======================
	@echo [ Create object file: ] $@
	@echo =======================
	@$(CC) $(CPPFLAGS) $(CFLAGS) $< $(INCD) -o $@


#Directories
dirs:
	@echo +========================
	@echo [ Creating directories: ]
	@echo =========================
	@$(MKDIR) $(OBJD)

#Clean
clean:
	@echo -==========================
	@echo [ Cleaning object folder: ]
	@echo ===========================
	@$(RM) $(DEPENDS) $(OBJECTS) $(OUT) 2>nul
	@$(RMDIR) $(OBJD)
