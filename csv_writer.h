#pragma once
#include "vector.h"
#include <stdio.h> 

void save_buildings_to_csv(const vector* buildings, const char* filename);
void write_buildings_to_stream(const vector* buildings, FILE* stream);
void write_csv_header(FILE* stream);