#======================================================================================
# Check OS
#======================================================================================

ifeq ($(OS),Windows_NT)
    CCFLAGS 				+= -D WIN32
    OS 						:= WINDOWS
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
    	ARCHITECTURE 		:= AMD64
        CCFLAGS 			+= -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        	ARCHITECTURE 	:= AMD64
            CCFLAGS 		+= -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        	ARCHITECTURE 	:= IA32
            CCFLAGS 		+= -D IA32
        endif
    endif
else
	OS := UNDEFINED
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    	OS 					:= LINUX
        CCFLAGS 			+= -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
    	OS 					:= OSX
        CCFLAGS 			+= -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
    	ARCHITECTURE 		:= AMD64
        CCFLAGS 			+= -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
    	ARCHITECTURE 		:= IA32
        CCFLAGS 			+= -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
    	ARCHITECTURE 		:= ARM
        CCFLAGS 			+= -D ARM
    endif
endif

#=======================================================================================
# Define Variables
#=======================================================================================

#ifeq ($(OS),WINDOWS)
#	DEL := del
#else
#	DEL := rm
#endif

#=======================================================================================
# Define Variables
#=======================================================================================

CC 			:= g++
CFLAGS 		:= -c -Wall -Werror
CPPFLAGS 	:= -std=gnu++11 -std=c++11
LDFLAGS 	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

INCLUDEDIR	:= include
SOURCEDIR	:= source
OBJECTDIR	:= obj
LIBD 		:= -L./lib -LC:/Libs/SDL2/lib
INCD 		:= -I./include -IC:/Libs/SDL/include

DEB 		:= Debug
REL 		:= Release
TARGET 		:= $(DEB)

SOURCES		:= $(subst ./,,$(subst ",,$(subst \,/,$(shell forfiles /s /m *.cpp /c "cmd /c echo @relpath"))))
HEADERS		:= $(subst ./,,$(subst ",,$(subst \,/,$(shell forfiles /s /m *.h /c "cmd /c echo @relpath"))))
OBJECTS		:= $(SOURCES:%.cpp=$(OBJECTDIR)/$(TARGET)/%.o)
OUT 		:= Turbo_$(TARGET).exe

MDLS 		:= audio event extern gui logic net system turbo utils geometry
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
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(OUT) $(INCD) $(LIBD) $(LDFLAGS)

#Compile


#$(OBJECTDIR)/$(TARGET)/$(SOURCEDIR)/%.o: $(SOURCEDIR)/%.cpp $(INCLUDEDIR)/%.h
$(OBJECTDIR)/$(TARGET)/$(SOURCEDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo +======================
	@echo [ Create object file: ] $<
	@echo =======================
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(INCD) -o $@

#Directories
dirs:
	@mkdir $(MKOBJD)

#Clean
clean:
	-del $(MKOBJ) $(OUT)
	-rmdir $(MKOBJD)

##INCLUDEDIR	:= include
##SOURCEDIR	:= source
##OBJECTDIR	:= obj
##
##CC 			:= g++
##CFLAGS 		:= -c -Wall -Werror
##CPPFLAGS 	:= -std=gnu++11 -std=c++11
##LDFLAGS 	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net
##
##MDLS 		:= audio event extern gui logic net system turbo utils
##DEB 		:= Debug
##REL 		:= Release
##TAR 		:= $(DEB)
##SRCD 		:= $(addprefix source/, $(MDLS)) source
##DEPD 		:= $(addprefix include/, $(MDLS)) include
##OBJD 		:= $(addprefix obj/$(TAR)/source/, $(MDLS))
##INCD 		:= -I./include -IC:/Libs/SDL/include
##LIBD 		:= -L./lib -LC:/Libs/SDL2/lib
##
##MKOBJD 		:= $(subst /,\,$(OBJD))
##
##TARGET 		:= $(DEBD)
##OUT 		:= Turbo.exe
##SRC 		:= $(foreach sdir, $(SRCD), $(wildcard $(sdir)/*.cpp))
##DEP 		:= $(foreach ddir, $(DEPD), $(wildcard $(ddir)/*.h))
##OBJ 		:= $(SRC:%.cpp=obj/$(TAR)/%.o)
##
##MKOBJ 		:= $(subst /,\,$(OBJ))
##
##Debug: all
##
##all: $(OUT)
##
###Link
##$(OUT): $(OBJ)
##	@echo +=============
##	@echo Create target: $(OUT)
##	@echo ==============
##	$(CC) $(CPPFLAGS) $(OBJ) -o $(OUT) $(INCD) $(LIBD) $(LDFLAGS)
##
###Compile
##obj/Debug/source/%.o: source/%.cpp
##	@echo $(SRC)
##	@echo +===============
##	@echo Create OBJ File: $?
##	@echo ================
##	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(INCD) -o $@
##
###Directories
##dirs:
##	@echo Create DIR:
##	@echo ===========
##	@mkdir $(MKOBJD)
##
###Clean
##clean:
##	@echo Delete DIR:
##	@echo ===========
##	-del $(MKOBJ) $(OUT)
##	-rmdir $(MKOBJD)