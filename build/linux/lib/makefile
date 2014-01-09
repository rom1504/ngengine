# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Compilation Flags
CFLAGS=-I ../../../include/ -I ../../../externals/glm -I ../../../externals/freetype-gl/ -lGL -lGLU -lGLEW -Wall -m64 -std=gnu++0x

# Sources
SRC_FREETYPE_GL=edtaa3func.c font-manager.c mat4.c platform.c shader.c text-buffer.c texture-atlas.c texture-font.c vector.c vertex-attribute.c vertex-buffer.c
SRC_FREETYPE_GL2=$(addprefix ../../../externals/freetype-gl/, $(SRC_FREETYPE_GL))
SRC=$(call rwildcard, ../../../src/, *.cpp) $(call rwildcard, ../../../externals/glm/glm, *.cpp)

OBJ=$(SRC:.cpp=.o) $(SRC_FREETYPE_GL2:.c=.o)
DEST=../../../bin/ngengine.a

all: $(DEST)

$(DEST): $(OBJ)
	mkdir -p ../../../bin
	ar -rv $@ $(OBJ)

%.o: %.cpp
	gcc -o $@ -c $< $(CFLAGS)

%.o: %.c
	gcc -o $@ -c $< $(CFLAGS)

