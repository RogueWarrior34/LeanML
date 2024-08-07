#include <lml_matrix.h>
#include <stdlib.h>
#include <stdio.h>
#include <lml_vector.h>
#include <time.h>

typedef struct __lml_mat_double
{
	double **data;
	dimension_t rows;
	dimension_t columns;
}lml_mat_double;

lml_mat_double * lml_mat_double_create_new(dimension_t rows, dimension_t columns)
{
lml_mat_double *matrix;
index_t r,k;
if(rows<=0 || columns<=0) return NULL;
matrix=(lml_mat_double *)malloc(sizeof(lml_mat_double));
if(matrix==NULL) return NULL;
matrix->data=(double **)malloc(sizeof(double *)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}
for(r=0;r<rows;r++)
{
matrix->data[r]=(double *)malloc(sizeof(double)*columns);
if(matrix->data[r]==NULL)
{
for(k=0;k<r;k++)
{
free(matrix->data[k]);
}
free(matrix->data);
free(matrix);
return NULL;
}
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}

void lml_mat_double_destroy(lml_mat_double *matrix)
{
index_t r;
if(matrix==NULL) return;
for(r=0;r<matrix->rows;r++)
{
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
}

lml_mat_double * lml_mat_double_from_csv(const char *csv_file_name)
{
lml_mat_double *matrix;
int index;
char m;
index_t r,c;
double value;
char double_string[1025];
dimension_t rows,columns;
FILE *file;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
rows=0;
columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(rows==0)
{
if(m==',') columns++;
}
if(m=='\n') rows++;
}
columns++;
matrix=lml_mat_double_create_new(rows,columns);
if(matrix==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',' || m=='\n')
{
double_string[index]='\0';
value=strtod(double_string,NULL);
index=0;
matrix->data[r][c]=value;
c++;
if(c==matrix->columns)
{
r++;
c=0;
}
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}


double lml_mat_double_get(lml_mat_double *matrix,index_t row,index_t column)
{
if(matrix==NULL)
{
printf("Invalid matrix.\n");
return 0.0;
}
else if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns)
{
printf("Invalid index.\n");
return 0.0;
}
else 
{
return matrix->data[row][column];
}
}

void lml_mat_double_set(lml_mat_double *matrix,index_t row,index_t column,double value)
{
if(matrix==NULL)
{
printf("Invalid matrix.\n");
return;
}
else if(row<0 || row>=matrix->rows || column<0 || column>=matrix->columns)
{
printf("Invalid index.\n");
return;
}
else
{
matrix->data[row][column]=value;
}
}

void lml_mat_double_get_dimensions(lml_mat_double *matrix,dimension_t *rows,dimension_t *columns)
{
if(matrix==NULL) return;
if(rows!=NULL) *rows=matrix->rows;
if(columns!=NULL) *columns=matrix->columns; 
}

void lml_mat_double_copy(lml_mat_double *target,lml_mat_double *source,index_t targetRowIndex,index_t targetColIndex,index_t sourceFromRowIndex,index_t sourceFromColIndex,index_t sourceToRowIndex,index_t sourceToColIndex)
{
index_t targetRow;
index_t targetColumn;
index_t sourceRow;
index_t sourceColumn;
if(target==NULL || source==NULL) return;
if(targetRowIndex<0 || targetRowIndex>=target->rows) return;
if(targetColIndex<0 || targetColIndex>=target->columns) return;
if(sourceFromRowIndex<0 || sourceFromRowIndex>=source->rows) return;
if(sourceFromColIndex<0 || sourceFromColIndex>=source->columns) return;
if(sourceToRowIndex<0 || sourceToRowIndex>=source->rows) return;
if(sourceToColIndex<0 || sourceToColIndex>=source->columns) return;

if(sourceFromRowIndex>sourceToRowIndex || sourceFromColIndex>sourceToColIndex) return;

targetRow=targetRowIndex;
sourceRow=sourceFromRowIndex;
while(sourceRow<=sourceToRowIndex)
{
targetColumn=targetColIndex;
sourceColumn=sourceFromColIndex;
while(sourceColumn<=sourceToColIndex)
{
if(targetRow>=0 && targetRow<target->rows && targetColumn>=0 && targetColumn<target->columns)
{
target->data[targetRow][targetColumn]=source->data[sourceRow][sourceColumn];
}
sourceColumn++;
targetColumn++;
}
sourceRow++;
targetRow++;
}

}

void lml_mat_double_fill(lml_mat_double *matrix,index_t fromRowIndex,index_t fromColIndex,index_t toRowIndex,index_t toColIndex,double value)
{
if(matrix==NULL) return;
if(fromRowIndex<0 || fromColIndex<0 || toRowIndex<0 || toColIndex<0) return;
if(fromRowIndex>=matrix->rows || fromRowIndex>=matrix->columns || toRowIndex>=matrix->rows || toColIndex>=matrix->columns) return;
if(fromRowIndex>toRowIndex || fromColIndex>toColIndex) return;
index_t r,c;
for(r=fromRowIndex;r<=toRowIndex;r++)
{
for(c=fromColIndex;c<=toColIndex;c++)
{
matrix->data[r][c]=value;
}
}
}

lml_column_vec_double * lml_mat_double_create_column_vec(lml_mat_double *matrix,index_t colIndex)
{
if(matrix==NULL) return NULL;
if(colIndex<0 || colIndex>=matrix->columns) return NULL;
lml_column_vec_double *vector;
vector=lml_column_vec_double_create_new(matrix->rows);
if(vector==NULL) return NULL;
index_t r;
for(r=0;r<matrix->rows;r++) lml_column_vec_double_set(vector,r,matrix->data[r][colIndex]);
return vector;
}

lml_row_vec_double * lml_mat_double_create_row_vec(lml_mat_double *matrix,index_t rowIndex)
{
if(matrix==NULL) return NULL;
if(rowIndex<0 || rowIndex>=matrix->rows) return NULL;
lml_row_vec_double *vector;
vector=lml_row_vec_double_create_new(matrix->columns);
if(vector==NULL) return NULL;
index_t c;
for(c=0;c<matrix->columns;c++) lml_row_vec_double_set(vector,c,matrix->data[rowIndex][c]);
return vector;
}

lml_mat_double * lml_mat_double_shuffle(lml_mat_double *matrix,uint8_t shuffle_times)
{
lml_mat_double *shuffledMatrix;
int r;
index_t a,b;
index_t c;
index_t u;
index_t idx;
index_t endIndex;
uint8_t j;
double temp;
if(matrix==NULL) return NULL;
if(shuffle_times==0) return NULL;
shuffledMatrix=lml_mat_double_create_new(matrix->rows,matrix->columns);
if(shuffledMatrix==NULL) return NULL;
lml_mat_double_copy(shuffledMatrix,matrix,0,0,0,0,matrix->rows-1,matrix->columns-1);
b=shuffledMatrix->rows-1;
srand(time(NULL));
endIndex=shuffledMatrix->rows-3;
//printf("rows cols %d %d\n",shuffledMatrix->rows,shuffledMatrix->columns);
for(j=1;j<=shuffle_times;j++)
{
for(u=0;u<=endIndex;u++)
{
a=u+1;
r=rand();
idx=(r%(b-a+1))+a;
for(c=0;c<shuffledMatrix->columns;c++)
{
//printf("uc %20.10lf ",shuffledMatrix->data[u][c]);
//printf("idxc %20.10lf ",shuffledMatrix->data[idx][c]);
//printf("\n");
temp=shuffledMatrix->data[u][c];
shuffledMatrix->data[u][c]=shuffledMatrix->data[idx][c];
shuffledMatrix->data[idx][c]=temp;
}
}
}
return shuffledMatrix;
}

void lml_mat_double_to_csv(lml_mat_double *matrix,char *csv_file_name)
{
index_t r,c;
char seperator;
FILE *file;
if(matrix==NULL || csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
fprintf(file,"%lf",matrix->data[r][c]);
if(c==matrix->columns-1) seperator='\n';
else seperator=',';
fputc(seperator,file);
}
}
fclose(file);
}

