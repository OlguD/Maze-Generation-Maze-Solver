#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H


#define WIDTH 15
#define HEIGHT 15


#define WALL 0
#define PATH 1


void initMaze(int maze[WIDTH][HEIGHT]);
void printMaze(int maze[WIDTH][HEIGHT]);
void generateMaze(int maze[WIDTH][HEIGHT], int x, int y);
void saveMazeToFile(int maze[WIDTH][HEIGHT]);



#endif

