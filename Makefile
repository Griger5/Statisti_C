CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags gtk4`
LIBS = -lm `pkg-config --libs gtk4`

run: clean data_point.o global_var.o temp_ui.o labeled_data_point.o standard_plot.o regression_plot.o lin_reg.o naive_bayes.o matrix_operations.o stats_calculate.o prob_den_funcs.o file_operation.o label_list.o main.o
	$(CC) $(CFLAGS) -o run build/data_point.o build/global_var.o build/temp_ui.o build/labeled_data_point.o build/standard_plot.o build/regression_plot.o build/lin_reg.o build/naive_bayes.o build/matrix_operations.o build/helper_funcs.o build/stats_calculate.o build/prob_den_funcs.o build/file_operation.o build/label_list.o build/main.o $(LIBS)

main.o:
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

global_var.o:
	$(CC) $(CFLAGS) -c src/gui/global_var.c -o build/global_var.o

temp_ui.o:
	$(CC) $(CFLAGS) -c src/gui/temp_ui.c -o build/temp_ui.o

standard_plot.o:
	$(CC) $(CFLAGS) -c src/plotting/standard_plot.c -o build/standard_plot.o

regression_plot.o:
	$(CC) $(CFLAGS) -c src/plotting/regression_plot.c -o build/regression_plot.o

lin_reg.o:
	$(CC) $(CFLAGS) -c src/logic/regression/lin_reg.c -o build/lin_reg.o

naive_bayes.o:
	$(CC) $(CFLAGS) -c src/logic/classification/naive_bayes.c -o build/naive_bayes.o

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