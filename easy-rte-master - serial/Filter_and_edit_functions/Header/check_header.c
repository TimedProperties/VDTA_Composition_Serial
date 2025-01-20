#include "convert_to_ranges.c"

int main(){
	printf("Checking the use of convert to ranges.h\n");
	predicate_to_range("predicates.txt","ranges.txt");
	return 0;
}
