#pragma once
#include "vector.h"
#include "apartment_building.h"
#include "comparator.h"

typedef enum {
    SORT_SELECTION,
    SORT_MERGE
} SortAlgorithm;

void selection_sort(vector* vec, Comparator comp);
void sort_merge(vector* vec, Comparator comp);

void sort_vector(vector* vec, Comparator comp, SortAlgorithm algorithm);


