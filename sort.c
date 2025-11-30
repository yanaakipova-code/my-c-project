#include "sort.h"
#include <string.h>
void selection_sort(vector* vec, Comparator comp) {
    if (!vector_is_valid_and_not_empty(vec)) {
        return;
    }

    size_t n = vector_size(vec);

    for (size_t i = 0; i < n - 1; i++){
        size_t min_index = i;

        for (size_t j = i + 1; j < n; j++) {
            apartment_building* current = vector_get(vec, j);
            apartment_building* min = vector_get(vec, min_index);
    
            if (comp(current, min)) {
                min_index = j;
            }
        }
        if (min_index != i) {
            apartment_building temp = *vector_get(vec, i);
            *vector_get(vec, i) = *vector_get(vec, min_index);
            *vector_get(vec, min_index) = temp;          
        }
    }

}