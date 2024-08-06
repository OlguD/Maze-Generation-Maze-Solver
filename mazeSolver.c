#include <stdbool.h>
#include <stdio.h>
#include "mazeSolver.h"
// 0 -> wall
// 1 -> path
// 2 -> exit

Coordinate directions[4] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

int main(){
    int maze[WIDTH][HEIGHT];

    loadMazeFromFile(maze);

    if (solveMaze(maze, 1, 1, WIDTH - 2, HEIGHT - 2)) {
        printf("Maze solved:\n");
    } else {
        printf("No solution found.\n");
    }

    printSolvedMaze(maze);
}



bool isValidMove(int maze[WIDTH][HEIGHT], int x, int y){
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && maze[x][y] == PATH;
}


void printSolvedMaze(int maze[WIDTH][HEIGHT]){
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (maze[x][y] == WALL) {
                printf("\033[31m# \033[0m"); // Kırmızı renk
            } else if (maze[x][y] == VISITED) {
                printf("\033[32m. \033[0m"); // Yeşil renk
            } else {
                printf("  "); // Varsayılan renk (boş yol)
            }
        }
        printf("\n");
    }
}



bool solveMaze(int maze[WIDTH][HEIGHT], int x, int y, int endX, int endY) {
    if (x == endX && y == endY) {
        maze[x][y] = VISITED;
        return true;
    }

    if (isValidMove(maze, x, y)) {
        maze[x][y] = VISITED;

        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i].x;
            int newY = y + directions[i].y;

            if (solveMaze(maze, newX, newY, endX, endY)) {
                return true;
            }
        }

        maze[x][y] = PATH; // Geri dön
    }

    return false;
}


void loadMazeFromFile(int maze[WIDTH][HEIGHT]){
    FILE *file = fopen("maze.txt", "r");

    if (file == NULL){
        printf("Error opening maze file");
    }

    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<WIDTH; x++){
            fscanf(file, "%d", &maze[x][y]);
        }
    }
    fclose(file);
}
