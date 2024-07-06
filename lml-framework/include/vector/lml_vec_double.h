#ifndef __LML__VEC__DOUBLE__
#define __LML__VEC__DOUBLE__
struct __lml_column_vec_double;
struct __lml_row_vec_double;
typedef struct __lml_column_vec_double lml_column_vec_double;
typedef struct __lml_row_vec_double lml_row_vec_double;
//column
lml_column_vec_double * lml_column_vec_double_create_new(dimension_t size);
void lml_column_vec_double_destroy(lml_column_vec_double *vector);
double lml_column_vec_double_get(lml_column_vec_double *vector,index_t index);
void lml_column_vec_double_set(lml_column_vec_double *vector,index_t index,double value);
lml_column_vec_double * lml_column_vec_double_create_new_filled(dimension_t size,double value);
lml_row_vec_double * lml_column_vec_double_transpose(lml_column_vec_double *vector);
dimension_t lml_column_vec_double_get_size(lml_column_vec_double *vector);
double lml_column_vec_double_get_mean(lml_column_vec_double *vector);
lml_column_vec_double * lml_column_vec_double_from_csv(char *csv_file_name);
void lml_column_vec_double_to_csv(lml_column_vec_double *vector,char *csv_file_name);

//row
lml_row_vec_double * lml_row_vec_double_create_new(dimension_t size);
void lml_row_vec_double_destroy(lml_row_vec_double *vector);
double lml_row_vec_double_get(lml_row_vec_double *vector,index_t index);
void lml_row_vec_double_set(lml_row_vec_double *vector,index_t index,double value);
lml_row_vec_double * lml_row_vec_double_create_new_filled(dimension_t size,double value);
lml_column_vec_double * lml_row_vec_double_transpose(lml_row_vec_double *vector);
dimension_t lml_row_vec_double_get_size(lml_row_vec_double *vector);
double lml_row_vec_double_get_mean(lml_row_vec_double *vector);
lml_row_vec_double * lml_row_vec_double_from_csv(char *csv_file_name);
void lml_row_vec_double_to_csv(lml_row_vec_double *vector,char *csv_file_name);

#endif