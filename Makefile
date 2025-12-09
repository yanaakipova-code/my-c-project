TARGET = program
.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

main.o: main.c
	gcc -c -o main.o main.c

args_parser.o: args_parser.c args_parser.h
	gcc -c -o args_parser.o args_parser.c

vector.o: vector.c vector.h apartment_building.h
	gcc -c -o vector.o vector.c

sort.o: sort.c sort.h vector.h apartment_building.h
	gcc -c -o sort.o sort.c

csv_reader.o: csv_reader.c csv_reader.h vector.h apartment_building.h
	gcc -c -o csv_reader.o csv_reader.c

csv_writer.o: csv_writer.c csv_writer.h vector.h apartment_building.h
	gcc -c -o csv_writer.o csv_writer.c

building_generator.o: building_generator.c building_generator.h apartment_building.h
	gcc -c -o building_generator.o building_generator.c

table_printer.o: table_printer.c table_printer.h vector.h apartment_building.h
	gcc -c -o table_printer.o table_printer.c

$(TARGET): main.o args_parser.o vector.o sort.o csv_reader.o csv_writer.o building_generator.o table_printer.o
	gcc -o $(TARGET) main.o args_parser.o vector.o sort.o csv_reader.o csv_writer.o building_generator.o table_printer.o

