#include <stdio.h>
#include <stdlib.h>
#include <lml_matrix.h>
#include <lml_vector.h>
#include <lml_operations.h>

lml_column_vec_double * lml_mult_double_rvec_cvec(lml_row_vec_double *leftVec, lml_column_vec_double *rightVec)
{
if(leftVec==NULL || rightVec==NULL) return NULL;
lml_column_vec_double *productVector;
double product;
index_t i;
dimension_t leftVecSize;
dimension_t rightVecSize;
double leftVecValue;
double rightVecValue;
leftVecSize=lml_row_vec_double_get_size(leftVec);
rightVecSize=lml_column_vec_double_get_size(rightVec);
if(leftVecSize!=rightVecSize) return NULL;
productVector=lml_column_vec_double_create_new(1);
if(productVector==NULL) return NULL;
product=0.0;
for(i=0;i<leftVecSize;i++)
{
leftVecValue=lml_row_vec_double_get(leftVec,i);
rightVecValue=lml_column_vec_double_get(rightVec,i);
product=product+(leftVecValue*rightVecValue);
}
lml_column_vec_double_set(productVector,0,product);
return productVector;
}

lml_column_vec_double * lml_subtract_double_column_vec(lml_column_vec_double *leftVector,lml_column_vec_double *rightVector)
{
if(leftVector==NULL || rightVector==NULL) return NULL;
lml_column_vec_double *resultVector;
double result;
index_t r;
dimension_t leftVecSize;
dimension_t rightVecSize;
double leftVecValue;
double rightVecValue;
leftVecSize=lml_column_vec_double_get_size(leftVector);
rightVecSize=lml_column_vec_double_get_size(rightVector);
if(leftVecSize!=rightVecSize) return NULL;
resultVector=lml_column_vec_double_create_new(leftVecSize);
if(resultVector==NULL) return NULL;
for(r=0;r<leftVecSize;r++)
{
leftVecValue=lml_column_vec_double_get(leftVector,r);
rightVecValue=lml_column_vec_double_get(rightVector,r);
result=leftVecValue-rightVecValue;
lml_column_vec_double_set(resultVector,r,result);
}
return resultVector;
}

lml_column_vec_double * lml_mult_double_mat_cvec(lml_mat_double *leftMat,lml_column_vec_double *rightVector)
{
if(leftMat==NULL || rightVector==NULL) return NULL;
dimension_t leftMatRows;
dimension_t leftMatColumns;
dimension_t rightVecSize;

double leftMatValue;
double rightVecValue;
double product;

lml_column_vec_double *productVector;
index_t r,c;

lml_mat_double_get_dimensions(leftMat,&leftMatRows,&leftMatColumns);
rightVecSize=lml_column_vec_double_get_size(rightVector);
if(leftMatColumns!=rightVecSize) return NULL;
productVector=lml_column_vec_double_create_new(leftMatRows);
if(productVector==NULL) return NULL;
product=0.0;
for(r=0;r<leftMatRows;r++)
{
product=0.0;
for(c=0;c<leftMatColumns;c++)
{
leftMatValue=lml_mat_double_get(leftMat,r,c);
rightVecValue=lml_column_vec_double_get(rightVector,c);
product=product+(leftMatValue*rightVecValue);
}
lml_column_vec_double_set(productVector,r,product);
}
return productVector;
}

lml_column_vec_double * lml_mult_double_scalar_cvec(double scalar_value,lml_column_vec_double *vector)
{
lml_column_vec_double *resultVector;
dimension_t vectorSize;
double value;
double product;
index_t i;
if(vector==NULL) return NULL;
vectorSize=lml_column_vec_double_get_size(vector);
resultVector=lml_column_vec_double_create_new(vectorSize);
if(resultVector==NULL) return NULL;
for(i=0;i<vectorSize;i++)
{
value=lml_column_vec_double_get(vector,i);
product=scalar_value*value;
lml_column_vec_double_set(resultVector,i,product);
}
return resultVector;
}
