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


static int data_sort(const ProgramArgs* args){
    if (args->input_file == NULL) {
        fprintf(stderr, "Error:\n");
        return 1;
    }

    vector* buildings = read_buildings_from_csv(args->input_file);
    if (buildings == NULL) {
        fprintf(stderr, "Error: couldn't read data from the file\n");
        return 1;
    }

    size_t count = vector_size(buildings);
    printf("Read %zu bildings\n", count);

    if (count == 0) {
        fprintf(stderr, "Error: the file does not contain data\n");
        vector_destroy(buildings);
        return 1;
    }
    Comparator comparator = get_comparator_by_field(args->order, args->sort_field);
    selection_sort(buildings, comparator);

    if (args->output_file) {
        if (write_buildings_to_csv(buildings, args->output_file) == NULL) {
            fprintf(stderr, "Error: Failed to write sorted data to the fileл '%s'\n", args->output_file);
            vector_destroy(buildings);
            return 1;
        }
        printf("The sorted data is saved to a file: %s\n", args->output_file);
    } else {
        puts("Sorted data (CSV format):\n");
        write_buildings_to_csv_stream(buildings, stdout);
    }
    vector_destroy(buildings);
    return 1;
}


static int dprint_data(const ProgramArgs* args) {
    vector* buildings = read_buildings_from_csv(args->input_file);
    if (args->input_file == NULL) {
        fprintf(stderr, "Error: an input file is required to display the table\n");
        return 1;
    }

    size_t count = vector_size(buildings);
    printf("Read it %zu buildings\n", count);

    if (count == 0) {
        fprintf(stderr, "Error: the file does not contain data\n");
        vector_destroy(buildings);
        return 1;
    }

    if (args->output_file) {
        print_buildings_to_file(buildings, args->output_file);
    } else {
        print_buildings_to_console(buildings);
    }
    vector_destroy(buildings);
    return 1;
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    ProgramArgs args;
    if (!parse_arguments(argc, argv, &args)) {
        print_help(argv[0]);
        fprintf(stderr, "Error: incorrect command line arguments\n");
        return 1;
    }
    switch (args.mode) {
    case MODE_GENERATE:
        return data_generation(&args);
    case MODE_SORT:
        return data_sort(&args);
    case MODE_PRINT:
        return dprint_data(&args);
    default:
        return 1;
        fprintf(stderr, "Error: The program is broken\n");
    }
}
