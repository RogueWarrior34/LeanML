#ifndef __MLFW__OPERATIONS__DOUBLE__
#define __MLFW__OPERATIONS__DOUBLE__
mlfw_column_vec_double * mlfw_mult_double_rvec_cvec(mlfw_row_vec_double *leftVec, mlfw_column_vec_double *rightVec);
mlfw_column_vec_double * mlfw_subtract_double_column_vec(mlfw_column_vec_double *leftVector,mlfw_column_vec_double *rightVector);
mlfw_column_vec_double * mlfw_mult_double_mat_cvec(mlfw_mat_double *leftMat,mlfw_column_vec_double *rightVector);

#endif