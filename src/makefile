#g++
CC=g++
CFLAGS=-c -Wall -Dmain=SDL_main
CFLAGS+=-I../lib/LuaJIT/src -I../lib/physfs/
LDFLAGS=-lSDLmain -lSDL
SOURCES=Main.cpp DSFile_Windows.cpp LuaState.cpp Asset.cpp AssetStore.cpp DancingSquid.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dinodeck

ifeq (${PLATFORM_DS},WINDOWS)
	CFLAGS+= -I/usr/include
	CFLAGS+= `sdl-config --cflags`
	LDFLAGS+= `sdl-config --libs`
	LDFLAGS+=-L/usr/lib -static-libstdc++ -lmingw32 -lopengl32 -lws2_32 -lwinmm
	LDFLAGS+=../lib/LuaJIT/src/libluajit.a ../lib/physfs/libphysfs.a
endif

ifeq (${PLATFORM_DS},MAC)
	SDLLIBS= -Bstatic `sdl-config --static-libs`
	CFLAGS+= -I/opt/local/include -I/opt/local/include/luajit-2.0
	LDFLAGS+= -framework IOKit
	LDFLAGS+=-lz -pagezero_size 10000 -image_base 100000000
	LDFLAGS+= $(SDLLIBS)
	LDFLAGS+= -L/opt/local/lib -framework OpenGL -framework Cocoa
	LDFLAGS+=/opt/local/lib/libluajit-5.1.a
	LDFLAGS+=/opt/local/lib/libphysfs.a
endif

default: mingw

mingw: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE) 2> /dev/null || true

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $? $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@