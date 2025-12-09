#include "building_generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*площадь квартиры*/
#define MIN_AREA 30.0f 
#define MAX_AREA 200.0f
#define AREA_RANGE (unsigned int)((MAX_AREA - MIN_AREA) * 10)
/*вероятность*/
#define ODDS80 80
#define ODDS20 20
#define ODDS70 70
/*параметры генерации*/
#define DEVELOPER_MICRODISTRICT_COUNT 6
#define MICRODISTRICT_COUNT 7
#define BUILDING_TYPE_COUNT 3
#define MIN_YEAR 1970
#define YEAR_RANGE 25
#define MIN_FLOORS 1
#define MAX_FLOORS 28
#define MANDATORY_ELEVATOR_FLOORS 9
#define HIGH_FLOORS_THRESHOLD 5
#define MIN_APARTMENTS_PER_FLOOR 4
#define MAX_APARTMENTS_PER_FLOOR 12
#define OLD_YEAR_THRESHOLD 2000

static const char* developers[] = {"PIK", "Level", "Strizhi",
     "Simvol", "Pifagor", "Gorod"};
     
static const char* microdistricts[] = {"Central", "North", "South",
     "Tagansky", "Tverskoy", "Zamoskvorechye", "Academic"};
     
static const char* building_types[] = {
    "Panel", "Brick", "Monolith"};

/*генерация случайного дома*/
apartment_building generate_random_building(){
     apartment_building building;

     unsigned int developer_index = rand() % DEVELOPER_MICRODISTRICT_COUNT;
     const char* random_developer = developers[developer_index];
     strcpy(building.developer, random_developer);

     unsigned int microdistrict_index = rand() % MICRODISTRICT_COUNT;
     const char* random_microdistrict = microdistricts[microdistrict_index];
     strcpy(building.microdistrict, random_microdistrict);
    
     unsigned int type_index = rand() % BUILDING_TYPE_COUNT;
     const char* random_type = building_types[type_index];
     strcpy(building.type, random_type);

     building.year = MIN_YEAR + rand() % YEAR_RANGE;
     building.count_floors = MIN_FLOORS + rand() % MAX_FLOORS;

     /*лифт дома*/
     if (building.count_floors > MANDATORY_ELEVATOR_FLOORS) {
          building.elevator = true;
     } else if (building.count_floors >= HIGH_FLOORS_THRESHOLD) {
          building.elevator = (rand() % 100 < ODDS80);
     } else {
          building.elevator = (rand() % 100 < ODDS20);
     }

    /*мусоропровод дома*/ 
     if (building.year < OLD_YEAR_THRESHOLD) {
          building.garbage_chute = (rand() % 100 < ODDS80);
     }else{
          building.garbage_chute = (rand() % 100 < ODDS70);
     }

     int apartments_per_floor = MIN_APARTMENTS_PER_FLOOR + rand() % MAX_APARTMENTS_PER_FLOOR;
     building.count_apartments = building.count_floors * apartments_per_floor;
     building.area_apartment = MIN_AREA + (rand() % AREA_RANGE) / 10.0f;

     return building;
}
/*генерация cvs файла*/
void  generate_rondom_building_cvs(unsigned int count_home, const char *file_name){
     FILE *file_pointer = fopen(file_name, "w");
     if(file_pointer){
          fputs("Название застройщика, Название микрорайона, Тип, Год постройки, \
               Наличие лифта, Количество квартир, Количество этажей,Средняя площадь квартиры\n", file_pointer);
          for(unsigned int i = 0; i < count_home; i++) {
            apartment_building building = generate_random_building();
            
          char buffer[130];
          sprintf(buffer, "%s,%s,%s,%u,%s,%s,%hu,%hu,%.1f\n",
                   building.developer, building.microdistrict, building.type,
                   building.year, building.elevator ? "true" : "false",
                   building.garbage_chute ? "true" : "false",
                   building.count_apartments, building.count_floors,
                   building.area_apartment);
          fputs(buffer, file_pointer);
          }
          fclose(file_pointer);
          return;
     }

}