#ifndef __LML__OPERATIONS__DOUBLE__
#define __LML__OPERATIONS__DOUBLE__
lml_column_vec_double * lml_mult_double_rvec_cvec(lml_row_vec_double *leftVec, lml_column_vec_double *rightVec);
lml_column_vec_double * lml_subtract_double_column_vec(lml_column_vec_double *leftVector,lml_column_vec_double *rightVector);
lml_column_vec_double * lml_mult_double_mat_cvec(lml_mat_double *leftMat,lml_column_vec_double *rightVector);
lml_column_vec_double * lml_mult_double_scalar_cvec(double scalar_value,lml_column_vec_double *vector);
#endif