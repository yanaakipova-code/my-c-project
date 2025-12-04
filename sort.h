#pragma once
#include "vector.h"
#include "apartment_building.h"

typedef bool (*Comparator)(const apartment_building*, const apartment_building*);
void selection_sort(vector* vec, Comparator comp);

bool compare_by_year(const apartment_building* a, const apartment_building* b);
bool compare_by_year_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_apartments(const apartment_building* a, const apartment_building* b);
bool compare_by_apartments_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_floors(const apartment_building* a, const apartment_building* b);
bool compare_by_floors_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_area(const apartment_building* a, const apartment_building* b);
bool compare_by_area_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_developer(const apartment_building* a, const apartment_building* b);
bool compare_by_developer_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_microdistrict(const apartment_building* a, const apartment_building* b);
bool compare_by_microdistrict_desc(const apartment_building* a, const apartment_building* b);
bool compare_by_type(const apartment_building* a, const apartment_building* b);
bool compare_by_type_desc(const apartment_building* a, const apartment_building* b);