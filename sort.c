#include "sort.h"
#include <string.h>

int comparator_by_ascending(const apartment_building *a, const apartment_building *b){
    if (a->year != b->year)
    if(a->year < b->year) return -1;
    if(a->year > b->year)  return 1;

    if (a->count_floors < b->count_floors) return -1;
    if (a->count_floors > b->count_floors) return 1;

    if (a->count_apartments < b->count_apartments) return -1;
    if (a->count_apartments > b->count_apartments) return 1;

    if (a->area_apartment < b->area_apartment) return -1;
    if (a->area_apartment > b->area_apartment) return 1;

    int cmp = strcmp(a->microdistrict, b->microdistrict);
    if (cmp < 0) return -1;
    if (cmp > 0) return 1;

    int cmp = strcmp(a->type, b->type);
    if (cmp < 0) return -1;
    if (cmp > 0) return 1;

    if (a->elevator < b->elevator) return -1;    
    if (a->elevator > b->elevator) return 1;

    int cmp = strcmp(a->developer, b->developer);
    if (cmp < 0) return -1;
    if (cmp > 0) return 1;

    if (a->garbage_chute < b->garbage_chute) return -1;
    if (a->garbage_chute > b->garbage_chute) return 1;

        return 0;
}
int comporator_reduction(apartment_building *a, apartment_building *b){
    int res = comparator_by_ascending(a,b);
    return -res;
}

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
    
            if (comp(current, min) < 0) {
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
