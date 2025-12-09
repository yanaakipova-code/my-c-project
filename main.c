#include "args_parser.h"
#include "apartment_building.h"
#include "vector.h"
#include "csv_reader.h"
#include "csv_writer.h"
#include "sort.h"
#include "building_generator.h"
#include "table_printer.h"


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static Comparator get_comparator(SortOrder order) {
    if (order == ORDER_ASC) {
        return comparator_by_ascending;
    } else {
        return comporator_reduction;
    }
}

int main(int argc, char* argv[]) {

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    srand(time(NULL));
    
    ProgramArgs args;
    if (!parse_arguments(argc, argv, &args)) {
        return 1;
    }
    
    int result = 0;
    
    switch (args.mode) {
        case MODE_GENERATE: {
            printf("Генерация %d случайных зданий...\n", args.generate_count);
            
            vector* buildings = vector_create();
            if (!buildings) {
                fprintf(stderr, "Ошибка: не удалось создать контейнер\n");
                result = 1;
                break;
            }
    
            for (int i = 0; i < args.generate_count; i++) {
                apartment_building b = generate_random_building();
                vector_push_back(buildings, &b);
            }
            if (args.output_file) {
                save_buildings_to_csv(buildings, args.output_file);
                printf("Данные сохранены в файл: %s\n", args.output_file);
            } else {
                write_buildings_to_stream(buildings, stdout);
            }
            
            vector_destroy(buildings);
            break;
        }
            
        case MODE_SORT: {
            vector* buildings = NULL;
            
            if (args.input_file) {
                printf("Чтение данных из файла: %s\n", args.input_file);
                buildings = read_buildings_from_csv(args.input_file);
            } else {
                printf("Чтение данных из стандартного ввода...\n");
                buildings = read_buildings_from_stream(stdin);
            }
            
            if (!buildings || vector_size(buildings) == 0) {
                fprintf(stderr, "Ошибка: нет данных для сортировки\n");
                result = 1;
                break;
            }
            
            printf("Прочитано %zu зданий\n", vector_size(buildings));

            Comparator comp = get_comparator(args.order);
            if (args.order == ORDER_ASC) {
                puts("Сортировка в порядке возрастания...\n");
            } else {
                puts("Сортировка в порядке убывания...\n");
            }   
            selection_sort(buildings, comp);
            
            if (args.output_file) {
                save_buildings_to_csv(buildings, args.output_file);
                printf("Отсортированные данные сохранены в файл: %s\n", args.output_file);
            } else {
                write_buildings_to_stream(buildings, stdout);
            }
            
            vector_destroy(buildings);
            break;
        }
            
        case MODE_PRINT: {
            vector* buildings = NULL;
            if (args.input_file) {
                printf("Чтение данных из файла: %s\n", args.input_file);
                buildings = read_buildings_from_csv(args.input_file);
            } else {
                puts("Введите имя файла с данными: ");
                char filename[256];
                if (!fgets(filename, sizeof(filename), stdin)) {
                    fprintf(stderr, "Ошибка: не удалось прочитать имя файла\n");
                    result = 1;
                    break;
                }
                filename[strcspn(filename, "\n")] = '\0';
                
                if (strlen(filename) == 0) {
                    fprintf(stderr, "Ошибка: имя файла не может быть пустым\n");
                    result = 1;
                    break;
                }
                
                buildings = read_buildings_from_csv(filename);
            }
            
            if (!buildings || vector_size(buildings) == 0) {
                fprintf(stderr, "Ошибка: нет данных для печати\n");
                result = 1;
                break;
            }
            
            printf("Прочитано %zu зданий\n", vector_size(buildings));
            if (args.output_file) {
                printf("Печать таблицы в файл: %s\n", args.output_file);
                print_buildings_to_file(buildings, args.output_file);
            } else {
                print_buildings_to_console(buildings);
            }
            
            vector_destroy(buildings);
            break;
        }
            
        default:
            fprintf(stderr, "Ошибка: неизвестный режим работы\n");
            result = 1;
            break;
    }
    
    return result;
}