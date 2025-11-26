#pragma once
#include <stdbool.h>
/*структура*/
typedef struct{
    char developer[27];
    char microdistrict[4];
    char type[12];
    unsigned int year;
    bool elevator;
    bool garbage_chute;
    unsigned short int count_apartments;
    unsigned short int count_floors;
    float  area_apartment;
}apartment_building;
