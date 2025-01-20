#include "valid_valuation.h"

// Function to parse ranges from the file
void parse_ranges(const char *filename, int values[]) {
	int ranges[10][2], size=10;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        //return -1;
    }
	int i;
	int is_valid;
	char line[1024];
	
	while(fgets(line,sizeof(line),file)){
		line[strcspn(line, "\n")] = 0;
		int offset = 0;
    for ( i = 0; i < size; i++) {
        if (sscanf(line+offset, " [%d %d]", &ranges[i][0], &ranges[i][1]) != 2) {
            fprintf(stderr, "Error reading range %d\n", i + 1);
            fclose(file);
            exit(1);
            //return -1;
        }
        while (line[offset] && line[offset] != ']') {
            offset++;
        }
        if (line[offset]) {
            offset++;  // Skip the closing ']'
        }
    }
    is_valid = check_values(values, ranges, 10);
    if(is_valid){
    	//return 1;
	}
}

	for (i = 0; i < size; i++) {
		if (!(values[i] >= ranges[i][0] && values[i] <= ranges[i][1])){
			values[i] = ranges[i][0];
		}
	}
    

    fclose(file);
    //return 0;
}

// Function to check if values are within the ranges
int check_values(int values[], int ranges[][2], int size) {
	int i, flag;
    for (i = 0; i < size; i++) {
        if (values[i] >= ranges[i][0] && values[i] <= ranges[i][1]) {
            //printf("Value %d (%d) is within range [%d, %d]\n", i + 1, values[i], ranges[i][0], ranges[i][1]);
            flag = 1;
        } else {
        	//printf("Value %d (%d) is not within range [%d, %d]\n", i + 1, values[i], ranges[i][0], ranges[i][1]);
            return 0;
        }
    }
    return flag;
}
/*
void get_first_range_set(char* filename, int ranges[][2], int size){
	FILE *file = fopen(filename, "r");
	char line[1024];
	fgets(line,sizeof(line),file);
	line[strcspn(line, "\n")] = 0;
		int offset = 0,i;
    for ( i = 0; i < size; i++) {
        if (sscanf(line+offset, " [%d %d]", &ranges[i][0], &ranges[i][1]) != 2) {
            fprintf(stderr, "Error reading range %d\n", i + 1);
            fclose(file);
            exit(1);
            //return -1;
        }
        while (line[offset] && line[offset] != ']') {
            offset++;
        }
        if (line[offset]) {
            offset++;  // Skip the closing ']'
        }
    }
}

void edit_values(char* filename, int values[]){
	int size = 10,i,ranges[10][2];
	get_first_range_set(filename, ranges, size);
	for (i = 0; i < size; i++) {
		if (!(values[i] >= ranges[i][0] && values[i] <= ranges[i][1])){
			values[i] = ranges[i][0];
		}
	}
}
*/

//void check_validity(char* filename, int values[]) {
    //const char *filename = "ranges.txt"; // File containing the ranges
   // int ranges[10][2];                  // Array to store ranges
    //int values[]={23,45,67,89,0,11,2,3,0,0};                     // Array to store input values

// Prompt the user for input values
//    printf("Enter 10 values to check:\n");
//    int i;
//    for (i = 0; i < 10; i++) {
//        printf("Value %d: ", i + 1);
//        scanf("%d", &values[i]);
//    }

    // Parse ranges from the file
//    if (parse_ranges(filename, ranges, 10, values) == 0) {
//        //fprintf(stderr, "Failed to parse ranges from file.\n");
//        printf("T valuation is invalid\n");
//    }
//    if(parse_ranges(filename, ranges, 10, values) == 1){
//    	printf("The valuation is valid\n");
//	}
//	if(parse_ranges(filename, ranges, 10, values) == -1){
//		printf("Error in parsing ranges\n");
//	}

    

    // Check if values are within the ranges
    //check_values(values, ranges, 10);

   // return parse_ranges(filename,ranges,10,values);
//}

