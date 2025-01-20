#include "F_drone_lh.h"
#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include <time.h>


#include "valid_valuation.c"
#include "convert_to_ranges.c"

//#include <fstream>
#define MAX_LINE_LENGTH 256
void print_data(uint32_t count, inputs_drone_lh_t inputs, outputs_drone_lh_t outputs) {
    printf("Tick %7d: X:%d, Y:%d Z:%d P:%d A:%d, B:%d C:%d D:%d E:%d F:%d\r\n", count, inputs.X, inputs.Y, inputs.Z, inputs.P, outputs.A, outputs.B, outputs.C, outputs.D, outputs.E, outputs.F);
}

int main() {
    enforcervars_drone_lh_t enf;
    inputs_drone_lh_t inputs;
    outputs_drone_lh_t outputs;
    int i=0, values[10];
    //char [] = "temp.txt";
    drone_lh_init_all_vars(&enf, &inputs, &outputs);

    FILE *file;
    char channel_values[MAX_LINE_LENGTH];
    int X, Y, Z, P, A, B, C, D, E, F;
    file = fopen("input.txt", "r");
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    
    const char *filename = "valid_transitions.txt";



    char buffer[256];
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // Handle all semaphores
    HANDLE sem3 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaphore3");
    HANDLE sem1 = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "Semaphore1");
    
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        //exit(1);
        getchar();
        return 0;
    }
    
    clock_t start, end;
    double time_in_ms;
    
	start = clock();
	
    uint32_t count = 0;
    while (fgets(channel_values, sizeof(channel_values), file)) {
    	
    	 WaitForSingleObject(sem3, INFINITE); 
    	 
    
    	
    	//    // Open the file for reading
    FILE *validTrFile = fopen(filename, "r");
    if (validTrFile == NULL) {
        printf("Error: Could not open file for reading.\n");
        return 1;
    }
//
//    // Create a temporary file
    	FILE *tempFile = fopen("temp.txt", "w");
       	if (tempFile == NULL) {
       	printf("Error: Could not create temporary file.\n");
       	fclose(tempFile);
       	return 1;
    	}
        count++;
        if(sscanf(channel_values, "%d %d %d %d %d %d %d %d %d %d", &X, &Y, &Z, &P, &A, &B, &C, &D, &E, &F) == 10){
       inputs.X = X;
       inputs.Y = Y;
       inputs.Z = Z;
       inputs.P = P;
       outputs.A = A;
       outputs.B = B;
       outputs.C = C;
       outputs.D = D;
       outputs.E = E;
       outputs.F = F;
        i=0;
        printf(" State = %d ",enf._policy_DRONE_LH_state);
        //FILE *tempfile = fopen(file_name, "w");
        drone_lh_give_valid_transitions(&enf);
        //////////////////////////////
       
        while(enf.valid_transitions[i]){
        	//printf("I have entered outerwhile\n");
    		char appendText[250] = " && ";
        	strcat(appendText,enf.valid_transitions[i]);
        	printf("%s\n", appendText);
        	while (fgets(buffer, sizeof(buffer), validTrFile)) {
        // Remove newline character if present
        		//printf("I am inside inner while");
        		//strcpy(appendText, enf.valid_transitions[i]);
        		size_t len = strlen(buffer);
        		if (len > 0 && buffer[len - 1] == '\n') {
            		buffer[len - 1] = '\0';
        		}
				//rintf("Validtr: %s\n",buffer);
        		fprintf(tempFile, "%s%s\n", buffer, appendText);
        		//printf("Successfully written\n");
    		}
    		rewind(validTrFile);
    		i++;
		}
		fclose(validTrFile);
		fclose(tempFile);
		
		if(remove("valid_transitions.txt")==0)
			printf("Remove Successful\n");
			
    	if(rename("temp.txt","valid_transitions.txt")==0)
			printf("Rename Succesful\n");
		else{
			printf("Rename Unsuccessful\n");
			perror("Error:");
			printf("\n");
		}
		predicate_to_range("valid_transitions.txt","ranges.txt");
		
		values[0] =inputs.X;
		values[1] =inputs.Y;
		values[2] =inputs.Z;
		values[3] =inputs.P;
		values[4] =outputs.A;
		values[5] =outputs.B;
		values[6] =outputs.C;
		values[7] =outputs.D;
		values[8] =outputs.E;
		values[9] =outputs.F;
		
		parse_ranges("ranges.txt",values);
		
		 
        
        //////////////////////////
//        if(tempfile){
//            while(enf.valid_transitions[i]){
//                fprintf(tempfile, "%s\n", enf.valid_transitions[i]);
//                printf("Writing %s to file %s\n", enf.valid_transitions[i], file_name);
//                i++;
//            }
//            fclose(tempfile);
//        }
//        else
//            printf("Error: Unable to open file %s\n", file_name);
        //printf("Valid transition = %s\t",enf.valid_transitions[0]);
        
        /*while(enf.valid_transitions[i]){
            printf("Valid transition = %s\t",enf.valid_transitions[i]);
            i++;
        }*/
        ReleaseSemaphore(sem1, 1, NULL);
        
        WaitForSingleObject(sem3, INFINITE);
        
       
		
		inputs.X = values[0];
		inputs.Y = values[1];
		inputs.Z = values[2];
		inputs.P = values[3];
		outputs.A = values[4];
		outputs.B = values[5];
		outputs.C = values[6];
		outputs.D = values[7];
		outputs.E = values[8];
		outputs.F = values[9];
        
        drone_lh_run_via_enforcer(&enf, &inputs, &outputs);

        
        print_data(count, inputs, outputs);
        }
        else
            printf("Bad input format\n");
        //printf()
        
        
      //getchar();
     ReleaseSemaphore(sem1, 1, NULL);
    }
    //printf("I have made some change in ab5_main.c\n");
    printf("I am outside while loop of drone_lh\n");
    end = clock();
    
     time_in_ms = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

    // Print the result
    printf("Execution time: %.3f ms\n", time_in_ms);
    printf("-------------------------------------------------\n-------------------------------------------\nEnd of program. Press Enter");
  getchar();
    
}

void drone_lh_run(inputs_drone_lh_t *inputs, outputs_drone_lh_t *outputs) {
    //do nothing
    //outputs->C
}
/*
FILE *outfile = fopen(filename2, "a"); // Open in append mode

    if (outfile) {
        fprintf(outfile, "\nExclude:\n");
        for (int i = 0; i < exclusion_count; i++) {
            fprintf(outfile, "%d %d\n", exclusions[i].first, exclusions[i].second);
        }
        fclose(outfile);
        printf("Vector of pairs appended to the file successfully.\n");
    } else {
        printf("Error: Unable to open the file %s!\n", filename2);
    }
*/
