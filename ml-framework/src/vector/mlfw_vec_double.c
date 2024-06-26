#include <stdio.h>
#include <stdlib.h>
#include <mlfw_vector.h>

typedef struct __mlfw_column_vec_double
{
double *data;
dimension_t size;
}mlfw_column_vec_double;
typedef struct __mlfw_row_vec_double
{
double *data;
dimension_t size;
}mlfw_row_vec_double;

//column
mlfw_column_vec_double * mlfw_column_vec_double_create_new(dimension_t size)
{
mlfw_column_vec_double *vector;
if(size<=0) return NULL;
vector=(mlfw_column_vec_double *)malloc(sizeof(mlfw_column_vec_double));
if(vector==NULL) return NULL;
vector->data=(double *)malloc(sizeof(double)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}

void mlfw_column_vec_double_destroy(mlfw_column_vec_double *vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
return;
}

double mlfw_column_vec_double_get(mlfw_column_vec_double *vector,index_t index)
{
double value=0.0;
if(vector==NULL) return value;
if(index<0 || index>=vector->size) return value; 
return vector->data[index];
}

void mlfw_column_vec_double_set(mlfw_column_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}

mlfw_column_vec_double * mlfw_column_vec_double_create_new_filled(dimension_t size,double value)
{
index_t index;
mlfw_column_vec_double *vector;
vector=mlfw_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(index=0;index<vector->size;index++)
{
vector->data[index]=value;
}
return vector;
}

mlfw_row_vec_double * mlfw_column_vec_double_transpose(mlfw_column_vec_double *vector)
{
index_t index;
if(vector==NULL) return NULL;
mlfw_row_vec_double *transposedVector;
transposedVector=mlfw_row_vec_double_create_new(vector->size);
if(transposedVector==NULL) return NULL;
for(index=0;index<transposedVector->size;index++)
{
transposedVector->data[index]=vector->data[index];
}
return transposedVector;
}

dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}

//row
mlfw_row_vec_double * mlfw_row_vec_double_create_new(dimension_t size)
{
mlfw_row_vec_double *vector;
if(size<=0) return NULL;
vector=(mlfw_row_vec_double *)malloc(sizeof(mlfw_row_vec_double));
if(vector==NULL) return NULL;
vector->data=(double *)malloc(sizeof(double)*size);
if(vector->data==NULL)
{
free(vector);
return NULL;
}
vector->size=size;
return vector;
}

void mlfw_row_vec_double_destroy(mlfw_row_vec_double *vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
return;
}

double mlfw_row_vec_double_get(mlfw_row_vec_double *vector,index_t index)
{
double value=0.0;
if(vector==NULL) return value;
if(index<0 || index>=vector->size) return value; 
return vector->data[index];
}

void mlfw_row_vec_double_set(mlfw_row_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return; 
vector->data[index]=value;
}

mlfw_row_vec_double * mlfw_row_vec_double_create_new_filled(dimension_t size,double value)
{
index_t i;
mlfw_row_vec_double *vector;
vector=mlfw_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(i=0;i<vector->size;i++)
{
vector->data[i]=value;
}
return vector;
}

mlfw_column_vec_double * mlfw_row_vec_double_transpose(mlfw_row_vec_double *vector)
{
index_t i;
if(vector==NULL) return NULL;
mlfw_column_vec_double *transposedVector;
transposedVector=mlfw_column_vec_double_create_new(vector->size);
if(transposedVector==NULL) return NULL;
for(i=0;i<transposedVector->size;i++)
{
transposedVector->data[i]=vector->data[i];
}
return transposedVector;
}

dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}
