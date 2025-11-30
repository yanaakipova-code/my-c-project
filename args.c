#include <stdbool.h>
#include <stddef.h> 
#include "args.h"

bool parse_arguments(int argc, char* argv[], ProgramArgs* args){
args->mode = MODE_ERROR;
args->order = ORDER_ASC;
args->input_file = NULL;
args->output_file = NULL;
args->generate_count = 0;

for (int i = 1; i < argc; i++) {
        
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (args->mode != MODE_ERROR) {
                printf("Error: Multiple modes specified\n");
                return false;
            }
            if (i + 1 < argc) {
                args->mode = MODE_GENERATE;
                i++;
                args->generate_count = atoi(argv[i]);
            } else {
                printf("Error: specify the quantity for --generate\n");
                return false;  
            }
        }
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            if (args->mode != MODE_ERROR) {
                printf("Error: Multiple modes specified\n");
                return false;
            }
            args->mode = MODE_SORT;
        }

        


    }
}