#include "vector.h"
#include "apartment_building.h"
#include "comparator.h"
#include <stdlib.h>
#include <stdio.h>

/* слияние двух отсортированных частей*/
static void merge(vector* vec, size_t left, size_t mid, size_t right, 
    Comparator comp, apartment_building* temp) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;

    while (i <= mid && j <= right) {
        apartment_building* a = vector_get(vec, i);
        apartment_building* b = vector_get(vec, j);
        
        if (comp(a, b) <= 0) {
            temp[k] = *a;
            i++;
        } else {
            temp[k] = *b;
            j++;
        }
        k++;
    }
    
    while (i <= mid) {
        apartment_building* a = vector_get(vec, i);
        temp[k] = *a;
        i++;
        k++;
    }
    
    while (j <= right) {
        apartment_building* b = vector_get(vec, j);
        temp[k] = *b;
            j++;
            k++;
    }
    
    for (size_t idx = left; idx <= right; idx++) {
        apartment_building* dest = vector_get(vec, idx);
        *dest = temp[idx];
    }
}

/* рекурсия */
static void merge_sort_recursive(vector* vec, size_t left, size_t right, 
    Comparator comp, apartment_building* temp) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        
        merge_sort_recursive(vec, left, mid, comp, temp);
        merge_sort_recursive(vec, mid + 1, right, comp, temp);
        
        merge(vec, left, mid, right, comp, temp);
    }
}
/* выделяет временную память и запускает рекурсию */
void sort_merge(vector* vec, Comparator comp) {
    if (!vector_is_valid_and_not_empty(vec)) return;
    
    size_t n = vector_size(vec);
    
    apartment_building* temp = (apartment_building*)malloc(n * sizeof(apartment_building));
    if (temp == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для сортировки слиянием\n");
        return;
    }
    
    merge_sort_recursive(vec, 0, n - 1, comp, temp);

    free(temp);
}