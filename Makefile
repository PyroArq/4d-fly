# get the mod name from main.cpp
MOD_NAME := $(shell grep -Po '(?<=#define MOD_NAME ")[^"]*' main.cpp)

# configure mingw as the compiler
CC=x86_64-w64-mingw32-g++

# 4dm.h will spam your compiler output otherwise
HIDE_SOME_WARNINGS=-Wno-return-type -Wno-conversion-null
CFLAGS=-std=c++20 -mwindows $(HIDE_SOME_WARNINGS) -s


INCLUDE=-I 4dm.h/ -I 4dm.h/networking/include/

# ./4dm.h/networking/lib/*;./4dm.h/soil/SOIL.lib;opengl32.lib;glew32.lib;glfw3.lib
NETLIBS=$(shell find 4dm.h/networking/lib/*.lib -not -name steamwebrtc.lib -not -name webrtc-lite.lib)
CLIBS=-L. $(patsubst %.lib,-l %,$(NETLIBS)) -L 4dm.h/soil -l SOIL -L. -l opengl32   -Wl,-Bdynamic  -l glew32 -l glfw3  -Wl,-Bstatic
# CLIBS=-L. $(patsubst %.lib,-l %,$(wildcard 4dm.h/networking/lib/*.lib)) -L 4dm.h/soil -l SOIL -L. -l opengl32   -Wl,-Bdynamic  -l glew32 -l glfw3  -Wl,-Bstatic


default: compile
compile:
	$(CC) $(CFLAGS) -O3 -flto $(INCLUDE)   main.cpp   -shared -static $(CLIBS)   -o "$(MOD_NAME).dll"

install:
	cd ~/.steamapps/4D\ Miner/4D\ Miner\ 0.2.1.4/mods/ && mkdir -p "$(MOD_NAME)"
	cp "$(MOD_NAME).dll" ~/.steamapps/4D\ Miner/4D\ Miner\ 0.2.1.4/mods/"$(MOD_NAME)"/

clean:
	rm "$(MOD_NAME).dll"
