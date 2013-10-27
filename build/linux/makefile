# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Sources
OBJ=$(call rwildcard, ../../src/, *.o) $(call rwildcard, ../../examples/, *.o)


all: lib examples

.PHONY: lib examples clean mrproper

clean: 
	rm $(OBJ)
  
mrproper: clean
	rm -rf ../../bin

lib:
	cd lib && $(MAKE)

examples:
	cd examples && $(MAKE)

