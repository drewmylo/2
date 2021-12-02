#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "week2.h"

int read_instruction(FILE* fp, int* delta, char* string) {
    return fscanf(fp, "%s %d\n", string, delta);      
}

void part_A(Coords* coords, char* string, int delta) {
    switch (string[0]) {
        case 'f':
            coords->x += delta;
            break;

        case 'd':
            coords->y += delta;
            break;

        case 'u':
            coords->y -= delta;
            break;
            }
}

void part_B(Coords* coords, char* string, int delta) {
    switch (string[0]) {
        case 'f':
            coords->x += delta;
            coords->y += (delta * coords->aim);
            break;

        case 'd':
            coords->aim += delta;
            break;

        case 'u':
            coords->aim -= delta;
            break;
            }
}

void free_mem(Coords* coords) {
    free(coords);
}

int main(int argc, char** argv) {
    FILE * fp;
    fp = fopen("./input.txt", "r");
    int delta;
    char string[7];
    Coords* coords = calloc(1, sizeof(Coords));
    while (read_instruction(fp, &delta, string) == 2){
        part_A(coords, string, delta);
    }
    printf("Part A: %d\n", coords->x * coords->y);

    memset(coords, 0, sizeof(Coords));
    rewind(fp);

    while (read_instruction(fp, &delta, string) == 2){
        part_B(coords, string, delta);
    }
    printf("Part B: %d\n", coords->x * coords->y);


    free_mem(coords);
    fclose(fp);
    exit(EXIT_SUCCESS);
}