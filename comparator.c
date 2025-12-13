#include <comparator.h>

int comparator_by_ascending(const apartment_building *a, const apartment_building *b) {
    if (a->year != b->year) {
        return (a->year - b->year);
    }
    
    if (a->count_floors != b->count_floors) {
        return (a->count_floors - b->count_floors);
    }
    
    if (a->count_apartments != b->count_apartments) {
        return (a->count_apartments - b->count_apartments);
    }
    
    if (a->area_apartment != b->area_apartment) {
        return (a->area_apartment - b->area_apartment);
    }
    
    int cmp = strcmp(a->type, b->type);
    if (cmp != 0){
        return cmp;
    }

    int cmp_mic = strcmp(a->microdistrict, b->microdistrict);
    if (cmp_mic != 0) {
        return cmp_mic;
    }
    
    int cmp_dev = strcmp(a->developer, b->developer);
    if (cmp_dev != 0) {
        return cmp_dev;
    }
    
    if (a->elevator != b->elevator) {
        return (a->elevator - b->elevator);
    }
    
    if (a->garbage_chute != b->garbage_chute) {
        return (a->garbage_chute - b->garbage_chute);
    }

    return 0;
}

int comporator_reduction(const apartment_building *a,const apartment_building *b){
    int res = comparator_by_ascending(a,b);
    return -res;
}