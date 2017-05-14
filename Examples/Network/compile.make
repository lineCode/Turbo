LIB 		:= -LC:/Libs/SDL/lib -LC:/Libs/Python/libs
INC 		:= -I../../Turbo/include -IC:/Libs/SDL/include -IC:/Libs/Python/include
LINK		:= -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lpython34

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