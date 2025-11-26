#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

vector* vector_create() {
    vector* temp_vector = (vector*)malloc(sizeof(vector));
    if (temp_vector == NULL) {
        puts("no memory allocated");
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