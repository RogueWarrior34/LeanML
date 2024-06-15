#include <stdio.h>
#include <stdlib.h>
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
#include <mlfw_operations.h>

mlfw_column_vec_double * mlfw_mult_double_rvec_cvec(mlfw_row_vec_double *leftVec, mlfw_column_vec_double *rightVec)
{
if(leftVec==NULL || rightVec==NULL) return NULL;
mlfw_column_vec_double *productVector;
double product;
index_t i;
dimension_t leftVecSize;
dimension_t rightVecSize;
double leftVecValue;
double rightVecValue;
leftVecSize=mlfw_row_vec_double_get_size(leftVec);
rightVecSize=mlfw_column_vec_double_get_size(rightVec);
if(leftVecSize!=rightVecSize) return NULL;
productVector=mlfw_column_vec_double_create_new(1);
if(productVector==NULL) return NULL;
product=0.0;
for(i=0;i<leftVecSize;i++)
{
leftVecValue=mlfw_row_vec_double_get(leftVec,i);
rightVecValue=mlfw_column_vec_double_get(rightVec,i);
product=product+(leftVecValue*rightVecValue);
}
mlfw_column_vec_double_set(productVector,0,product);
return productVector;
}

mlfw_column_vec_double * mlfw_subtract_double_column_vec(mlfw_column_vec_double *leftVector,mlfw_column_vec_double *rightVector)
{
if(leftVector==NULL || rightVector==NULL) return NULL;
mlfw_column_vec_double *resultVector;
double result;
index_t r;
dimension_t leftVecSize;
dimension_t rightVecSize;
double leftVecValue;
double rightVecValue;
leftVecSize=mlfw_column_vec_double_get_size(leftVector);
rightVecSize=mlfw_column_vec_double_get_size(rightVector);
if(leftVecSize!=rightVecSize) return NULL;
resultVector=mlfw_column_vec_double_create_new(leftVecSize);
if(resultVector==NULL) return NULL;
for(r=0;r<leftVecSize;r++)
{
leftVecValue=mlfw_column_vec_double_get(leftVector,r);
rightVecValue=mlfw_column_vec_double_get(rightVector,r);
result=leftVecValue-rightVecValue;
mlfw_column_vec_double_set(resultVector,r,result);
}
return resultVector;
}

mlfw_column_vec_double * mlfw_mult_double_mat_cvec(mlfw_mat_double *leftMat,mlfw_column_vec_double *rightVector)
{
if(leftMat==NULL || rightVector==NULL) return NULL;
dimension_t leftMatRows;
dimension_t leftMatColumns;
dimension_t rightVecSize;

double leftMatValue;
double rightVecValue;
double product;

mlfw_column_vec_double *productVector;
index_t r,c;

mlfw_mat_double_get_dimensions(leftMat,&leftMatRows,&leftMatColumns);
rightVecSize=mlfw_column_vec_double_get_size(rightVector);
if(leftMatColumns!=rightVecSize) return NULL;
productVector=mlfw_column_vec_double_create_new(leftMatRows);
if(productVector==NULL) return NULL;
product=0;
for(r=0;r<leftMatRows;r++)
{
for(c=0;c<leftMatColumns;c++)
{
leftMatValue=mlfw_mat_double_get(leftMat,r,c);
rightVecValue=mlfw_column_vec_double_get(rightVector,c);
product=product+(leftMatValue*rightVecValue);
}
mlfw_column_vec_double_set(productVector,r,product);
}
return productVector;
}

