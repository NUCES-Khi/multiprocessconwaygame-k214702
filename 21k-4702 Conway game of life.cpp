#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
//21k-4702
void RowUpdater(int *grid, int *newGrid, int row, int n) {
    int neighbors;
    for (int col = 0; col < n; col++) {
        neighbors = 0;
        for (int r = row - 1; r <= row + 1; r++) {
            for (int c = col - 1; c <= col + 1; c++) {
                if (r >= 0 && r < n && c >= 0 && c < n && !(r == row && c == col) && grid[r * n + c] == 1) {
                    neighbors++;
                }
            }
        }


void printGen(int *grid, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i * n + j]);
        }
        printf("\n");
    }
}


        if (grid[row * n + col] == 1) {
            if (neighbors == 2 || neighbors == 3) {
                newGrid[row * n + col] = 1;
            } else {
                newGrid[row * n + col] = 0;
            }
        } else {
            if (neighbors == 3) {
                newGrid[row * n + col] = 1;
            } else {
                newGrid[row * n + col] = 0;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the size of your grid NxN = ");
    scanf("%d", &n);

    int *grid = (int *)malloc(n * n * sizeof(int));
    int *newGrid = (int *)malloc(n * n * sizeof(int));

    printf("Enter your first state of the grid 0(dead), 1(alive)=\n");
    for (int i = 0; i < n * n; i++) {
        scanf("%d", &grid[i]);
    }

    int gen;
    printf("Enter the number of generations to simulate = ");
    scanf("%d", &gen);

    int **pipes = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        pipes[i] = (int *)malloc(2 * sizeof(int));
        pipe(pipes[i]);
    }

    for (int g = 1; g <= gen; g++) {
        for (int row = 0; row < n; row++) {
            pid_t pid = fork();
            if (pid == 0) {
                close(pipes[row][0]); 
                RowUpdater(grid, newGrid, row, n);
                write(pipes[row][1], newGrid + row * n, n * sizeof(int));
                exit(0);
            } else if (pid== -1) {
            // Usually not required as per our course
                printf("Error forking process.\n");
                exit(1);
            }
    }    
        for (int row = 0; row < n; row++) {
            wait(NULL);
        }

        for (int row = 0; row < n; row++) {
            read(pipes[row][0], newGrid + row * n, n * sizeof(int));
        }

        memcpy(grid, newGrid, n * n * sizeof(int));
    }

    printf("Final generation:\n");
    printGen(grid, n);

    free(grid);
    free(newGrid);
    for (int i = 0; i < n; i++) {
       free(pipes[i]);
    }
    free(pipes);

    return 0;
}
