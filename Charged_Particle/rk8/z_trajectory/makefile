#!bin/sh
# files

EXEC    := z_trajectory
SRC     := $(wildcard *.cpp)
OBJ     := $(patsubst %.cpp, %.o, $(SRC))

# Options
CC              := g++
GSL_INCLUDE     := -I $$TACC_GSL_INC -I $$TACC_GSL_INC/gsl
LDFLAGS         := -L $$TACC_GSL_LIB
LDLIBS          := -lgsl -lgslcblas -limf

# Rules
$(EXEC) : $(OBJ)
	$(CC) $(LDFLAGS) $(LDLIBS) -g -pg -o $@ $^
%.o: %.cpp
	$(CC) $(GSL_INCLUDE) -g -pg -c $<

main.o mytools.o: mytools.h

.PHONY: clean neat echo
clean: neat
	$(RM) $(OBJ) $(EXEC)
neat:
	$(RM) $~ .*~
