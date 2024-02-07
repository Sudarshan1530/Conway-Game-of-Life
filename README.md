# Implementation of Conway's Game of Life in C

## Information
The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input.

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead. Every cell interacts with its eight neighbors, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

- Any live cell with fewer than two live neighbors dies, as if by underpopulation.
- Any live cell with two or three live neighbors lives on to the next generation.
- Any live cell with more than three live neighbors dies, as if by overpopulation.
- Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 
## Quick Start

```
make
./conway
```

### Options
```
./conway glider
```
The glider is a pattern that travels across the board in Conway's Game of Life.

## Things I Learnt

- Use `size_t` instead of `int` while dealing with sizes, for example, while initializing the grid, since the size of `size_t` is platform-dependent and is usually chosen to be the most efficient unsigned integer type that can represent the maximum size of an object

- Use `#define` instead of magic values in code so that parameters can be changed easily and code is more readable

- The `usleep` function is a C function used for introducing a delay (in microseconds) in the execution of a program. It is present in the `unistd.h` header file
