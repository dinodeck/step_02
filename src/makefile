#g++
# libluajit-5.1.a is in /opt/local/lib
CC=g++
CFLAGS=-c -Wall -Dmain=SDL_main
CCFLAGS+=-I../lib/LuaJIT/src -I../lib/physfs/
LDFLAGS=-lSDLmain -lSDL
SOURCES=Main.cpp DSFile_Windows.cpp LuaState.cpp Asset.cpp AssetStore.cpp DancingSquid.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=lualoop

ifeq (${PLATFORM_DS},WINDOWS)
	LDFLAGS+=-L/usr/local/lib -static-libstdc++ -lmingw32 -lopengl32 -lws2_32 -lwinmm
	LDFLAGS+=../lib/LuaJIT/src/libluajit.a ../lib/physfs/libphysfs.a
endif

ifeq (${PLATFORM_DS},MAC)
	CFLAGS+= -I/opt/local/include -I/opt/local/include/luajit-2.0
	LDFLAGS+= -L/opt/local/lib -framework OpenGL -framework Cocoa
	LDFLAGS+= -framework IOKit
	LDFLAGS+=-lz
	LDFLAGS+=/opt/local/lib/libluajit-5.1.a
	LDFLAGS+=/opt/local/lib/libphysfs.a
endif

default: mingw

mingw: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o *.exe

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@