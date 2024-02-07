#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memcpy
#include <time.h> // for rand()
#include <unistd.h> // for usleep()


#define HEIGHT 50
#define WIDTH 100

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
            if (rand() % 2 == 0 && rand() % 5 == 0) {
                grid[i][j].state = ALIVE;
                continue;
            }
            grid[i][j].state = DEAD;
        }
    }

    return;
}
// initGrid returns a grid all cells having randomized values using the rand() function

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
    Cell** newGrid = createGrid(rows, cols);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            int aliveCount = 0;
            for (int a = -1; a < 2; a++) {
                for (int b = -1; b < 2; b++) {
                    if (a == 0 && b == 0) { // Current cell is not a neighbour
                        continue;
                    }
                    // Implement wraparound
                    int row = (i + a + rows) % rows;
                    int col = (j + b + cols) % cols;

                    if (grid[row][col].state == ALIVE) {
                        aliveCount++;
                    }
                }
            }
            switch (aliveCount) {
                case 0:
                case 1:
                    newGrid[i][j].state = DEAD;
                    break;
                case 2:
                    newGrid[i][j] = grid[i][j];
                    break; // Dead stays dead, alive stays alive
                case 3:
                    newGrid[i][j].state = ALIVE;
                    break;
                default:
                    newGrid[i][j].state = DEAD;
                    break;
            }
        }
    }
    memcpy(grid, newGrid, (rows * cols * sizeof(Cell)));
    
}
// Updates the grid

void initGlider(Cell** grid, int rows, int cols, int offset) {
    grid[offset + 0][offset + 1].state = ALIVE;
    grid[offset + 1][offset + 2].state = ALIVE;
    grid[offset + 2][offset + 0].state = ALIVE;
    grid[offset + 2][offset + 1].state = ALIVE;
    grid[offset + 2][offset + 2].state = ALIVE;
}

int main(int argc, char* argv[]) {
    char* program = argv[0];

    srand(time(NULL)); // Seed the rand() function
    system("clear");

    Cell** grid = createGrid(HEIGHT, WIDTH);

    if (argc < 2) {
        initGrid(grid, HEIGHT, WIDTH);

        while (printGrid(grid, HEIGHT, WIDTH) != 0) {
            usleep(SPEED * 1000); // In microseconds
            nextGeneration(grid, HEIGHT, WIDTH);
            system("clear");
        }
    }
    
    else {
        if (strcmp(argv[1], "glider") == 0) {
            initGlider(grid, HEIGHT, WIDTH, 0);
            while (printGrid(grid, HEIGHT, WIDTH) != 0) {
                usleep(SPEED * 1000); // In microseconds
                nextGeneration(grid, HEIGHT, WIDTH);
                system("clear");
            }
        }

        else {
            fprintf(stderr, "Usage: %s glider\n", program);
            exit(1);
        }
    }
}
