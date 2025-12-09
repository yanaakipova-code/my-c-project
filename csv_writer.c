#include "csv_writer.h"
#include "apartment_building.h"
#include <stdio.h>

static const char *bool_to_str(bool value){
    if (value == true) {
        return "true";
    } else {
        return "false";
    }
}
static void write_building_csv(const apartment_building* building, FILE* stream) {
    if (building == NULL || stream == NULL){
        return ;
    }
    fprintf(stream, "%s,%s,%s,%u,%s,%s,%hu,%hu,%.1f\n",
            building->developer,
            building->microdistrict,
            building->type,
            building->year,
            bool_to_str(building->elevator),
            bool_to_str(building->garbage_chute),
            building->count_apartments,
            building->count_floors,
            building->area_apartment);
}
void write_buildings_to_stream(const vector* buildings, FILE* stream){
    if (buildings == NULL || stream == NULL){
        return ;
    }
    fprintf(stream, "\n");
    size_t count = vector_size(buildings);
    for(size_t i = 0; i < count; i++){
        apartment_building* building = vector_get(buildings, i);
        write_building_csv(building, stream);
    }
    fflush(stream);
}

void save_buildings_to_csv(const vector* buildings, const char* filename){
    if (buildings == NULL || filename == NULL){
        puts("Ошибка: Данные не могут быть записаны\n");
        return;
    }
    FILE* file = fopen(filename, "w");
     if (file == NULL) {
        puts("Ошибка: Не удалось открыть файл");
        return;
    }
    write_buildings_to_stream(buildings, file);
    fclose(file);

    printf("Данные были успешно записаны в'%s'\n",filename);
}

