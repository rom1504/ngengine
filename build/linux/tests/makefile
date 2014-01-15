# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

#Paths
NGENGINE=../../../bin/ngengine.a

# Compilation Flags
CFLAGS=-I ../../../include/ -Wall -m64 -std=gnu++11 $(NGENGINE) -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image -I ../../../externals/glm -I ../../../externals/freetype-gl -I ../../../bridges/ `freetype-config --cflags` `freetype-config --libs` -I ../../../tests -lpthread

# Sources
SRC=$(call rwildcard, ../../../tests/, *.cpp)# ../../../bridges/SDL2/NGE_SDL.cpp

OBJ=$(SRC:.cpp=.o)
DEST=../../../bin/tests

$(DEST): $(OBJ) $(NGENGINE)
	mkdir -p ../../../bin/
	g++ -o $@ $(OBJ) $(CFLAGS)

%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

$(NGENGINE): 

