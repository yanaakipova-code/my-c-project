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
#include <time.h>

static Comparator get_comparator_by_field(SortOrder order, const char* field_name){
    
    if (field_name != NULL) {
        fprintf(stderr, "Warning: Sorting by field '%s' is not supported. Using universal comparator\n");
    }
    if (order == ORDER_ASC) {
        return comparator_by_ascending;
    } else {
        return comporator_reduction;
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
        save_buildings_to_csv(buildings, args->output_file);
        printf("The data has been successfully saved to a file: %s\n", args->output_file);
    } else {
        puts("Generated data (CSV format):\n");
        write_buildings_to_stream(buildings, stdout);
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
        save_buildings_to_csv(buildings, args->output_file);
        printf("The sorted data is saved to a file: %s\n", args->output_file);
    } else {
        puts("Sorted data (CSV format):\n");
        write_buildings_to_stream(buildings, stdout);
    }
    vector_destroy(buildings);
    return 1;
}


static int print_data(const ProgramArgs* args) {
    if (args->input_file == NULL) {
        fprintf(stderr, "Error: there is no input file\n");
        return 1;
    }
    vector* buildings = read_buildings_from_csv(args->input_file);
    if (buildings == NULL) {
        fprintf(stderr, "Error: the data has not been read '%s'\n", args->input_file);
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
        fprintf(stderr, "Error: incorrect command line arguments\n");
        return 1;
    }
    switch (args.mode) {
    case MODE_GENERATE:
        return data_generation(&args);
    case MODE_SORT:
        return data_sort(&args);
    case MODE_PRINT:
        return print_data(&args);
    default:
        return 1;
        fprintf(stderr, "Error: The program is broken\n");
    }
}
