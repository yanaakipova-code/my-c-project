#include "csv_reader.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static bool parse_bool(const char *str){
    if (strcmp(str, "true") || strcmp(str, "yes") || strcmp(str, "1")){
        return true;
    }
}

vector* read_buildings_from_csv(const char * filename){
    FILE* file = foprn(filename, "r");

    if (filename == NULL){
        printf("Error: file: %s couldn't be opened", filename);
        return NULL;
    }

}

