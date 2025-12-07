#pragma once
#include <stddef.h>
#include "apartment_building.h"
typedef struct{
    size_t capacity;
    size_t size;
    apartment_building* data;
}vector;
 
bool vector_is_valid(const vector* vec);
bool vector_is_valid_and_not_empty(const vector* vec);

vector* vector_create();
void vector_clear(vector* vec);
void vector_destroy(vector* vec);
size_t vector_size(const vector* vec);

apartment_building* vector_get(const vector* vec, size_t index);
apartment_building* vector_front(const vector* vec);
apartment_building* vector_back(const vector* vec);

void vector_expansion(vector* vec);

void vector_push_back(vector* vec, const apartment_building* value);
void vector_push_front(vector* vec, const apartment_building* value);
void vector_insertion(vector* vec, size_t index, const apartment_building* value);

apartment_building* vector_next(const vector* vec, const apartment_building* value);
apartment_building* vector_previous(const vector* vec, const apartment_building* value);

bool vector_removal_back(vector* vec);
bool vector_removal_front(vector * vec);
bool vector_erase(vector* vec, size_t index);
bool vector_swap(vector* vec, size_t i, size_t j);