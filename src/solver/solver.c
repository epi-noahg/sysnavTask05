/*
** EPITECH PROJECT, 2021
** ex5
** File description:
** solver.c
*/

#include "../include/open_file.h"
#include "../include/matrix.h"

int recursiveSolve(int x, int y, int endX, int endY, matrix_t *maze, matrix_t *correctPath, matrix_t *wasHere) {
    if (x == endX && y == endY)
        return 1;
    if (maze->matrix[x][y] || wasHere->matrix[x][y])
        return 0;
    wasHere->matrix[x][y] = 1;
    if (x != 0) {
        if (recursiveSolve(x - 1, y, endX, endY, maze, correctPath, wasHere)) {
            correctPath->matrix[x][y] = 1;
            return 1;
        }
    }
    if (x != maze->x_max - 1) {
        if (recursiveSolve(x + 1, y, endX, endY, maze, correctPath, wasHere)) {
            correctPath->matrix[x][y] = 1;
            return 1;
        }
    }
    if (y != 0) {
        if (recursiveSolve(x, y - 1, endX, endY, maze, correctPath, wasHere)) {
            correctPath->matrix[x][y] = 1;
            return 1;
        }
    }
    if (y != maze->y_max - 1) {
        if (recursiveSolve(x, y + 1, endX, endY, maze, correctPath, wasHere)) {
            correctPath->matrix[x][y] = 1;
            return 1;
        }
    }
    return 0;
}

void solveMaze(matrix_t *maze)
{
    matrix_t *wasHere = create_matrix(maze->x_max, maze->y_max);
    matrix_t *correctPath = create_matrix(maze->x_max, maze->y_max);
    int x = 24;
    int y = 21;
    int endX = 14;
    int endY = 29;


    int b = recursiveSolve(x, y, endX, endY, maze, correctPath, wasHere);
    print_matrix(correctPath);
}



int count_char(char *str, char c)
{
    int res = 0;

    for (int i = 0; str[i] != '\0'; i++)
        res += str[i] == c ? 1 : 0;
    return (res);
}

int find_length(char *str)
{
    int i = 0;

    for (; str[i] != '\n'; i++);
    return (i);
}

void solver(char **av)
{
    char *map = open_file(av);
    matrix_t *matrix = create_matrix(find_length(map), count_char(map, '\n'));

    // print_matrix(matrix);
    fill_matrix(matrix->matrix, map);
    solveMaze(matrix);
}