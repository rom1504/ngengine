ifndef EXAMPLE
none:
	echo "You need to precise the EXAMPLE variable."
	@exit 1;
endif

# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

#Paths
NGENGINE=../../../../bin/ngengine.a

# Compilation Flags
CFLAGS=-I ../../../../include/ -Wall -m64 -std=gnu++11 $(NGENGINE) -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image -I ../../../../externals/glm -I ../../../../externals/freetype-gl -I ../../../../bridges/ `freetype-config --cflags` `freetype-config --libs` -I ../../../../examples

# Sources
SRC=$(call rwildcard, ../../../../examples/$(EXAMPLE), *.cpp) ../../../../bridges/SDL2/NGE_SDL.cpp

OBJ=$(SRC:.cpp=.o)
DEST=../../../../bin/examples/$(EXAMPLE)/example

$(DEST): $(OBJ) $(NGENGINE)
	mkdir -p ../../../../bin/examples/$(EXAMPLE)
	g++ -o $@ $(OBJ) $(CFLAGS)
	cp -R ../../../../resources/Shaders ../../../../bin/examples/$(EXAMPLE)/
ifdef RESOURCES
	cp -R ../../../../resources/$(EXAMPLE)/* ../../../../bin/examples/$(EXAMPLE)/
endif

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

$(NGENGINE): 

