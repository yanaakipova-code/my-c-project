#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

vector* vector_create() {
    vector* temp_vector = (vector*)malloc(sizeof(vector));
    if (temp_vector == NULL) {
        puts("No memory allocated");
        return NULL;
    }
    size_t initial_capacity = 4;
    temp_vector->data = (apartment_building*)malloc(
        initial_capacity * sizeof(apartment_building)
    );
    if (temp_vector->data == NULL) {
        puts("no memory allocated");
        free(temp_vector);
        return NULL;
    }
    temp_vector->size = 0;
    temp_vector->capacity = initial_capacity;
    return temp_vector;
}
void vector_clear(vector* vec) {
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->capacity = 0;
}
void vector_destroy(vector* vec) {
    if (vec == NULL) return;
    vector_clear(vec);
    free(vec);    
}
size_t vector_size(const vector* vec) {
    if (vec == NULL) {
        return 0; 
    }
    return vec->size;   
}
apartment_building* vector_get(const vector* vec, size_t index){
    if (vec == NULL || index >= vec->size) {
        return NULL;
    }    
    return &vec->data[index];
}
apartment_building* vector_front(const vector* vec) {
    return vector_get(vec, 0);
}
apartment_building* vector_back(const vector* vec) {
    if (vec == NULL || vec->size == 0){
        return NULL;
    }
    return &vec->data[vec->size - 1];
} 

void vector_expansion(vector* vec) {
    if (vec == NULL) {
        return;
    }
    size_t new_capacity;
    if (vec->capacity == 0) {
        new_capacity = 4;        
    } else {
        new_capacity = vec->capacity * 2;  
    }
    apartment_building* new_data = (apartment_building*)realloc(
        vec->data, new_capacity * sizeof(apartment_building));
    if (new_data == NULL) {
        puts("Error: memory addition error\n");
        return;
    }
    vec->data = new_data;
    vec->capacity = new_capacity;
}