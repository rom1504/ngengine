# Recursive Wildcard Function
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

# Sources
OBJ=$(call rwildcard, ../../src/, *.o) \
$(call rwildcard, ../../examples/, *.o) \
$(call rwildcard, ../../tests/, *.o)

DEP=$(call rwildcard, ../../src/, *.d) \
$(call rwildcard, ../../examples/, *.d) \
$(call rwildcard, ../../tests/, *.d)


all: lib examples

.PHONY: lib examples tests clean mrproper

clean: 
	rm -f $(OBJ)
	rm -f $(DEP)
  
mrproper: clean
	rm -rf ../../bin

lib:
	cd lib && $(MAKE)

examples:
	cd examples && $(MAKE)

tests:
	cd tests && $(MAKE)

