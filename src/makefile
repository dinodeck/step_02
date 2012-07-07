#g++
CC=g++
CFLAGS=-c -Wall -Dmain=SDL_main -I../lib/LuaJIT/src
LDFLAGS=-L/usr/local/lib -static-libgcc -static-libstdc++ -lmingw32 -lSDLmain -lSDL -lopengl32 -lws2_32 -lwinmm ../lib/LuaJIT/src/libluajit.a
SOURCES=main.cpp LuaState.cpp Resource.cpp ResourceStore.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lualoop

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@