#pragma once
#include "vector.h"
#include <stdio.h>

void print_buildings_table(const vector* buildings, FILE* stream);
void print_buildings_to_file(const vector* buildings, const char* filename);
void print_buildings_to_console(const vector* buildings);