#===========================================

# creates a new directory
f_mkdir		 = mkdir
# searches for all folders in the first argument
f_subdirs	 = $(1) $(foreach sub_dir, $(wildcard $(1)/*), $(call f_subdirs, $(sub_dir)))
# searches for all files in subfolders with the ending in the first argument
f_subfiles	 = $(1) $(2) $(foreach sub_dir, $(wildcard $(1)/*$(2)), $(call f_subfiles, $(sub_dir), $(2)))
#============================================

INCLUDEDIR	:= include
SOURCEDIR	:= source
OBJECTDIR	:= obj

CC 			:= g++
CFLAGS 		:= -c -Wall -Werror
CPPFLAGS 	:= -std=gnu++11 -std=c++11
LDFLAGS 	:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

MDLS 		:= audio event extern gui logic net system turbo utils
DEB 		:= Debug
REL 		:= Release
TAR 		:= $(DEB)
SRCD 		:= $(foreach d, $(MDLS), $(addprefix $(SOURCEDIR)/, $(d))) $(SOURCEDIR)
DEPD 		:= $(foreach d, $(MDLS), $(addprefix $(INCLUDEDIR)/ ,$(d))) $(INCLUDEDIR)
OBJD 		:= $(addprefix $(OBJECTDIR)/$(TAR)/$(SOURCEDIR)/, $(MDLS))
INCD 		:= -I./include -IC:/Libs/SDL/include
LIBD 		:= -L./lib -LC:/Libs/SDL2/lib

MKOBJD 		:= $(subst /,\,$(OBJD))

TARGET 		:= $(DEBD)
OUT 		:= Turbo.exe
SRC 		:= $(foreach sdir, $(SRCD), $(wildcard $(sdir)/*.cpp))
DEP 		:= $(foreach ddir, $(DEPD), $(wildcard $(ddir)/*.h))
OBJ 		:= $(SRC:%.cpp=obj/$(TAR)/%.o)

MKOBJ 		:= $(subst /,\,$(OBJ))

test := $(call f_subdirs,$(SOURCEDIR))
tester :=  $(foreach sdir, $(test), $(wildcard $(sdir)/*.cpp))
testf := $(call f_subfiles, $(SOURCEDIR))

Debug: all

all: $(OUT)

#Link
$(OUT): $(OBJ)
	@echo Create target: $(OUT)
	@echo ==============
	$(CC) $(CPPFLAGS) $(OBJ) -o $(OUT) $(LIBD) $(LDFLAGS)

#Compile
obj/Debug/source/%.o: source/%.cpp
	@echo Create OBJ File: $?
	@echo ================
	$(CC) $(CPPFLAGS) $(CFLAGS) $? $(INCD) -o $@

#Directories
dirs:
	@echo Create DIR:
	@echo ===========
	@mkdir $(MKOBJD)

#Clean
clean:
	@echo Delete DIR:
	@echo ===========
	-del $(MKOBJ) $(OUT)
	-rmdir $(MKOBJD)


#-c $(SRC) -I ./include -L ./lib