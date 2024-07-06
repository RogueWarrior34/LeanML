#ifndef __LML__SCALE__DOUBLE__
#define __LML__SCALE__DOUBLE__
#include<lml_matrix.h>

lml_mat_double * lml_scale_double_min_max(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,char *min_max_file);
lml_mat_double * lml_scale_double_given_min_max(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,lml_mat_double *min_max_matrix);
 

#endif