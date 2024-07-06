#ifndef __LML__MAT__DOUBLE__
#define __LML__MAT__DOUBLE__
struct __lml_mat_double;
typedef struct __lml_mat_double lml_mat_double;
lml_mat_double * lml_mat_double_create_new(dimension_t rows,dimension_t columns);
void lml_mat_double_destroy(lml_mat_double *matrix);
lml_mat_double * lml_mat_double_from_csv(const char *csv_file_name);
double lml_mat_double_get(lml_mat_double *matrix,index_t row,index_t column);
void lml_mat_double_set(lml_mat_double *matrix,index_t row,index_t column,double value);
void lml_mat_double_get_dimensions(lml_mat_double *matrix,dimension_t *rows,dimension_t *columns);
void lml_mat_double_copy(lml_mat_double *target,lml_mat_double *source,index_t targetRowIndex,index_t targetColIndex,index_t sourceFromRowIndex,index_t sourceFromColIndex,index_t sourceToRowIndex,index_t sourceToColIndex);
void lml_mat_double_fill(lml_mat_double *matrix,index_t fromRowIndex,index_t fromColIndex,index_t toRowIndex,index_t toColIndex,double value);
lml_column_vec_double * lml_mat_double_create_column_vec(lml_mat_double *matrix,index_t colIndex);
lml_row_vec_double * lml_mat_double_create_row_vec(lml_mat_double *matrix,index_t rowIndex);
lml_mat_double * lml_mat_double_shuffle(lml_mat_double *matrix,uint8_t shuffle_times);
void lml_mat_double_to_csv(lml_mat_double *matrix,char *csv_file_name);
lml_mat_double * lml_mat_double_transpose(lml_mat_double *matrix);
double lml_mat_double_get_minimum(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);
double lml_mat_double_get_maximum(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index);


#endif