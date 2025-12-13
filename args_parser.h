#pragma once
#include <stdbool.h> 
typedef enum {
    SORT_SELECTION,
    SORT_MERGE
} SortAlgorithm;
typedef enum{
    MODE_ERROR,
    MODE_GENERATE,
    MODE_SORT,
    MODE_PRINT
}ProgramMode;
typedef enum {
    ORDER_ASC,
    ORDER_DESC
} SortOrder;
typedef struct {
    ProgramMode mode;
    SortOrder order;
    SortAlgorithm sort_algorithm;
    char* sort_field; 
    char* input_file;
    char* output_file;
    int generate_count;
} ProgramArgs;
bool parse_arguments(int argc, char* argv[], ProgramArgs* args);