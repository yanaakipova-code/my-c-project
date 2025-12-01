#include "csv_reader.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

static bool parse_bool(const char *str){
    if (strcmp(str, "true") || strcmp(str, "yes") || strcmp(str, "1")){
        return true;
    }
    else{
        return false;
    }
}

vector* read_buildings_from_csv(const char * filename){
    FILE* file = fopen(filename, "r");

    if (file == NULL){
        printf("Error: file: %s couldn't be opened", filename);
        return NULL;
    }
    vector* buildings = vector_create();
    if (buildings == NULL){
        fclose(file);
        puts("Error: couldn't write file");
        return NULL;
    }
}

