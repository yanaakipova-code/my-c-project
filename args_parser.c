#include <stdbool.h>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include "args_parser.h"

#define PASS_ONE 6  // "--out=" имеет длину 6
#define PASS_TWO 5  // "--in=" имеет длину 5

static void print_help(const char* program_name){
    printf("Использование: %s [РЕЖИМ] [ОПЦИИ]\n\n", program_name);
    printf("Режимы (выберите один):\n");
    printf("  --generate N, -g N   Сгенерировать N случайных зданий\n");
    printf("  --sort, -s           Отсортировать здания\n");
    printf("  --print, -P          Напечатать здания в виде таблицы\n\n");
    
    printf("Опции:\n");
    printf("  --in ФАЙЛ, -i ФАЙЛ   Входной файл (stdin если не указан)\n");
    printf("  --out ФАЙЛ, -o ФАЙЛ  Выходной файл (stdout если не указан)\n");
    printf("  --type asc|desc, -t A|D  Порядок сортировки (по умолчанию asc)\n\n");
    
    printf("Форматы:\n");
    printf("  --in file.csv    или --in=file.csv    или -i file.csv\n");
    printf("  --out file.csv   или --out=file.csv   или -o file.csv\n");
    printf("  --type asc       или --type=asc       или -t A\n");
    printf("  --type desc      или --type=desc      или -t D\n");
}


bool parse_arguments(int argc, char* argv[], ProgramArgs* args){
    args->mode = MODE_ERROR;
    args->order = ORDER_ASC;
    args->input_file = NULL;
    args->output_file = NULL;
    args->generate_count = 0;

    if (argc == 1){
        print_help(argv[0]);
        return false;
    }

    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i]; 
        
        if (strcmp(arg, "--generate") == 0 || strcmp(arg, "-g") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_GENERATE) {
                fprintf(stderr, "Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_GENERATE;

            if (i + 1 < argc) {
                args->generate_count = atoi(argv[++i]);
                if (args->generate_count <= 0){
                    fprintf(stderr, "Ошибка: число должно быть положительным\n");
                    return false;
                }
            } else {
                fprintf(stderr, "Ошибка: укажите количество для --generate\n");
                return false;  
            }
        }
        else if (strcmp(arg, "--sort") == 0 || strcmp(arg, "-s") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_SORT) {
                fprintf(stderr, "Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_SORT;
        }
        else if (strcmp(arg, "--print") == 0 || strcmp(arg, "-P") == 0) {
            if (args->mode != MODE_ERROR && args->mode != MODE_PRINT) {
                fprintf(stderr, "Ошибка: задано несколько режимов\n");
                return false;
            }
            args->mode = MODE_PRINT;
        }
        else if (strcmp(arg, "--in") == 0) {
            if (i + 1 < argc) {
                args->input_file = argv[++i];
            } else {
                fprintf(stderr, "Ошибка: --in требует имя файла\n");
                return false;
            }
        }
        else if (strcmp(arg, "-i") == 0) {
            if (i + 1 < argc) {
                args->input_file = argv[++i];
            } else {
                fprintf(stderr, "Ошибка: -i требуется имя файла\n");
                return false;
            }
        }
        else if (strncmp(arg, "--in=", PASS_TWO) == 0) {
            args->input_file = (char*)(arg + PASS_TWO);
        }
        else if (strcmp(arg, "--out") == 0) {
            if (i + 1 < argc) {
                args->output_file = argv[++i];
            } else {
                fprintf(stderr, "Ошибка: --out требует имя файла\n");
                return false;
            }
        }
        else if (strcmp(arg, "-o") == 0) {
            if (i + 1 < argc) {
                args->output_file = argv[++i];
            } else {
                fprintf(stderr, "Ошибка: -o требуется имя файла\n");
                return false;
            }
        }
        else if (strncmp(arg, "--out=", PASS_ONE) == 0) {
            args->output_file = (char*)(arg + PASS_ONE);
        }
        else if (strcmp(arg, "--type") == 0) {
            if (i + 1 < argc) {
                i++;
                if (strcmp(argv[i], "asc") == 0) {
                    args->order = ORDER_ASC;
                } else if (strcmp(argv[i], "desc") == 0) {
                    args->order = ORDER_DESC;
                } else {
                    fprintf(stderr, "Ошибка: --type принимает asc или desc\n");
                    return false;
                }
            } else {
                fprintf(stderr, "Ошибка: --type требует значение\n");
                return false;
            }
        }
        else if (strcmp(arg, "--type=asc") == 0) {
            args->order = ORDER_ASC;
        }
        else if (strcmp(arg, "--type=desc") == 0) {
            args->order = ORDER_DESC;
        }
        else if (strcmp(arg, "-t") == 0) {
            if (i + 1 < argc) {
                i++;
                if (strcmp(argv[i], "A") == 0 || strcmp(argv[i], "asc") == 0) {
                    args->order = ORDER_ASC;
                } else if (strcmp(argv[i], "D") == 0 || strcmp(argv[i], "desc") == 0) {
                    args->order = ORDER_DESC;
                } else {
                    fprintf(stderr, "Ошибка: -t принимает A|asc или D|desc\n");
                    return false;
                }
            } else {
                fprintf(stderr, "Ошибка: -t требует значение\n");
                return false;
            }
        }
        else {
            fprintf(stderr, "Ошибка: неизвестный аргумент '%s'\n", arg);
            return false;
        }
    } 

    if (args->mode == MODE_ERROR) {
        fprintf(stderr, "Ошибка: режим не выбран\n");
        return false;
    }
    
    return true;
}