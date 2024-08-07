#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H


#define WALL 0
#define PATH 1
#define VISITED 2

#include "mazeGenerator.h"
#include <stdbool.h>
typedef struct{
    int x, y;
}Coordinate;


bool isValidMove(int maze[WIDTH][HEIGHT], int x, int y);
void printSolvedMaze(int maze[WIDTH][HEIGHT]);
void loadMazeFromFile(char filename[], int maze[WIDTH][HEIGHT]);
bool solveMaze(int maze[WIDTH][HEIGHT], int x, int y, int endX, int endY);


#endif

