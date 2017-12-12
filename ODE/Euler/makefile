#!bin/sh
# files
EXEC	:= Euler
SRC	:= $(wildcard *.cpp)
OBJ	:= $(patsubst %.cpp, %.o, $(SRC))

# Options
CC		:= g++

# Rules
$(EXEC) : $(OBJ)
	$(CC) -g -pg -o $@ $^
%.o: %.cpp
	$(CC) -g -pg -c $<

main.o mytools.o: mytools.h

.PHONY: clean neat echo
clean: neat
	$(RM) $(OBJ) $(EXEC)
neat:
	$(RM) $~ .*~
