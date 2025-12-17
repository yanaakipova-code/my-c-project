#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

bool vector_is_valid(const vector* vec) {
    if (vec == NULL) {
        return false;
    }
    if (vec->data == NULL) {
        return false;
    }
    return true;
}
bool vector_is_valid_and_not_empty(const vector* vec) {
    if (!vector_is_valid(vec)) {
        return false;
    }
    if (vec->size == 0) {
        return false;
    }
    return true;
}
vector* vector_create() {
    vector* temp_vector = (vector*)malloc(sizeof(vector));
    if (temp_vector == NULL) {
        puts("Память не выделена ");
        return NULL;
    }
    size_t initial_capacity = 4;
    temp_vector->data = (apartment_building*)malloc(
        initial_capacity * sizeof(apartment_building)
    );
    if (temp_vector->data == NULL) {
        puts("Память не выделена");
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
    if (!vector_is_valid(vec)){
        return 0;
    }
    return vec->size;   
}
apartment_building* vector_get(const vector* vec, size_t index){
    if (!vector_is_valid(vec) || index >= vec->size){
        return NULL;
    }    
    return &vec->data[index];
}
apartment_building* vector_front(const vector* vec) {
     if (!vector_is_valid_and_not_empty(vec)){
        return NULL;
    }
    return vector_get(vec, 0);
}
apartment_building* vector_back(const vector* vec) {
    if  (!vector_is_valid_and_not_empty(vec)){
        return NULL;
    }
    return &vec->data[vec->size - 1];
} 

void vector_expansion(vector* vec) {
    if (!vector_is_valid(vec)) {
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
        puts("Ошибка: память не добавлена\n");
        return;
    }
    vec->data = new_data;
    vec->capacity = new_capacity;
}

void vector_push_back(vector* vec, const apartment_building* value){
    if (!vector_is_valid(vec) || value == NULL) {
        return;
    }
    if (vec->size >= vec->capacity) {
        vector_expansion(vec);
    }
    size_t temporary = vec->size;
    vec->data[temporary] = *value;
    vec->size = temporary + 1;
}

void vector_push_front(vector* vec, const apartment_building* value){
    if (!vector_is_valid(vec) || value == NULL) {
        return;
    }
    for (size_t i = vec->size; i > 0; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[0] = *value;
    vec->size++;
}

void vector_insertion(vector* vec, size_t index, const apartment_building* value){
    if (!vector_is_valid(vec) || value == NULL || index > vec->size){
        return;
    }
    if (vec->size >= vec->capacity) {
        vector_expansion(vec);
    }
    for (size_t i = vec->size; i > index; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[index] = *value;
    vec->size++;
}

apartment_building* vector_next(const vector* vec,  const apartment_building* value){
    if (!vector_is_valid(vec) || value == NULL) {
        return NULL;
    }
    size_t index= value - vec->data;
    if (value < vec->data || value >= vec->data + vec->size){
        return NULL;
    }
    if (index + 1 < vec->size) {
        return &vec->data[index + 1];
    }else{
        return NULL;
    }
}

apartment_building* vector_previous(const vector* vec, const apartment_building* value){
    if (!vector_is_valid(vec) || value == NULL ){
        return NULL;
    }
    size_t index = value - vec->data;
    if (index >= vec->size) {
        return NULL;
    }
    if (index > 0) {
        return &vec->data[index - 1];
    } else {
        return NULL;
    }
}

bool vector_removal_back(vector* vec){
    if (!vector_is_valid_and_not_empty(vec)){
        return false;
    }
    vec->size--;
    return true;
}

bool vector_removal_front(vector* vec) {
    if (!vector_is_valid_and_not_empty(vec)){
        return false;
    }
    for (size_t i = 1; i < vec->size; i++){
        vec->data[i-1] = vec->data[i];
    }
    vec->size--;
    return true;
}

bool vector_erase(vector* vec, size_t index) {
    if (!vec || index >= vec->size){
        return false;
    }
    for (size_t i = index + 1; i < vec->size; i++){
        vec->data[i-1] = vec->data[i];
    }
    vec->size--;
    return true;
}

bool vector_swap(vector* vec, size_t i, size_t j){
    if (!vec || i >= vec->size || j >= vec->size){
        return false;
    }
    if (i == j) return true;
    apartment_building temp = vec->data[i];
    vec->data[i] = vec->data[j];
    vec->data[j] = temp;
    return true;
}

