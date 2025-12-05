#include "args.h"
#include "apartment_building.h"
#include "vector.h"
#include "csv_reader.h"
#include "csv_writer.h"
#include "sort.h"
#include "building_generator.h"
#include "table_printer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Comparator get_comparator_by_field(SortOrder order, const char* field_name){
    
    if (field_name == NULL){
        if (order == ORDER_ASC){
            return compare_by_year;
        }else{
            return compare_by_year_desc;
        }
    }

     if (strcmp(field_name, "developer") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_developer;
        } else {
            return compare_by_developer_desc;
        }
    }

    if (strcmp(field_name, "microdistrict") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_microdistrict;
        } else {
            return compare_by_microdistrict_desc;
        }
    }

    if (strcmp(field_name, "year") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_year;
        } else {
            return compare_by_year_desc;
        }
    }

    if (strcmp(field_name, "apartments") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_apartments;
        } else {
            return compare_by_apartments_desc;
        }
    }

    if (strcmp(field_name, "floors") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_floors;
        } else {
            return compare_by_floors_desc;
        }
    }

    if (strcmp(field_name, "area") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_area;
        } else {
            return compare_by_area_desc;
        }
    }

    if (strcmp(field_name, "type") == 0) {
        if (order == ORDER_ASC) {
            return compare_by_type;
        } else {
            return compare_by_type_desc;
        }
    }
}


static int data_generation(const ProgramArgs* args){
    if (args->generate_count < 0) {
        return 1;
    }

    vector* buildings = vector_create();
    if (buildings == NULL) {
        return 1;
    }

    for (int i = 0; i < args->generate_count; i++) {
        apartment_building building = generate_random_building();
        vector_push_back(buildings, &building);
    }

    if (args->output_file) {
        if (write_buildings_to_csv(buildings, args->output_file) == NULL) {
            fprintf(stderr, "Ошибка: не удалось записать данные в файл '%s'\n", args->output_file);
            vector_destroy(buildings);
            return 1;
        }
        printf("Данные успешно сохранены в файл: %s\n", args->output_file);
    } else {
        puts("Сгенерированные данные (CSV формат):\n");
        write_buildings_to_csv_stream(buildings, stdout);
    }
    vector_destroy(buildings);

    return 1;
}