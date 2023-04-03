CC=gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LFLAGS = -lm
NAME = main

SRC = main.c createUndirectedGraph.c charactGraph.c
DEPS = createUndirectedGraph.h charactGraph.h

OBJS = main.o createUndirectedGraph.o charactGraph.o

YOU : $(SRC) $(NAME)
$(NAME): $(OBJS)
	$(CC) -g $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS) nauty27r1/nauty.a
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f $(OBJS) $(NAME)