lml_mat_double * lml_mat_double_transpose(lml_mat_double *matrix)
{
lml_mat_double *transpose;
index_t r,c;
if(matrix==NULL) return NULL;
transpose=lml_mat_double_create_new(matrix->columns,matrix->rows);
if(transpose==NULL) return NULL;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
transpose->data[c][r]=matrix->data[r][c];
}
}
return transpose;
}

double lml_mat_double_get_minimum(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double minimum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0 || end_row_index>=matrix->rows) return 0.0;
if(start_column_index<0 || end_column_index>=matrix->columns) return 0.0;
if(start_row_index>end_row_index || start_column_index>end_column_index) return 0.0;
minimum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]<minimum) minimum=matrix->data[r][c];
}
}
return minimum;
}

double lml_mat_double_get_maximum(lml_mat_double *matrix,index_t start_row_index,index_t start_column_index,index_t end_row_index,index_t end_column_index)
{
double maximum;
index_t r,c;
if(matrix==NULL) return 0.0;
if(start_row_index<0 || end_row_index>=matrix->rows) return 0.0;
if(start_column_index<0 || end_column_index>=matrix->columns) return 0.0;
if(start_row_index>end_row_index || start_column_index>end_column_index) return 0.0;
maximum=matrix->data[start_row_index][start_column_index];
for(r=start_row_index;r<=end_row_index;r++)
{
for(c=start_column_index;c<=end_column_index;c++)
{
if(matrix->data[r][c]>maximum) maximum=matrix->data[r][c];
}
}
return maximum;
}