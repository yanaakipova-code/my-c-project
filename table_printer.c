#include "table_printer.h" 
#include "apartment_building.h"
#include <stdio.h>

static void print_horizontal_line(FILE* stream, 
                                 int col_dev, int col_micro, int col_type,
                                 int col_year, int col_elev, int col_garb,
                                 int col_apt, int col_floors, int col_area) {
    fprintf(stream, "+");
    for (int i = 0; i < col_dev + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_micro + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_type + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_year + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_elev + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_garb + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_apt + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_floors + 2; i++) fputc('-', stream);
    fprintf(stream, "+");
    for (int i = 0; i < col_area + 2; i++) fputc('-', stream);
    fprintf(stream, "+\n");
}

void print_buildings_table(const vector* buildings, FILE* stream) {
    if (buildings == NULL || stream == NULL) {
        return;
    }

    size_t count = vector_size(buildings);

    const int col_dev = 20;
    const int col_micro = 15;
    const int col_type = 12;
    const int col_year = 6;
    const int col_elev = 8;
    const int col_garb = 16;
    const int col_apt = 12;
    const int col_floors = 10;
    const int col_area = 15;

    print_horizontal_line(stream, col_dev, col_micro, col_type, col_year,
        col_elev, col_garb, col_apt, col_floors, col_area);

    fprintf(stream, "| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
            col_dev, "Developer",
            col_micro, "Microdistrict",
            col_type, "Type",
            col_year, "Year",
            col_elev, "Elevator",
            col_garb, "Garbage Chute",
            col_apt, "Apartments",
            col_floors, "Floors",
            col_area, "Area (m²)");
    print_horizontal_line(stream, col_dev, col_micro, col_type, col_year,
                         col_elev, col_garb, col_apt, col_floors, col_area);

    for (size_t i = 0; i < count; i++) {
        const apartment_building* b = vector_get(buildings, i);
        if (b) {
            const char* elevator_str;
            if (b->elevator) {
                elevator_str = "YES";
            } else {
                elevator_str = "NO";
            }

            const char* garbage_str;  
            if (b->garbage_chute) {
                garbage_str = "YES";
            } else {
                garbage_str = "NO";
            }

            fprintf(stream, "| %-*s | %-*s | %-*s | %-*u | %-*s | %-*s | %-*hu | %-*hu | %-*.2f |\n",
                    col_dev, b->developer,
                    col_micro, b->microdistrict,
                    col_type, b->type,
                    col_year, b->year,
                    col_elev, elevator_str, 
                    col_garb, garbage_str,
                    col_apt, b->count_apartments,
                    col_floors, b->count_floors,
                    col_area, b->area_apartment);
        }
    }

    if (count > 0) {
        print_horizontal_line(stream, col_dev, col_micro, col_type, col_year,
            col_elev, col_garb, col_apt, col_floors, col_area);
    }
}
    
void print_buildings_to_file(const vector* buildings, const char* filename) {
    if (buildings == NULL || filename == NULL) {
        fprintf(stderr, "Ошибка: Неверные параметры\n");
        return;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Ошибка: He удается открыть файл %s для записи\n", filename);
        return;
    }

    print_buildings_table(buildings, file);
    fclose(file);
}

void print_buildings_to_console(const vector* buildings) {
    if (buildings == NULL) {
        fprintf(stderr, "Ошибка: Неверный параметр\n");
        return;
    }

    print_buildings_table(buildings, stdout);
}