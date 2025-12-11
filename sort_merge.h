#include "vector.h"
#include "apartment_building.h"
#include "comparator.h"

void sort_merge(vector* vec, Comparator comp);
static void merge_sort_recursive(vector* vec, size_t left, size_t right, 
    Comparator comp, apartment_building* temp);
static void merge(vector* vec, size_t left, size_t mid, size_t right, 
    Comparator comp, apartment_building* temp);