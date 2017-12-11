#bin/sh
# files

EXEC    := xy_trajectory
SRC     := $(wildcard *.cpp)
OBJ     := $(patsubst %.cpp, %.o, $(SRC))

# Options
CC              := g++
GSL_INCLUDE     := -I $$TACC_GSL_INC -I $$TACC_GSL_INC/gsl
LDFLAGS         := -L $$TACC_GSL_LIB
LDLIBS          := -lgsl -lgslcblas -limf

# Rules
$(EXEC) : $(OBJ)
	 $(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
%.o: %.cpp
	 $(CC) $(GSL_INCLUDE) -c $<

main.o mytools.o: mytools.h

.PHONY: clean neat echo
clean: neat
	 $(RM) $(OBJ) $(EXEC)
neat:
	 $(RM) $~ .*~

