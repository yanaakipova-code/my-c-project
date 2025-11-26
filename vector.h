#pragma once
#include <stddef.h>
#include <apartment_building.h>
typedef struct{
    size_t size;
    size_t capacity;
    apartment_building* data;
}vector;