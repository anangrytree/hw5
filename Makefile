SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
CC := g++
CFLAGS := -O3
GSL := $$HOME/local/gsl-2.5
EXEC := hand

$(EXEC): hand.o
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -o $@ $^ -L$(GSL)/lib
hand.o: hand.cpp
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -c $< -L$(GSL)/lib
clean: neat
	@$(RM) $(OBJ)
	@$(RM) $(EXEC)
neat:
	@$(RM) *~ .*~
