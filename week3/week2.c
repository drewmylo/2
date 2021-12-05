#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "week2.h"

int read_instruction(FILE * fp, BinaryArray* binaryArray, int position) {
    char buffer[300];
    fgets(buffer, 300, fp);    
    int lengthToCopy = strlen(buffer);
    buffer[lengthToCopy - 1] = '\0';
    binaryArray->binaryArray[position] = calloc(lengthToCopy, sizeof(char));
    strcpy(binaryArray->binaryArray[position], buffer);
    return lengthToCopy;
}


void part_A(BinaryArray* binaryArray, int* answer1, int* answer2) {
    int finalArray[12] = {0};
    
    for (int x = 0; x < binaryArray->height; x++) {
        for (int y = 0; y < binaryArray->width; y++)
        {
            finalArray[y] += (binaryArray->binaryArray[x][y] - 48);
        }
    }

    int finalBinary = 0; 
    for (int i = 0; i < binaryArray->width; i++) {
        if (finalArray[i] > (binaryArray->height / 2)) {
            finalBinary = finalBinary << 1;
            finalBinary = finalBinary | 1;
        }
        else {
            finalBinary = finalBinary << 1;
        }       
    } 

    *answer1 = finalBinary & 0b111111111111;
    *answer2 = ~finalBinary & 0b111111111111;
    printf("Final answer: %u\n", (((*answer1)) * (*answer2)));
}

unsigned int binary_char_array_to_int(char* binary, int width) {
    unsigned int result = 0;
    for (int i = 0; i < width; i++) {
        if (binary[i] == '1') {
            result = result << 1;
            result = result | 1;
        }
        else {
            result = result << 1;
        }       
    } 
    return result & 0b111111111111;
}

char find_most_common_bit(char** strings, int size, int bitPosition) {
    int count = 0;
    for (int x = 0; x < size; x++)
    {
        if (strings[x][bitPosition] == '1')
        {
            count++;
        }       
    }
    if (count >= (size / 2)) {
        return '1';     
    }
    else {
        return '0';
    }
}

char find_least_common_bit(char** strings, int size, int bitPosition) {
    int count = 0;
    for (int x = 0; x < size; x++)
    {
        if (strings[x][bitPosition] == '0')
        {
            count++;
        }       
    }
    if (count <= (size / 2)) {
        return '0';     
    }
    else {
        return '1';
    }
}

char** return_strings_with_bit(char** strings, int size, char bit, int bitPosition, int* newSize){
    char** newSetOfStrings = calloc(*newSize, sizeof(char *));
    *newSize = 0;

    for (int x = 0; x < size; x++)
    {
        if (strings[x][bitPosition] == bit)
        {
            (*newSize)++;
            newSetOfStrings = realloc(newSetOfStrings, *newSize * sizeof(char*));
            newSetOfStrings[(*newSize) - 1] = calloc(13, sizeof(char));
            strcpy(newSetOfStrings[(*newSize) - 1], strings[x]);
        }       
    }

    return newSetOfStrings;
}

void part_B(BinaryArray* binaryArray) {
    int newSize = 1000;
    int bitPosition = 0;
    char mostCommonDigit;
    char** newArray = binaryArray->binaryArray;
    while (newSize > 1 && bitPosition < binaryArray->width)
    {
        mostCommonDigit = find_most_common_bit(newArray, newSize, bitPosition);
        newArray = return_strings_with_bit(newArray, newSize, mostCommonDigit, bitPosition, &newSize);
        bitPosition++;
    }
    int answer1 = binary_char_array_to_int(newArray[0], 12);

    int newSize2 = 1000;
    int bitPosition2 = 0;
    char leastCommonDigit;
    char** newArray2 = binaryArray->binaryArray;
    while (newSize2 > 1 && bitPosition2 < binaryArray->width)
    {
        leastCommonDigit = find_least_common_bit(newArray2, newSize2, bitPosition2);
        newArray2 = return_strings_with_bit(newArray2, newSize2, leastCommonDigit, bitPosition2, &newSize2);
        bitPosition2++;
    }
    printf("answer ===== %u\n", (binary_char_array_to_int(newArray2[0], 12) * answer1));

}

void free_mem(BinaryArray* binaryArray) {
    free(binaryArray);
}

int main(int argc, char** argv) {
    FILE * fp;
    fp = fopen("./input.txt", "r");
    BinaryArray* binaryArray = calloc(1, sizeof(BinaryArray));
    binaryArray->height = 1000;
    binaryArray->width = 12;
    binaryArray->binaryArray = calloc(binaryArray->height, sizeof(char *));
    for (int x = 0; x < binaryArray->height; x++) {
        read_instruction(fp, binaryArray, x);
    }
    int oxygen =0;
    int c02 = 0;
    part_A(binaryArray, &oxygen, &c02);
    part_B(binaryArray);

    fclose(fp);
    exit(EXIT_SUCCESS);
}