# Conway's Game of Life

## Things I Learnt

- Use `size_t` instead of `int` while dealing with sizes, for example, while initializing the grid, since the size of `size_t` is platform-dependent and is usually chosen to be the most efficient unsigned integer type that can represent the maximum size of an object.

- Use `#define` instead of magic values in code so that parameters can be changed easily and code is more readable

- The `usleep` function is a C function used for introducing a delay (in microseconds) in the execution of a program. It is present in the `unistd.h` header file.