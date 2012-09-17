#g++
CC=g++
CFLAGS=-c -Wall -Dmain=SDL_main -I../lib/LuaJIT/src -I../lib/physfs/
LDFLAGS=-L/usr/local/lib -static-libgcc -static-libstdc++ -lmingw32 -lSDLmain -lSDL -lopengl32 -lws2_32 -lwinmm ../lib/LuaJIT/src/libluajit.a ../lib/physfs/libphysfs.a
SOURCES=Main.cpp DSFile_Windows.cpp LuaState.cpp Asset.cpp AssetStore.cpp DancingSquid.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lualoop

default: mingw

mingw: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o *.exe

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@