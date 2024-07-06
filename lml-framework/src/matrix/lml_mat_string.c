#include<lml_matrix.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct __lml_mat_string
{
char ***data;
dimension_t rows;
dimension_t columns;
}lml_mat_string;

lml_mat_string * lml_mat_string_create_new(dimension_t rows,dimension_t columns)
{
lml_mat_string *matrix;
index_t r,k,c;
if(rows<=0 || columns<=0) return NULL;
matrix=(lml_mat_string *)malloc(sizeof(lml_mat_string));
if(matrix==NULL) return NULL;
matrix->data=(char ***)malloc(sizeof(char **)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
} 
for(r=0;r<rows;r++)
{
matrix->data[r]=(char **)malloc(sizeof(char *)*columns);
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
else
{
for(c=0;c<columns;c++) matrix->data[r][c]=NULL;
}
}
matrix->rows=rows;
matrix->columns=columns;
return matrix;
}


void lml_mat_string_destroy(lml_mat_string *matrix)
{
index_t r,c;
if(matrix==NULL) return;
for(r=0;r<matrix->rows;r++)
{
for(c=0;c<matrix->columns;c++)
{
if(matrix->data[r][c]!=NULL) free(matrix->data[r][c]);
}
free(matrix->data[r]);
}
free(matrix->data);
free(matrix);
}

lml_mat_string * lml_mat_string_from_csv(const char *csv_file_name)
{
lml_mat_string *matrix;
int index;
char m;
index_t r,c;
char string[5001];
dimension_t rows,columns;
FILE *file;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
rows=0;
columns=0;
while(1)
{
m=getc(file);
if(feof(file)) break;
if(rows==0)
{
if(m==',') columns++;
}
if(m=='\n') rows++;
}
columns++;
matrix=lml_mat_string_create_new(rows,columns);
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
string[index]='\0';
matrix->data[r][c]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[r][c]!=NULL) 
{
strcpy(matrix->data[r][c],string);
}
index=0;
c++;
if(c==matrix->columns)
{
r++;
c=0;
}
}
else
{
string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}

void lml_mat_string_get(lml_mat_string *matrix,index_t row,index_t column,char **string)
{
if(string==NULL) return;
if(matrix==NULL)
{
*string=NULL;
return;
}
if(row<0 || row>=matrix->rows)
{
*string=NULL;
return;
}
if(column<0 || column>=matrix->columns)
{
*string=NULL;
return;
}
if(matrix->data[row][column]==NULL)
{
*string=NULL;
return;
}
*string=(char *)malloc(sizeof(char)*(strlen(matrix->data[row][column])+1));
if(*string==NULL) return;
strcpy(*string,matrix->data[row][column]);
}

void lml_mat_string_set(lml_mat_string *matrix,index_t row,index_t column,char *string)
{
if(matrix==NULL || string==NULL) return;
if(row<0 || row>=matrix->rows) return;
if(column<0 || column>matrix->columns) return;
if(matrix->data[row][column]!=NULL) free(matrix->data[row][column]);
matrix->data[row][column]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[row][column]!=NULL) strcpy(matrix->data[row][column],string);
}

void lml_mat_string_get_dimensions(lml_mat_string *matrix,dimension_t *rows,dimension_t *columns)
{
if(matrix==NULL) return;
if(rows!=NULL) *rows=matrix->rows; 
if(columns!=NULL) *columns=matrix->columns;
}
