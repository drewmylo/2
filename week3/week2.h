#ifndef DAY3_H
#define DAY3_H
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    char** binaryArray;
    int width;
    int height;
} BinaryArray; 
int read_instruction(FILE* fp, BinaryArray* binaryArray, int position);
int get_instruction_length(FILE* fp);
void part_A(BinaryArray* binaryArray, int* answer1, int* answer2);
void free_mem(BinaryArray* binaryArray);
#endif