#pragma once
#include <stddef.h>
#include <apartment_building.h>
typedef struct{
    size_t capacity;
    size_t size;
    apartment_building* data;
}vector;