SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
CC := g++
CFLAGS := -O3
GSL := $$HOME/local/gsl-2.5
EXEC := hand

dealer: dealer.o hand
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -o $@ $< -L$(GSL)/lib
dealer.o: dealer.cpp
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -c $< -L$(GSL)/lib
hand: hand.o
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -o $@ $^ -L$(GSL)/lib
hand.o: hand.cpp
	@$(CC) -I$(GSL)/include $(CFLAGS) -lgsl -lgslcblas -c $< -L$(GSL)/lib
clean: neat
	@$(RM) dealer
	@$(RM) hand
	@$(RM) hand.o
	@$(RM) dealer.o
neat:
	@$(RM) *~ .*~
