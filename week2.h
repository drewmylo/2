#ifndef WEEK2_H
#define WEEK2_H
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int x;
    int y;
    int aim;
} Coords; 
int read_instruction(FILE* fp, int* delta, char* string);
void part_A(Coords* coords, char* string, int delta);
void part_B(Coords* coords, char* string, int delta);
void free_mem(Coords* coords);
#endif