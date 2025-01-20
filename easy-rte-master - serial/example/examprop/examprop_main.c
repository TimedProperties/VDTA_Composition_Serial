#include "F_examprop.h"
#include <stdio.h>
#include <stdint.h>
//#include <fstream>
#define MAX_LINE_LENGTH 256
void print_data(uint32_t count, inputs_examprop_t inputs, outputs_examprop_t outputs) {
    printf("Tick %7d: A:%d, B:%d C:%d D:%d\r\n", count, inputs.A, inputs.B, outputs.C, outputs.D);
}

int main() {
    enforcervars_examprop_t enf;
    inputs_examprop_t inputs;
    outputs_examprop_t outputs;
    int i=0;
    char file_name[] = "example/examprop/valid_transitions.txt";
    examprop_init_all_vars(&enf, &inputs, &outputs);

    FILE *file;
    char channel_values[MAX_LINE_LENGTH];
    int a, b, c, d;
    file = fopen("example/examprop/input.txt", "r");

    if (file == NULL) {
        printf("Error: Could not open file.\n");
        //exit(1);
        getch();
        return 0;
    }

    uint32_t count = 0;
    while (fgets(channel_values, sizeof(channel_values), file)) {
        count++;
        if(sscanf(channel_values, "%d %d %d %d", &a, &b, &c, &d) == 4){
       inputs.A = a;
       inputs.B = b;
       outputs.C = c;
       outputs.D = d;
        i=0;
        printf(" State = %d ",enf._policy_EXAMPROP_state);
        FILE *outfile = fopen(file_name, "w");
        examprop_give_valid_transitions(&enf);
        if(outfile){
            while(enf.valid_transition[i]){
                fprintf(outfile, "%s\n", enf.valid_transition[i]);
                printf("Writing %s to file %s\n", enf.valid_transition[i], file_name);
                i++;
            }
            fclose(outfile);
        }
        else
            printf("Error: Unable to open file %s\n", file_name);
        //printf("Valid transition = %s\t",enf.valid_transition[0]);
        
        /*while(enf.valid_transition[i]){
            printf("Valid transition = %s\t",enf.valid_transition[i]);
            i++;
        }*/
        
        examprop_run_via_enforcer(&enf, &inputs, &outputs);

        
        print_data(count, inputs, outputs);
        }
        else
            printf("Bad input format\n");
        //printf()
    }
    //printf("I have made some change in ab5_main.c\n");
    getch();
}

void examprop_run(inputs_examprop_t *inputs, outputs_examprop_t *outputs) {
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
