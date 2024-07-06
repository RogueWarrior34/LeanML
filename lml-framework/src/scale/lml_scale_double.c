#include<lml_scale.h>
#include<lml_matrix.h>
#include<stdlib.h>
#include<stdio.h>

lml_mat_double * lml_scale_double_min_max(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,char *min_max_file)
{
FILE *file;
dimension_t matrixRows;
dimension_t matrixColumns;
dimension_t newMatrixRows;
dimension_t newMatrixColumns;
lml_mat_double *newMatrix;
double *min;
double *max;
index_t r;
index_t c;
index_t newRow;
index_t newCol;
index_t i;
double value;
double scaledValue;
if(matrix==NULL) return NULL;
lml_mat_double_get_dimensions(matrix,&matrixRows,&matrixColumns);
if(start_row_index<0 || end_row_index>=matrixRows) return NULL;
if(start_column_index<0 || end_column_index>=matrixColumns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
newMatrixRows=end_row_index-start_row_index+1;
newMatrixColumns=end_column_index-start_column_index+1;
newMatrix=lml_mat_double_create_new(newMatrixRows,newMatrixColumns);
if(newMatrix==NULL) return NULL;
min=(double *)malloc(sizeof(double)*newMatrixColumns);
if(min==NULL)
{
lml_mat_double_destroy(newMatrix);
return NULL;
}
max=(double *)malloc(sizeof(double)*newMatrixColumns);
if(max==NULL)
{
lml_mat_double_destroy(newMatrix);
free(min);
return NULL;
}
i=0;
for(c=start_column_index;c<=end_column_index;c++)
{
min[i]=lml_mat_double_get_minimum(matrix,start_row_index,c,end_row_index,c);
max[i]=lml_mat_double_get_maximum(matrix,start_row_index,c,end_row_index,c);
i++;
}
r=start_row_index;
for(newRow=0;newRow<newMatrixRows;newRow++)
{
c=start_column_index;
for(newCol=0;newCol<newMatrixColumns;newCol++)
{
value=lml_mat_double_get(matrix,r,c);
scaledValue=(value-min[newCol])/(max[newCol]-min[newCol]);
lml_mat_double_set(newMatrix,newRow,newCol,scaledValue);
c++;
}
r++;
}
file=fopen(min_max_file,"w");
if(file==NULL)
{
free(min);
free(max);
lml_mat_double_destroy(newMatrix);
return NULL;
}
for(i=0;i<newCol;i++)
{
fprintf(file,"%lf",min[i]);
if(i==newCol-1) fputc('\n',file);
else fputc(',',file);
}
for(i=0;i<newCol;i++)
{
fprintf(file,"%lf",max[i]);
if(i==newCol-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
free(min);
free(max);
return newMatrix;
}


lml_mat_double * lml_scale_double_given_min_max(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index,lml_mat_double *min_max_matrix)
{
dimension_t matrixRows;
dimension_t matrixColumns;
dimension_t newMatrixRows;
dimension_t newMatrixColumns;
dimension_t minMaxRows;
dimension_t minMaxColumns;
lml_mat_double *newMatrix;
index_t r;
index_t c;
index_t newRow;
index_t newCol;
index_t i;
double min;
double max;
double value;
double scaledValue;
if(matrix==NULL) return NULL;
lml_mat_double_get_dimensions(matrix,&matrixRows,&matrixColumns);
lml_mat_double_get_dimensions(min_max_matrix,&minMaxRows,&minMaxColumns);
if(minMaxRows!=2) return NULL;
if(start_row_index<0 || end_row_index>=matrixRows) return NULL;
if(start_column_index<0 || end_column_index>=matrixColumns) return NULL;
if(start_row_index>end_row_index || start_column_index>end_column_index) return NULL;
newMatrixRows=end_row_index-start_row_index+1;
newMatrixColumns=end_column_index-start_column_index+1;
if(minMaxColumns!=newMatrixColumns) return NULL;
newMatrix=lml_mat_double_create_new(newMatrixRows,newMatrixColumns);
if(newMatrix==NULL) return NULL;
r=start_row_index;
for(newRow=0;newRow<newMatrixRows;newRow++)
{
c=start_column_index;
for(newCol=0;newCol<newMatrixColumns;newCol++)
{
min=lml_mat_double_get(min_max_matrix,0,newCol);
max=lml_mat_double_get(min_max_matrix,1,newCol);
value=lml_mat_double_get(matrix,r,c);
scaledValue=(value-min)/(max-min);
lml_mat_double_set(newMatrix,newRow,newCol,scaledValue);
c++;
}
r++;
}

return newMatrix;
}
