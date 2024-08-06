#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mazeGenerator.h"

int main(){


    int maze[WIDTH][HEIGHT];
    srand(time(NULL));

    initMaze(maze);
    generateMaze(maze, 1, 1);
    printMaze(maze);

    saveMazeToFile(maze);

    return 0;
}


void initMaze(int maze[WIDTH][HEIGHT]){

    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<WIDTH; x++){
            maze[x][y] = WALL;    
        }
    }
}

void printMaze(int maze[WIDTH][HEIGHT]){

    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<WIDTH; x++){
            if (maze[x][y] == WALL){
                printf("# ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }

}


void saveMazeToFile(int maze[WIDTH][HEIGHT]){
    FILE *file = fopen("maze.txt", "w");
    if (file == NULL){
        perror("Unable to open file for writing");
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(file, "%d ", maze[x][y]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


void generateMaze(int maze[WIDTH][HEIGHT], int x, int y){
    int directions[4] = {0, 1, 2, 3};

    for (int i=0; i<4; i++){
        int j = rand() % 4;
        int temp = directions[i];
        directions[j] = temp;
    }

    maze[x][y] = PATH;

    for (int i=0; i<4; i++){
        int dir = directions[i];
        int nx = x, ny = y;

        switch (dir) {
            case 0: nx = x + 2; break; // SAĞ
            case 1: nx = x - 2; break; // SOL
            case 2: ny = y + 2; break; // AŞAĞI
            case 3: ny = y - 2; break; // YUKARI
        }

        if (nx >= 1 && nx < WIDTH -1 && ny >= 1 && ny < HEIGHT - 1 && maze[nx][ny] == WALL){
            maze[(nx + x) / 2][(ny + y) / 2] = PATH; 

            generateMaze(maze, nx, ny);
        }
    }
}
