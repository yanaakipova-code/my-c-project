#include "csv_reader.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#define FIRST_SIZE 64
#define ORIGINAL_SIZE 0
#define FALSE_LETTER 6

static bool parse_bool(const char *str){
    if (strcmp(str, "true") == 0 || strcmp(str, "yes") ==0 || strcmp(str, "1") == 0){
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
     while(ch = fgetc(file) != "\n" && ch != EOF){
        if (length + 1 >= capacity){
            capacity *= 2;
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
    char* header = read_line(file);
    if (header == 0){
        fclose(file);
        vector_destroy(buildings);
        printf("Error: File '%s' is empty\n", filename);
        return NULL;
    }
    free(header); 
    char *line;
    while ((line = read_line(file)) != NULL){
        apartment_building building;
        char elevator_str[FALSE_LETTER];
        char garbage_chute_str[FALSE_LETTER];
        int parsed = sscanf(line, "%26[^,],%14[^,],%11[^,],%u,%9[^,],%9[^,],%hu,%hu,%f",
            building.developer,
            building.microdistrict,
            building.type,
            &building.year,
            elevator_str,
            garbage_chute_str,
            &building.count_apartments,
            &building.count_floors,
            &building.area_apartment
        );
        if (parsed == 9) {
            building.elevator = parse_bool(elevator_str);
            building.garbage_chute = parse_bool(garbage_chute_str);
            vector_push_back(buildings, &building);
        }
        else {
            printf("Error: couldn't read the line: %s\n", line);
        }
        free(line);
    }
    fclose(file);
    if (vector_size(buildings) == 0) {
        printf("Error: couldn't read file'%s'\n", filename);
        vector_destroy(buildings);
        return NULL;
    }
    printf("Successfully read %zu records from '%s'\n",vector_size(buildings), filename);
    return buildings;
}
void free_buildings_vector(vector* buildings) {
    if (buildings != NULL) {
        vector_destroy(buildings);
    }
}

