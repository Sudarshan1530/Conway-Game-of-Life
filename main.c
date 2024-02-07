#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 25
#define WIDTH 25

#define BACKGROUND '-'
#define CELL '*'

#define SPEED 50 // Speed of getting new grid (milliseconds)

typedef enum State {
    DEAD,
    ALIVE,
} State;
// We use an enum with value of ALIVE as 1 so that counting number of live neighbours and setting cell states become easier

typedef struct Cell {
    State state;
} Cell;
// Cell.state associates a state with each cell which makes it easy to handle

Cell** createGrid(int rows, int cols) {
    Cell** grid = (Cell**)malloc(rows * sizeof(Cell*));

    for (size_t i = 0; i < cols; i++) {
        grid[i] = (Cell*)malloc(cols * sizeof(Cell));
    }

    return grid;
}

void initGrid(Cell** grid, int rows, int cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            grid[i][j].state = DEAD;
        }
    }

    return;
}
// initGrid returns a grid with all cells having default state dead (Basically a grid of all 0s)

int printGrid(Cell** grid, int rows, int cols) {
    int aliveCount = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (grid[i][j].state == ALIVE) {
                aliveCount++;
                printf("%c", CELL);
            }
            else {
                printf("%c", BACKGROUND);
            }
        }
        printf("\n");
    }

    return aliveCount;
}
// printGrid looks at 0s and 1s of the grid and prints the corresponding symbol representing it
// It returns the number of live cells

void nextGeneration(Cell** grid, int rows, int cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            int aliveCount = 0;
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a == 0 && b == 0) { // Current cell is not a neighbour
                        continue;
                    }
                    if ((i + a >= 0 && i + a < rows) && (j + b >= 0 && j + b < rows)) {
                        if (grid[i + a][j + b].state == ALIVE) {
                            aliveCount++;
                        }
                    }
                }
            }
            switch (aliveCount) {
                case 0:
                case 1:
                    grid[i][j].state = DEAD;
                    break;
                case 2:
                    break; // Dead stays dead, alive stays alive
                case 3:
                    grid[i][j].state = ALIVE;
                    break;
                default:
                    grid[i][j].state = DEAD;
                    break;
            }
        }
    }
}
// Updates the grid

void sampleGrid(Cell** grid, int rows, int cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            grid[i][j].state = ALIVE;
        }
    }
} // Modify the grid for samples

int main(void) {
    Cell** grid = createGrid(HEIGHT, WIDTH);

    initGrid(grid, HEIGHT, WIDTH);

    sampleGrid(grid, HEIGHT / 5, WIDTH / 5);

    while (printGrid(grid, HEIGHT, WIDTH) != 0) {
        usleep(SPEED * 1000); // In microseconds
        nextGeneration(grid, HEIGHT, WIDTH);
        system("clear");
    }

    printGrid(grid, HEIGHT, WIDTH);
}