#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bits/stdc++.h"
#define UP 0    //-y
#define DOWN 1  //+y
#define LEFT 2  //-x
#define RIGHT 3 //+x
#define OUTFILE "MAZE"
#define WHITE fprintf(outfile, "%c%c%c", 255, 255, 255)
#define BLACK fprintf(outfile, "%c%c%c", 0, 0, 0)
#define RED fprintf(outfile, "%c%c%c", 0, 0, 255)

#define nodeadend //generate a maze without any dead ends! (consequently, many solutions to maze)
#define prim      //enable this to generate mazes using prim's algorithm.
// #define backtrack//enable this to generate mazes using depth-first search. Don't enable both.
// #define movie   //this option spams bitmaps to illustrate each step of generation.
using namespace std;

void initialize();
void generate();
void savebmp(int xspecial, int yspecial);
int maze_generate();

#endif