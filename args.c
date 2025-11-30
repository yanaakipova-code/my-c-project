#include "args.h"
parse_arguments(int argc, char* argv[], ProgramArgs* args){
args->mode = MODE_ERROR;
args->order = ORDER_ASC;
args->input_file = NULL;
args->output_file = NULL;
args->generate_count = 0;
}