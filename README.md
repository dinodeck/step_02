#2-LuaGameLoop

Simple GameLoop using OpenGL and SDL and a Lua settings file, that can be dynamically reloaded

I've provided some of the code in  the library folders but it's best to download a fresh one I think.



##Building on Windows

For reference I've just built with 

PhysFS 2.03
LuaJIT 2.03

Yeh the same version :o

###PhysFS

It needs CMake. Download and install it. Possible log in and out to get the env variables registered. In msys you should be able to type

	cmake

And get a help print out. If that's working, go the PhysFS dir and run

cmake -G "MSYS Makefiles" . -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CC_COMPILER=gcc

Then

	make && make install

###LuaJIT

Go to the src directory. Open the makefile and change

	# Mixed mode creates a static + dynamic library and a statically linked luajit.
	#BUILDMODE= mixed
	#
	# Static mode creates a static library and a statically linked luajit.
	BUILDMODE= static

I find if you do mixed mode, it doesn't generate the .a. 
