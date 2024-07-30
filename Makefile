CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm

run: clean data_point.o labeled_data_point.o lin_reg.o matrix_operations.o stats_calculate.o prob_den_funcs.o file_operation.o label_list.o temp_main.o
	$(CC) $(CFLAGS) -o run build/data_point.o build/labeled_data_point.o build/lin_reg.o build/matrix_operations.o build/helper_funcs.o build/stats_calculate.o build/prob_den_funcs.o build/file_operation.o build/label_list.o build/temp_main.o $(LIBS)

temp_main.o:
	$(CC) $(CFLAGS) -c src/temp_main.c -o build/temp_main.o

lin_reg.o:
	$(CC) $(CFLAGS) -c src/logic/regression/lin_reg.c -o build/lin_reg.o

data_point.o:
	$(CC) $(CFLAGS) -c src/logic/data_structs/data_point.c -o build/data_point.o

labeled_data_point.o:
	$(CC) $(CFLAGS) -c src/logic/data_structs/labeled_data_point.c -o build/labeled_data_point.o

prob_den_funcs.o:
	$(CC) $(CFLAGS) -c src/math_functions/prob_den_funcs.c -o build/prob_den_funcs.o

stats_calculate.o: helper_funcs.o
	$(CC) $(CFLAGS) -c src/math_functions/stats_calculate.c -o build/stats_calculate.o

helper_funcs.o:
	$(CC) $(CFLAGS) -c src/math_functions/helper_funcs.c -o build/helper_funcs.o 

matrix_operations.o:
	$(CC) $(CFLAGS) -c src/math_functions/matrix_operations.c -o build/matrix_operations.o	

label_list.o:
	$(CC) $(CFLAGS) -c src/utils/label_list.c -o build/label_list.o

file_operation.o:
	$(CC) $(CFLAGS) -c src/utils/file_operation.c -o build/file_operation.o

clean:
	rm -rf build
	mkdir build