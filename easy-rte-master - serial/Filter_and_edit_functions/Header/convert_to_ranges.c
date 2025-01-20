#include "convert_to_ranges.h"

void parseCondition(char *condition, Range *ranges, char *variables) {
    char var;
    char op[3] = {0};
    int value;

    // Parse the condition
    if (sscanf(condition, " %c %2[><=!]= %d", &var, op, &value) == 3 ||
        sscanf(condition, " %c %1[><] %d", &var, op, &value) == 3) {
        int index = strchr(variables, var) - variables;

        if (strcmp(op, "==") == 0) {
            // Handle equality
            if (value < ranges[index].min || value > ranges[index].max) {
                // Conflict detected
                ranges[index].min = INT_MAX;
                ranges[index].max = INT_MIN;
            } else {
                ranges[index].min = value;
                ranges[index].max = value;
            }
        } else if (strcmp(op, ">") == 0) {
            if (value + 1 > ranges[index].max) {
                // Conflict detected
                ranges[index].min = INT_MAX;
                ranges[index].max = INT_MIN;
            } else if (value + 1 > ranges[index].min) {
                ranges[index].min = value + 1;
            }
        } else if (strcmp(op, ">=") == 0) {
            if (value > ranges[index].max) {
                // Conflict detected
                ranges[index].min = INT_MAX;
                ranges[index].max = INT_MIN;
            } else if (value > ranges[index].min) {
                ranges[index].min = value;
            }
        } else if (strcmp(op, "<") == 0) {
            if (value - 1 < ranges[index].min) {
                // Conflict detected
                ranges[index].min = INT_MAX;
                ranges[index].max = INT_MIN;
            } else if (value - 1 < ranges[index].max) {
                ranges[index].max = value - 1;
            }
        } else if (strcmp(op, "<=") == 0) {
            if (value < ranges[index].min) {
                // Conflict detected
                ranges[index].min = INT_MAX;
                ranges[index].max = INT_MIN;
            } else if (value < ranges[index].max) {
                ranges[index].max = value;
            }
        }
    } else if (sscanf(condition, " %c == %d", &var, &value) == 2) {
        // Handle equality (alternative parsing for `==`)
        int index = strchr(variables, var) - variables;
        if (value < ranges[index].min || value > ranges[index].max) {
            // Conflict detected
            ranges[index].min = INT_MAX;
            ranges[index].max = INT_MIN;
        } else {
            ranges[index].min = value;
            ranges[index].max = value;
        }
    }
}

// Function to check for conflicts in ranges
int hasConflict(Range *ranges) {
	int i;
    for (i = 0; i < NUM_VARS; i++) {
        if (ranges[i].min > ranges[i].max) {
            return 1; // Conflict detected
        }
    }
    return 0;
}

// Function to process a single predicate
void processPredicate(char *predicate, Range *ranges, char *variables) {
	int i;
    // Initialize ranges with default values
    for ( i = 0; i < NUM_VARS; i++) {
        ranges[i].min = DEFAULT_MIN;
        ranges[i].max = DEFAULT_MAX;
    }

    // Tokenize the predicate by '&&'
    char *condition = strtok(predicate, "&&");
    while (condition != NULL) {
        parseCondition(condition, ranges, variables);
        condition = strtok(NULL, "&&");
    }
}

void predicate_to_range(char *filePred, char* fileRange) {
    // Array of variable names
    char variables[NUM_VARS] = {'X', 'Y', 'Z', 'P', 'A', 'B', 'C', 'D', 'E', 'F'};
	int i;
    // File containing predicates
    FILE *inputFile = fopen(filePred, "r");
    if (!inputFile) {
        perror("Error opening input file");
        //return 1;
        exit(1);
    }

    // File to write ranges
    FILE *outputFile = fopen(fileRange, "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        //return 1;
        exit(1);
    }

    char line[1024];
    Range ranges[NUM_VARS];

    while (fgets(line, sizeof(line), inputFile)) {
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Process the predicate
        processPredicate(line, ranges, variables);

        // Check for conflicts
        if (!hasConflict(ranges)) {
            // Write the ranges to the output file
            for (i = 0; i < NUM_VARS; i++) {
                fprintf(outputFile, "[%d %d] ", ranges[i].min, ranges[i].max);
            }
            fprintf(outputFile, "\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);
    //printf("Non-conflicting ranges written to ranges.txt\n");

    //return 0;
}
