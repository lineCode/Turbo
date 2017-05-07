# Turbo

- C++ Class Wrapper for SDL2
- 2D Component/Entity Game Engine

___

## Installation

- [SDL 2](https://www.libsdl.org/download-2.0.php)
- [IMG 2](https://www.libsdl.org/projects/SDL_image/)
- [TTF 2](https://www.libsdl.org/projects/SDL_ttf/)
- [MIX 2](https://www.libsdl.org/projects/SDL_mixer/)
- ([NET 2](https://www.libsdl.org/projects/SDL_net/)) * optionally, not yet implemented

Download the development files for your platform and your Environment. You may want to download the binary files as well.
- **If you have trouble with 64 bit files may have to use the 32 bit libraries in order to compile for 64 bit systems.**

Extract the include and lib directory you have to use to your libraries path (example: `C:/libraries/SDL/include/`).
- **Remember this path, you will need this later to configure the make file.**

___

### Generating Executables

**Visual Studio:**

-

**GNU make:**

1. Change parameters at the section `# Define Variables` in the file Turbo/Turbo.make to fit your system requirements:

	1.1 `INCD`: include directory of SDL2 and Python
	
		(example `INCD := -IC:/libraries/SDL/include/ -IC:/libraries/Python/include/`)
	
	1.2 `LIBD`: library directory of SDL2 and Python
	
		(example: `LIBD := -IC:/libraries/SDL/lib/ -IC:/libraries/Python/libs/`)
	
	1.3 `PROJECT`: desired output file name

		(example: `PROJECT := Turbo`)	

	1.4 `CFLAGS` and `CPPFLAGS`: compiler flags
	
		(example: `CFLAGS := -c -Wall -Werror` and `CPPFLAGS := -std=c++11`)
	
	1.5 `LDFLAGS`: linker flags

		(example: `LDFLAGS := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpython34`)

If you have done all the above things you can now build Turbo with the following command.
(This requires, that you have added the make executable to your Environment path)
	
		`make Turbo.make`

This command should generate object files into the directory obj and a executable in the base directory of the project.

___

For more information and help take a look at either 'Visual Studio Support' or 'GNU make'.
