#include <stdbool.h>
#include <string.h> 
#include <stddef.h> 
#include <stdio.h>
#include <stdlib.h>
#include "args_parser.h"

#define PASS_ONE 6
#define PASS_TWO 5

static void print_help(const char* program_name){
    printf("Использование: %s [РЕЖИМ] [ЗНАЧЕНИЯ]", program_name);
    puts("Режимы(выберите один)");
    puts("  --generate N, -g N   Сгенерировать N случайных зданий\n");
    puts("  --sort, -s           Отсортировать здания\n");
    puts("  --print, -P          Напечатать здания в виде таблицы\n\n");
    
    puts("Опции:\n");
    puts("  --in ФАЙЛ, -i ФАЙЛ   Входной файл (stdin если не указан)\n");
    puts("  --out ФАЙЛ, -o ФАЙЛ  Выходной файл (stdout если не указан)\n");
    puts("  --type asc|desc, -t A|D  Порядок сортировки (по умолчанию asc)\n");
}


bool parse_arguments(int argc, char* argv[], ProgramArgs* args){
args->mode = MODE_ERROR;
args->order = ORDER_ASC;
args->sort_field = NULL;
args->input_file = NULL;
args->output_file = NULL;
args->generate_count = 0;

if (argc == 1){
    print_help(argv[0]);
    return false;
}

for (int i = 1; i < argc; i++) {
        const char* arg = argv[1];
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_GENERATE) {
                puts("Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_GENERATE;

            if (i + 1 < argc) {
                args->generate_count = atoi(argv[i++]);
                if (args->generate_count <= 0){
                    fprintf(stderr, "ошибка, число должно быть положительным");
                }
            } else {
                puts("Ошибка: укажите количество для --generate\n");
                return false;  
            }
        }
        else if (strcmp(argv[i], "--sort") == 0 || strcmp(argv[i], "-s") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_SORT) {
                puts("Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_SORT;
        }
        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_PRINT) {
                puts("Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_PRINT;
        }

        else if(strcmp(argv[i], "-o") == 0){
            if (i+1 < argc){
                args->output_file = argv[++i];
            }else {
                puts("Ошибка: -o требуется имя файла\n");
                return false;
            }
        }
        else if (strncmp(argv[i], "--out=", PASS_ONE) == 0){
            args->output_file = argv[i] + PASS_ONE;
        }


        else if (strcmp(argv[i], "-i") == 0){
            if (i+1 < argc){
                args->input_file=argv[++i];
            }
            else{
                puts("Ошибка: -i требуется имя файла\n");
                return false;
            }
        }
        else if(strncmp(argv[i], "--in=",PASS_TWO) == 0){
            args->input_file = argv[i] + PASS_TWO;
        }


        else if (strcmp(argv[i], "--type=asc") == 0 || strcmp(argv[i], "-t") == 0 \
                    && i + 1 < argc && strcmp(argv[i], "A") == 0 || strcmp(argv[i], "asc") == 0 ) {
            args->order = ORDER_ASC;
            if (strcmp(argv[i], "-t") == 0) i++;
        }
        else if (strcmp(arg, "--type=desc") == 0 || \
                    (strcmp(arg, "-t") == 0 && i + 1 < argc && 
                        (strcmp(argv[i+1], "D") == 0 || strcmp(argv[i+1], "desc") == 0))) {
            args->order = ORDER_DESC;
            if (strcmp(arg, "-t") == 0) i++;
        }
        else{
            fprint(stderr, "Ошибка: неизвестный аргумент");
        }

    if (args->mode == MODE_ERROR) {
        printf("Ошибка: Режим не выбран\n");
        return false;
    }
    
    return true;
}