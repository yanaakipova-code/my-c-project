#pragma once
#include "vector.h"

vector* read_buildings_from_csv(const char* filename);

void free_buildings_vector(vector* buildings);