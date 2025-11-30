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
bool compare_by_year(const apartment_building* a, const apartment_building* b) {
    return a->year < b->year;
}

bool compare_by_year_desc(const apartment_building* a, const apartment_building* b) {
    return a->year > b->year;
}

bool compare_by_apartments(const apartment_building* a, const apartment_building* b) {
    return a->count_apartments < b->count_apartments;
}

bool compare_by_apartments_desc(const apartment_building* a, const apartment_building* b) {
    return a->count_apartments > b->count_apartments;
}

bool compare_by_floors(const apartment_building* a, const apartment_building* b) {
    return a->count_floors < b->count_floors;
}

bool compare_by_floors_desc(const apartment_building* a, const apartment_building* b) {
    return a->count_floors > b->count_floors;
}

bool compare_by_area(const apartment_building* a, const apartment_building* b) {
    return a->area_apartment < b->area_apartment;
}

bool compare_by_area_desc(const apartment_building* a, const apartment_building* b) {
    return a->area_apartment > b->area_apartment;
}

bool compare_by_developer(const apartment_building* a, const apartment_building* b) {
    return strcmp(a->developer, b->developer) < 0;
}

bool compare_by_developer_desc(const apartment_building* a, const apartment_building* b) {
    return strcmp(a->developer, b->developer) > 0;
}

bool compare_by_microdistrict(const apartment_building* a, const apartment_building* b) {
    return strcmp(a->microdistrict, b->microdistrict) < 0;
}

bool compare_by_microdistrict_desc(const apartment_building* a, const apartment_building* b) {
    return strcmp(a->microdistrict, b->microdistrict) > 0;
}