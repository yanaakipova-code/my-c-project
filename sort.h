#pragma once
#include "vector.h"
#include "apartment_building.h"

typedef bool (*Comparator)(const apartment_building*, const apartment_building*);
void selection_sort(vector* vec, Comparator comp);