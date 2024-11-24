CC = gcc
CFLAGS = -Wall -g

all: maze maze1 maze2 maze3

maze: maze.c
	$(CC) $(CFLAGS) -o maze maze.c

maze1.c: maze.c patch1.diff
	cp maze.c maze1.c
	patch maze1.c < patch1.diff

maze1: maze1.c
	$(CC) $(CFLAGS) -o maze1 maze1.c

maze2.c: maze.c patch2.diff
	cp maze.c maze2.c
	patch maze2.c < patch2.diff

maze2: maze2.c
	$(CC) $(CFLAGS) -o maze2 maze2.c

maze3.c: maze.c patch3.diff
	cp maze.c maze3.c
	patch maze3.c < patch3.diff

maze3: maze3.c
	$(CC) $(CFLAGS) -o maze3 maze3.c

run: all
	@echo "Running maze:"
	@./maze
	@echo "\nRunning maze1 with size 8:"
	@./maze1 8
	@echo "\nRunning maze2 with symbols '+-' and size 5:"
	@./maze2 '+-' 5
	@echo "\nRunning maze3 with seed 123, symbols ' .', and size 10:"
	@./maze3 123 ' .' 10

clean:
	rm -f maze maze1 maze2 maze3 maze1.c maze2.c maze3.c
