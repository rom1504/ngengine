# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Compilation Flags
CFLAGS=-I ../../../../include/ -Wall -m64 -std=gnu++0x ../../../../bin/ngengine.a -lSDL -lGL -lGLU -lGLEW -I ../../../../bridges/SDL1.2/ -lSDL_image -I ../../../../externals/glm

NAME=03_Texture

# Sources
SRC=$(call rwildcard, ../../../../examples/$(NAME), *.cpp) ../../../../bridges/SDL1.2/NGE_SDL.cpp

OBJ=$(SRC:.cpp=.o)
DEST=../../../../bin/examples/$(NAME)/example

all: $(DEST)

$(DEST): $(OBJ)
	mkdir -p ../../../../bin/examples/$(NAME)
	g++ -o $@ $(OBJ) $(CFLAGS)
	cp -R ../../../../resources/$(NAME)/* ../../../../bin/examples/$(NAME)/

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

