#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_ranges(const char *filename, int values[]);

int check_values(int values[], int ranges[][2], int size);

void get_first_range_set(char* filename, int ranges[][2], int size);

void edit_values(char* filename, int values[]);
