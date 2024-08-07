#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define WIDTH 15
#define HEIGHT 15

#define WALL 0
#define PATH 1
#define VISITED 2
#define BACKTRACK 3

typedef struct {
    int x;
    int y;
} Coordinate;

extern Coordinate directions[4];
extern int stepX;
extern int stepY;

void loadMazeFromFile(char filename[], int maze[WIDTH][HEIGHT]);
bool isValidMove(int maze[WIDTH][HEIGHT], int x, int y);
bool solveMazeStep(int maze[WIDTH][HEIGHT], int x, int y, int endX, int endY);
void setStart(int x, int y);
bool backtrack(int maze[WIDTH][HEIGHT], int *x, int *y);

#endif // UTILS_H
