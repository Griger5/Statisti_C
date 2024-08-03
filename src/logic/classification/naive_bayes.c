#include <stdlib.h>

#include "naive_bayes.h"
#include "../data_structs/labeled_data_point.h"
#include "../../math_functions/helper_funcs.h"
#include "../../math_functions/stats_calculate.h"
#include "../../math_functions/prob_den_funcs.h"

Matrix *naive_bayes_train(const DataSet data_set) {
    size_t dims = data_set.field_count;
    size_t rec_count = data_set.rec_count;
    size_t class_count = data_set.label_count;

    if (class_count == 0) return NULL;

    Matrix *parameter_key = malloc((1+2*class_count)*sizeof(Matrix));

    if (parameter_key == NULL) return NULL; 

    parameter_key[0] = init_matrix(1, class_count);

    DataSet *classes = malloc(class_count*sizeof(DataSet));

    if (classes == NULL) return NULL;

    for (size_t i = 0; i < class_count; i++) {
        classes[i] = split_label(data_set, i);

        if (classes[i].data == NULL) return NULL;

        parameter_key[0].values[0][i] = 1.0*classes[i].rec_count/rec_count;

        parameter_key[i+1] = init_matrix(1, dims);
        for (size_t j = 0; j < dims; j++) {
            parameter_key[i+1].values[0][j] = mean_arith_data(classes[i], j);
        }

        parameter_key[i+1+class_count] = std_covar_matrix(classes[i]);
    }

    free_array_of_datasets(classes, class_count);

    return parameter_key;
}

int naive_bayes_classify(const Matrix input_vector, const Matrix *parameter_key) {
    size_t class_count = parameter_key[0].cols;

    double *result_for_class = malloc(class_count*sizeof(double));

    if (result_for_class == NULL) return -1;

    for (size_t i = 0; i < class_count; i++) {
        result_for_class[i] = parameter_key[0].values[0][i] * multi_var_normal_pdf(parameter_key[1+i], parameter_key[1+class_count+i], input_vector);
    }

    double curr_max = result_for_class[0];
    int max_index = 0;

    for (size_t i = 1; i < class_count; i++) {
        if (result_for_class[i] > curr_max) {
            curr_max = result_for_class[i];
            max_index = (int)i;
        }
    }

    free(result_for_class);

    return max_index;
}

void naive_bayes_classify_dataset(DataSet data_set, const Matrix *parameter_key) {
    size_t rec_count = data_set.rec_count;
    size_t dims = data_set.field_count;
    size_t class_count = parameter_key[0].cols;

    double *result_for_class = malloc(class_count*sizeof(double));
    if (result_for_class == NULL) return;

    Matrix input_vector = init_matrix(1, dims);

    for (size_t record = 0; record < rec_count; record++) {
        for (size_t i = 0; i < dims; i++) {
            input_vector.values[0][i] = data_set.data[record]->values[i];
        }

        for (size_t i = 0; i < class_count; i++) {
            result_for_class[i] = parameter_key[0].values[0][i] * multi_var_normal_pdf(parameter_key[1+i], parameter_key[1+class_count+i], input_vector);
        }

        double curr_max = result_for_class[0];
        int max_index = 0;

        for (size_t i = 1; i < class_count; i++) {
            if (result_for_class[i] > curr_max) {
                curr_max = result_for_class[i];
                max_index = (int)i;
            }
        }

        data_set.data[record]->label_num = max_index;
    }

    free(result_for_class);
    free_matrix(&input_vector);

    return;
}

void naive_bayes_free_key(Matrix *parameter_key) {
    size_t class_count = parameter_key[0].cols;

    for (size_t i = 0; i < 2*class_count+1; i++) {
        free_matrix(&parameter_key[i]);
    }

    free(parameter_key);
}