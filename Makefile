CC=gcc
CFLAGS=-Wall -Werror -Wextra
BUILD=

all: graph

graph: graph.o parse.o operation.o
	$(CC) graph.o parse.o operation.o -o $(BUILD)graph -lm

graph.o: src/graph.c
	$(CC) $(CFLAGS) -c src/graph.c

parse.o: src/parse.c
	$(CC) $(CFLAGS) -c src/parse.c

operation.o: src/operation.c
	$(CC) $(CFLAGS) -c src/operation.c

clean:
	rm -rf *.o $(BUILD)graph

rebuild: clean all

run:
	$(BUILD)./graph
