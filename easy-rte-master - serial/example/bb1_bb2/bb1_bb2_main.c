#include "F_bb1_bb2.h"
#include <stdio.h>

void print_data(uint32_t count, inputs_bb1_bb2_t inputs, outputs_bb1_bb2_t outputs) {
    printf("Tick %7d: x:%d  y:%d  z:%d  psi:%d  x_up:%d  x_down:%d  y_up:%d y_down:%d z_up:%d  z_down:%d\r\n", count, inputs.x, inputs.y, inputs.z, inputs.psi, outputs.x_up, outputs.x_down, outputs.y_up, outputs.y_down, outputs.z_up, outputs.z_down);
}

int main() {
    enforcervars_bb1_bb2_t enf;
    inputs_bb1_bb2_t inputs;
    outputs_bb1_bb2_t outputs;
    
    bb1_bb2_init_all_vars(&enf, &inputs, &outputs);
    
    inputs.x = 0;
    inputs.y = 0;
    inputs.z = 0;
    inputs.psi = 0;
    outputs.x_up = 0;
    outputs.x_down = 0;
    outputs.y_up = 0;
    outputs.y_down = 0;
    outputs.z_up = 0;
    outputs.z_down = 0;

    uint32_t count = 0;
    while(count++ < 50) {
//        if(count % 10 == 0) {
//            inputs.A = true;
//        } else {
//            inputs.A = false;
//        }
		if(count==20){
			outputs.z_down = 1;
		}

        bb1_bb2_run_via_enforcer(&enf, &inputs, &outputs);

        print_data(count, inputs, outputs);
    }
    char  ch;
    ch = getchar();
    return 0;
}

void bb1_bb2_run(inputs_bb1_bb2_t *inputs, outputs_bb1_bb2_t *outputs) {
    //do nothing
}

