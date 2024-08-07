#include "utils.h"
#include <stdio.h>

Coordinate directions[4] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
};

int stepX = 0;
int stepY = 0;

void loadMazeFromFile(char filename[], int maze[WIDTH][HEIGHT]) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening maze file");
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fscanf(file, "%d", &maze[x][y]);
        }
    }
    fclose(file);
}

bool isValidMove(int maze[WIDTH][HEIGHT], int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && maze[x][y] == PATH;
}

bool solveMazeStep(int maze[WIDTH][HEIGHT], int x, int y, int endX, int endY) {
    if (x == endX && y == endY) {
        maze[x][y] = VISITED;
        stepX = x;
        stepY = y;
        return true;
    }

    if (isValidMove(maze, x, y)) {
        maze[x][y] = VISITED;
        stepX = x;
        stepY = y;
        return false;
    }

    return false;
}

void setStart(int x, int y) {
    stepX = x;
    stepY = y;
}

bool backtrack(int maze[WIDTH][HEIGHT], int *x, int *y) {
    for (int i = 0; i < 4; i++) {
        int newX = *x + directions[i].x;
        int newY = *y + directions[i].y;
        if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && maze[newX][newY] == VISITED) {
            *x = newX;
            *y = newY;
            return true;
        }
    }
    maze[*x][*y] = BACKTRACK;
    return false;
}