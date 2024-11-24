#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_WIDTH 6
#define MAZE_HEIGHT 6
#define GRID_WIDTH (MAZE_WIDTH * 2 + 1)
#define GRID_HEIGHT (MAZE_HEIGHT * 2 + 1)

char grid[GRID_HEIGHT][GRID_WIDTH];
int visited[MAZE_HEIGHT][MAZE_WIDTH];

int dx[] = { 0, 0, 1, -1 };
int dy[] = { -1, 1, 0, 0 };

void init_grid() {
    int x, y;

    for (y = 0; y < GRID_HEIGHT; y++) {
        for (x = 0; x < GRID_WIDTH; x++) {
            grid[y][x] = '#';
        }
    }

    for (y = 0; y < MAZE_HEIGHT; y++) {
        for (x = 0; x < MAZE_WIDTH; x++) {
            grid[y * 2 + 1][x * 2 + 1] = '.';
            visited[y][x] = 0;
        }
    }
}

void shuffle_directions(int *dirs) {
    for (int i = 0; i < 4; i++) {
        int r = rand() % 4;
        int temp = dirs[i];
        dirs[i] = dirs[r];
        dirs[r] = temp;
    }
}

void generate_maze(int x, int y) {
    visited[y][x] = 1;

    int dirs[] = { 0, 1, 2, 3 };
    shuffle_directions(dirs);

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[dirs[i]];
        int ny = y + dy[dirs[i]];

        if (nx >= 0 && nx < MAZE_WIDTH && ny >= 0 && ny < MAZE_HEIGHT && !visited[ny][nx]) {
            grid[y * 2 + 1 + dy[dirs[i]]][x * 2 + 1 + dx[dirs[i]]] = '.';
            generate_maze(nx, ny);
        }
    }
}

void print_grid() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    init_grid();
    generate_maze(0, 0);
    print_grid();

    return 0;
}
