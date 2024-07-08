CC = gcc
CFLAGS = -Wall -Wextra

run: clean data_point.o lin_reg.o stats_calculate.o file_operation.o temp_main.o
	$(CC) $(CFLAGS) -o run build/data_point.o build/lin_reg.o build/stats_calculate.o build/file_operation.o build/temp_main.o

temp_main.o:
	$(CC) $(CFLAGS) -c src/temp_main.c -o build/temp_main.o

lin_reg.o:
	$(CC) $(CFLAGS) -c src/logic/regression/lin_reg.c -o build/lin_reg.o

data_point.o:
	$(CC) $(CFLAGS) -c src/logic/data_structs/data_point.c -o build/data_point.o

stats_calculate.o:
	$(CC) $(CFLAGS) -c src/math_functions/stats_calculate.c -o build/stats_calculate.o

file_operation.o:
	$(CC) $(CFLAGS) -c src/utils/file_operation.c -o build/file_operation.o

clean:
	rm -rf build
	mkdir build