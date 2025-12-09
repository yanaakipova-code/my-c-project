#include "csv_reader.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define FIRST_SIZE 64
#define ORIGINAL_SIZE 0
#define MAX_BOOL_STR 7

static bool parse_bool(const char *str){
    if (strcmp(str, "true") == 0 || strcmp(str, "yes") == 0 || strcmp(str, "1") == 0){
        return true;
    }
    else{
        return false;
    }
}

static char *read_line(FILE* file){
    size_t capacity = FIRST_SIZE;
    size_t length = ORIGINAL_SIZE;
    char* line = malloc(capacity * sizeof(char));
    if (line == NULL){
        fprintf(stderr, "Ошибка: Память не выделена\n");
        return NULL;
    }
    
    int ch;
    while((ch = fgetc(file)) != '\n' && ch != EOF){
        if (length + 1 >= capacity){
            capacity *= 2;
            char* new_line = realloc(line, capacity);
            if (new_line == NULL){
                free(line);
                fprintf(stderr, "Ошибка: память не увеличилось\n");
                return NULL;
            }
            line = new_line;
        }
        line[length++] = (char)ch;
    }
    
    if (length == 0 && ch == EOF) {
        free(line);
        return NULL;
    }
    
    line[length] = '\0';
    return line;
}

vector* read_buildings_from_csv(const char * filename){
    if (filename == NULL) {
        return read_buildings_from_stream(stdin);
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL){
        fprintf(stderr, "Ошибка: файл '%s' не удалось открыть\n", filename);
        return NULL;
    }
    
    vector* buildings = vector_create();
    if (buildings == NULL){
        fclose(file);
        fprintf(stderr, "Ошибка: не удалось создать контейнер\n");
        return NULL;
    }
    
    char* header = read_line(file);
    if (header == NULL){
        fclose(file);
        vector_destroy(buildings);
        fprintf(stderr, "Ошибка: файл '%s' пуст\n", filename);
        return NULL;
    }
    free(header); 
    
    char *line;
    while ((line = read_line(file)) != NULL){
        apartment_building building;
        char elevator_str[MAX_BOOL_STR];
        char garbage_chute_str[MAX_BOOL_STR];
        
        int parsed = sscanf(line, "%26[^,],%14[^,],%11[^,],%u,%6[^,],%6[^,],%hu,%hu,%f",
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
            fprintf(stderr, "Ошибка: не удалось прочитать строку: %s\n", line);
        }
        free(line);
    }
    
    fclose(file);
    
    if (vector_size(buildings) == 0) {
        fprintf(stderr, "Ошибка: не удалось прочитать данные из файла '%s'\n", filename);
        vector_destroy(buildings);
        return NULL;
    }
    
    printf("Успешно прочитаны записи %zu из файла '%s'\n", vector_size(buildings), filename);
    return buildings;
}

vector* read_buildings_from_stream(FILE* stream) {
    if (stream == NULL) {
        fprintf(stderr, "Ошибка: поток недействителен\n");
        return NULL;
    }
    
    vector* buildings = vector_create();
    if (buildings == NULL) {
        fprintf(stderr, "Ошибка: не удалось создать контейнер\n");
        return NULL;
    }
    
    char* header = read_line(stream);
    if (header != NULL) {
        free(header);
    }
    
    char* line;
    while ((line = read_line(stream)) != NULL) {
        apartment_building building;
        char elevator_str[MAX_BOOL_STR];
        char garbage_chute_str[MAX_BOOL_STR];
        
        int parsed = sscanf(line, "%26[^,],%14[^,],%11[^,],%u,%6[^,],%6[^,],%hu,%hu,%f",
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
        } else {
            fprintf(stderr, "Ошибка: не удалось прочитать строку из потока: %s\n", line);
        }
        free(line);
    }
    
    if (vector_size(buildings) == 0) {
        fprintf(stderr, "Предупреждение: не удалось прочитать данные из потока\n");
        vector_destroy(buildings);
        return NULL;
    }
    
    printf("Успешно прочитаны записи %zu из потока\n", vector_size(buildings));
    return buildings;
}

void free_buildings_vector(vector* buildings) {
    if (buildings != NULL) {
        vector_destroy(buildings);
    }
}