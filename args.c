#include <stdbool.h>
#include <string.h> 
#include <stddef.h> 
#include "args.h"

#define PASS_ONE 6
#define PASS_TWO 5

bool parse_arguments(int argc, char* argv[], ProgramArgs* args){
args->mode = MODE_ERROR;
args->order = ORDER_ASC;
args->sort_field = NULL;
args->input_file = NULL;
args->output_file = NULL;
args->generate_count = 0;

for (int i = 1; i < argc; i++) {
        
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (args->mode != MODE_ERROR) {
                puts("Error: Multiple modes specified\n");
                return false;
            }
            if (i + 1 < argc) {
                args->mode = MODE_GENERATE;
                i++;
                args->generate_count = atoi(argv[i]);
            } else {
                puts("Error: specify the quantity for --generate\n");
                return false;  
            }
        }
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            if (args->mode != MODE_ERROR) {
                puts("Error: Multiple modes specified\n");
                return false;
            }
            args->mode = MODE_SORT;
        }


        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            if (args->mode != MODE_ERROR) {
                puts("Error: Multiple modes specified\n");
                return false;
            }
            args->mode = MODE_PRINT;
        }

        else if(strcmp(argv[i], "-o") == 0){
            if (i+1 < argc){
                args->output_file = argv[++i];
            }else {
                puts("Error: -o requires filename\n");
                return false;
            }
        }
        else if (strncmp(argv[i], "--out=", PASS_ONE) == 0){
            args->output_file = argv[i] + PASS_ONE;
        }


        else if (strcmp(argv[i], "-i") == 0){
            if (i+1 < argc){
                args->input_file=argv[++i];
            }
            else{
                puts("Error: -i requires filename\n");
                return false;
            }
        }
        else if(strncmp(argv[i], "--in=",PASS_TWO) == 0){
            args->input_file = argv[i] + PASS_TWO;
        }


        else if (strcmp(argv[i], "--type=asc") == 0) {
            args->order = ORDER_ASC;
        }
        else if (strcmp(argv[i], "--type=desc") == 0) {
            args->order = ORDER_DESC;
        }
        else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "A") == 0) {
                    args->order = ORDER_ASC;
                    i++;
                }else if (strcmp(argv[i + 1], "D") == 0) {
                    args->order = ORDER_DESC;
                    i++;
                }else{
                    puts("Error: -t is entered with A (asc) or D (desc)\n");
                    return false;
                }
            }
            else{
                    puts("Error: -t is entered with A (asc) or D (desc)\n");
                    return false;
                }
        }
        else if (strncmp(argv[i], "--field=", 8) == 0) {
            args->sort_field = argv[i] + 8;
        }
        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            args->sort_field = argv[++i];
        }
        else {
            printf("Error: Unknown argument '%s'\n", argv[i]);
            return false;
        }
    }
    if (args->mode == MODE_ERROR) {
        printf("Error: No mode selected\n");
        return false;
    }
    
    return true;
}