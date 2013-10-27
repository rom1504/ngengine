# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Compilation Flags
CFLAGS=-I ../../../include/ -I ../../../externals/glm -lGL -lGLU -lGLEW -Wall -m64 -std=gnu++0x

# Sources
SRC=$(call rwildcard, ../../../src/, *.cpp) $(call rwildcard, ../../../externals/glm/glm, *.cpp)

OBJ=$(SRC:.cpp=.o)
DEST=../../../bin/ngengine.a

all: $(DEST)

$(DEST): $(OBJ)
	mkdir -p ../../../bin
	ar -rv $@ $(OBJ)

%.o: %.cpp
	gcc -o $@ -c $< $(CFLAGS)

