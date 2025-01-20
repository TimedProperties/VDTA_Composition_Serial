#include "F_ab5.h"
#include <stdio.h>
#include <stdint.h>

void print_data(uint32_t count, inputs_ab5_t inputs, outputs_ab5_t outputs) {
    printf("Tick %7d: A:%d, B:%d\r\n", count, inputs.A, outputs.B);
}

int main() {
    enforcervars_ab5_t enf;
    inputs_ab5_t inputs;
    outputs_ab5_t outputs;
    int i=0;
    ab5_init_all_vars(&enf, &inputs, &outputs);

    uint32_t count = 0;
    while(count++ < 30) {
        if(count % 10 == 0) {
            inputs.A = true;
        } else {
            inputs.A = false;
        }
        i=0;
        ab5_run_via_enforcer(&enf, &inputs, &outputs);

        printf(" State = %d ",enf._policy_AB5_state);
        //printf("Valid transition = %s\t",enf.valid_transition[0]);
        while(enf.valid_transition[i]){
            printf("Valid transition = %s\t",enf.valid_transition[i]);
            i++;
        }
        print_data(count, inputs, outputs);
        
        //printf()
    }
    printf("I have made some change in ab5_main.c\n");
    getch();
}

void ab5_run(inputs_ab5_t *inputs, outputs_ab5_t *outputs) {
    //do nothing
}

