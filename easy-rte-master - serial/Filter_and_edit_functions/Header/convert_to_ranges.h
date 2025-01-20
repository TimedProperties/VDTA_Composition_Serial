//Header
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define NUM_VARS 10
#define DEFAULT_MIN 0
#define DEFAULT_MAX 500

typedef struct {
    int min;
    int max;
} Range;


void parseCondition(char *condition, Range *ranges, char *variables);

int hasConflict(Range *ranges);

void processPredicate(char *predicate, Range *ranges, char *variables);

void predicate_to_range(char *filePred, char* fileRange);
