#pragma once
#include "vector.h"
#include <stdio.h>

vector* read_buildings_from_csv(const char* filename);
vector* read_buildings_from_stream(FILE* stream);
void free_buildings_vector(vector* buildings);