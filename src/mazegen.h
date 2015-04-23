/*
 * MazeGen.c -- Mark Howell -- 8 May 1991
 *
 * Usage: MazeGen [width [height [seed]]]
 */

#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "adv.h"
#include "level.h"
#include "config.h"
#include "file.h"
#include "toolfuncs.h"

#define WIDTH  10
#define HEIGHT 10

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

#ifdef TRUE
#undef TRUE
#endif /* TRUE */

#define TRUE 1

#define cell_empty(a) (!(a)->up && !(a)->right && !(a)->down && !(a)->left)

typedef struct {
    unsigned int id;
    unsigned int up;
    unsigned int right;
    unsigned int down;
    unsigned int left;
    unsigned int path;
    unsigned int visited;
} cell_t;
typedef cell_t *maze_t;

int MazeMain(ST_FILE *pstFile);
void CreateMaze (maze_t maze, int width, int height);
void SolveMaze (maze_t maze, int width, int height);
void PrintMaze (maze_t maze, int width, int height);
void SaveMaze (ST_FILE *pstFile, maze_t maze, int width, int height);

#endif