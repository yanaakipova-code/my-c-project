#include <comparator.h>

int comparator_by_ascending(const apartment_building *a, const apartment_building *b) {
    if (a->year != b->year) {
        if (a->year < b->year) {
            return -1;
        } else {
            return 1;
        }
    }
    
    if (a->count_floors != b->count_floors) {
        if (a->count_floors < b->count_floors) {
            return -1;
        } else {
            return 1;
        }
    }
    
    if (a->count_apartments != b->count_apartments) {
        if (a->count_apartments < b->count_apartments) {
            return -1;
        } else {
            return 1;
        }
    }
    
    if (a->area_apartment != b->area_apartment) {
        if (a->area_apartment < b->area_apartment) {
            return -1;
        } else {
            return 1;
        }
    }
    
    int cmp = strcmp(a->type, b->type);
    if (cmp < 0) {
        return -1;
    } else if (cmp > 0) {
        return 1;
    }

    int cmp_mic = strcmp(a->microdistrict, b->microdistrict);
    if (cmp_mic < 0) {
        return -1;
    } else if (cmp_mic > 0) {
        return 1;
    }
    
    int cmp_dev = strcmp(a->developer, b->developer);
    if (cmp_dev < 0) {
        return -1;
    } else if (cmp_dev > 0) {
        return 1;
    }
    
    if (a->elevator != b->elevator) {
        if (a->elevator < b->elevator) {
            return -1;
        } else {
            return 1;
        }
    }
    
    if (a->garbage_chute != b->garbage_chute) {
        if (a->garbage_chute < b->garbage_chute) {
            return -1;
        } else {
            return 1;
        }
    }

    return 0;
}

int comporator_reduction(const apartment_building *a,const apartment_building *b){
    int res = comparator_by_ascending(a,b);
    return -res;
}