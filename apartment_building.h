#pragma once
#include <stdbool.h>

typedef struct{
    char developer[30];
    char microdistrict[50];
    char type[13];
    unsigned int year;
    bool elevator;
    bool garbage_chute;
    unsigned short int count_apartments;
    unsigned short int count_floors;
    float  area_apartment;
}apartment_building;
