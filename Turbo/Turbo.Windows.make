#======================================================================================
# Check OS
#======================================================================================

ifeq ($(OS),Windows_NT)
    CCFLAGS 				= -D WIN32
    OS_NAME 				:= WINDOWS
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
    	ARCHITECTURE 		:= AMD64
        CCFLAGS 			= -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        	ARCHITECTURE 	:= AMD64
            CCFLAGS 		= -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        	ARCHITECTURE 	:= IA32
            CCFLAGS 		= -D IA32
        endif
    endif
else
	OS_NAME := UNDEFINED
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    	OS_NAME				:= LINUX
        CCFLAGS 			= -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
    	OS_NAME				:= OSX
        CCFLAGS 			= -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
    	ARCHITECTURE 		:= AMD64
        CCFLAGS 			= -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
    	ARCHITECTURE 		:= IA32
        CCFLAGS 			= -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
    	ARCHITECTURE 		:= ARM
        CCFLAGS 			= -D ARM
    endif
endif

#=======================================================================================
# Define Macros
#=======================================================================================

ifeq ($(OS_NAME),WINDOWS)
	RM 		:= del
	RMDIR	:= rmdir
	MKDIR	:= mkdir
else
	RM 		:= rm
	RMDIR	:= rmdir
	MKDIR	:= mkdir
endif

#=======================================================================================
# Define Variables
#=======================================================================================

CC 			:= g++
CFLAGS 		:= -c -Wall -Werror
CPPFLAGS 	:= -std=gnu++11 -std=c++11
LDFLAGS 	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lpython34

INCLUDEDIR	:= include
SOURCEDIR	:= source
OBJECTDIR	:= obj
LIBD 		:= -L./lib
INCD 		:= -I./include

DEB 		:= Debug
REL 		:= Release
PROJECT		:= Turbo
TARGET 		:= $(DEB)

SOURCES		:= $(subst ./,,$(subst ",,$(subst \,/,$(shell forfiles /s /m *.cpp /c "cmd /c echo @relpath"))))
HEADERS		:= $(subst ./,,$(subst ",,$(subst \,/,$(shell forfiles /s /m *.h /c "cmd /c echo @relpath"))))
OBJECTS		:= $(SOURCES:%.cpp=$(OBJECTDIR)/$(TARGET)/%.o)
OUT 		:= $(PROJECT)_$(TARGET).exe

MDLS 		:= audio event extern gui logic net script system turbo utils geometry
SRCD 		:= $(foreach d, $(MDLS), $(addprefix $(SOURCEDIR)/, $(d))) $(SOURCEDIR)
DEPD 		:= $(foreach d, $(MDLS), $(addprefix $(INCLUDEDIR)/ ,$(d))) $(INCLUDEDIR)
OBJD 		:= $(addprefix $(OBJECTDIR)/$(TARGET)/$(SOURCEDIR)/, $(MDLS))
MKOBJ 		:= $(subst /,\,$(OBJECTS))
MKOBJD 		:= $(subst /,\,$(OBJD))

#=======================================================================================
# Build
#=======================================================================================

Debug: all

all: $(OUT)

#Link
$(OUT): $(OBJECTS)
	@echo +=====================
	@echo [ Create taget file: ] $(OUT)
	@echo ======================
	$(CC) $(CPPFLAGS) $(CCFLAGS) $(OBJECTS) -o $(OUT) $(INCD) $(LIBD) $(LDFLAGS)
	@echo =======================
	@echo [ Successfully build: ] $(PROJECT)
	@echo =======================

#Compile

#$(OBJECTDIR)/$(TARGET)/$(SOURCEDIR)/%.o: $(SOURCEDIR)/%.cpp $(INCLUDEDIR)/%.h
$(OBJECTDIR)/$(TARGET)/$(SOURCEDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo +======================
	@echo [ Create object file: ] $@
	@echo =======================
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(INCD) -o $@

#Directories
dirs:
	@echo +========================
	@echo [ Creating directories: ]
	@echo =========================
	mkdir $(MKOBJD)

#Clean
clean:
	@echo -=========================
	@echo [ Cleaning object files: ]
	@echo ==========================
	-$RM $(MKOBJ) $(OUT)
	-$RMDIR $(MKOBJD)