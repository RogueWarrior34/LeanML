#ifndef __MLFW__MAT__DOUBLE__
#define __MLFW__MAT__DOUBLE__
struct __mlfw_mat_double;
typedef struct __mlfw_mat_double mlfw_mat_double;
mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows,dimension_t columns);
void mlfw_mat_double_destroy(mlfw_mat_double *matrix);
mlfw_mat_double * mlfw_mat_double_from_csv(const char *csv_file_name);
double mlfw_mat_double_get(mlfw_mat_double *matrix,index_t row,index_t column);
void mlfw_mat_double_set(mlfw_mat_double *matrix,index_t row,index_t column,double value);
void mlfw_mat_double_get_dimensions(mlfw_mat_double *matrix,dimension_t *rows,dimension_t *columns);
void mlfw_mat_double_copy(mlfw_mat_double *target,mlfw_mat_double *source,index_t targetRowIndex,index_t targetColIndex,index_t sourceFromRowIndex,index_t sourceFromColIndex,index_t sourceToRowIndex,index_t sourceToColIndex);
void mlfw_mat_double_fill(mlfw_mat_double *matrix,index_t fromRowIndex,index_t fromColIndex,index_t toRowIndex,index_t toColIndex,double value);
mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix,index_t colIndex);
mlfw_row_vec_double * mlfw_mat_double_create_row_vec(mlfw_mat_double *matrix,index_t rowIndex);
mlfw_mat_double * mlfw_mat_double_shuffle(mlfw_mat_double *matrix,uint8_t shuffle_times);
void mlfw_mat_double_to_csv(mlfw_mat_double *matrix,char *csv_file_name);


#endif