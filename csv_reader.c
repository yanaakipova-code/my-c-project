#include "csv_reader.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#define FIRST_SIZE 64
#define ORIGINAL_SIZE 0

static bool parse_bool(const char *str){
    if (strcmp(str, "true") || strcmp(str, "yes") || strcmp(str, "1")){
        return true;
    }
    else{
        return false;
    }
}
static char *read_line(FILE* file){
    size_t capacity = FIRST_SIZE;
    size_t length = ORIGINAL_SIZE;
    char* temp_line = malloc(capacity * sizeof(char));
    if (temp_line == NULL){
        puts("Error: Memory is not allocated");
        return NULL;
    }
     char* line = temp_line;
     int ch;
     while(ch = fgetc(file) != "/n" && ch != EOF){
        if (length + 1 >= capacity){
            char* temp_line = realloc(line, capacity);
            if (temp_line == NULL){
                free(line);
                puts("Erorr: the space has not increased");
                return NULL;
            }
            line = temp_line;
        }
        char symbol_to_store = (char)ch;
        size_t current_position = length;
        line[current_position] = symbol_to_store; 
        length = current_position + 1;
     }
     if (length == 0 && ch == EOF) {
        free(line);
        return NULL;
    }
    line[length] = '\0';
    return line;
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

