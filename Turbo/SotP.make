MKDIR = mkdir

CC := g++
CFLAGS := -c -Wall -Werror
CPPFLAGS := -std=gnu++11 -std=c++11
LDFLAGS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

MDLS := turbo gui event logic audio extern
DEB := Debug
REL := Release
TAR := $(DEB)
SRCD := $(addprefix source/, $(MDLS)) source
DEPD := $(addprefix include/, $(MDLS)) include
OBJD := $(addprefix obj/$(TAR)/source/, $(MDLS))
INCD := ./include
LIBD := ./lib

MKOBJD := $(subst /,\,$(OBJD))

TARGET := $(DEBD)
OUT := out.exe
SRC := $(foreach sdir, $(SRCD), $(wildcard $(sdir)/*.cpp))
DEP := $(foreach ddir, $(DEPD), $(wildcard $(ddir)/*.h))
OBJ := $(SRC:%.cpp=obj/$(TAR)/%.o)

MKOBJ := $(subst /,\,$(OBJ))

Debug: all

all: $(OUT)

#Link
$(OUT): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(OUT) -L $(LIBD) $(LDFLAGS)

#Compile
obj/Debug/source/%.o: source/%.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -I $(INCD) -o $@

#Directories
dirs:
	@mkdir $(MKOBJD)

#Clean
clean:
	-del $(MKOBJ) $(OUT)
	-rmdir $(MKOBJD)


#-c $(SRC) -I ./include -L ./lib