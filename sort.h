#pragma once
#include "vector.h"
#include "apartment_building.h"
#include "comparator.h"

typedef int (*Comparator)(const apartment_building*, const apartment_building*);
void selection_sort(vector* vec, Comparator comp);

int comparator_by_ascending(const apartment_building *a, const apartment_building *b);
int comporator_reduction(const apartment_building *a, const apartment_building *b);
