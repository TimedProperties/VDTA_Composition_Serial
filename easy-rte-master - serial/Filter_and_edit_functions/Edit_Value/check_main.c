#include <stdio.h>
#include "valid_valuation.c"

int main(){
	int flag,i;
	int values[]={12,4,2,6,1,4,5,8,9,8};
	char filename[] = "ranges.txt";
	parse_ranges(filename, values);
	
	for(i = 0; i<10;i++){
		printf("%d  ", values[i]);
	}
//	if (flag == 0) {
//        fprintf(stderr, "Failed to parse ranges from file.\n");
//        printf("T valuation is invalid\n");
//    }
//    if(flag == 1){
//    	printf("The valuation is valid\n");
//	}
//	if(flag == -1){
//		printf("Error in parsing ranges\n");
//	}
//	edit_values(filename,values);
//	flag = parse_ranges(filename, values);
//	if (flag == 0) {
//        fprintf(stderr, "Failed to parse ranges from file.\n");
//        printf("T valuation is invalid\n");
//    }
//    if(flag == 1){
//    	printf("The valuation is valid\n");
//	}
//	if(flag == -1){
//		printf("Error in parsing ranges\n");
//	}
}
