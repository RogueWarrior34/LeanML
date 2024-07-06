#include <stdio.h>
#include <stdlib.h>
#include <lml_vector.h>

typedef struct __lml_column_vec_double
{
double *data;
dimension_t size;
}lml_column_vec_double;
typedef struct __lml_row_vec_double
{
double *data;
dimension_t size;
}lml_row_vec_double;

//column
lml_column_vec_double * lml_column_vec_double_create_new(dimension_t size)
{
lml_column_vec_double *vector;
if(size<=0) return NULL;
vector=(lml_column_vec_double *)malloc(sizeof(lml_column_vec_double));
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

void lml_column_vec_double_destroy(lml_column_vec_double *vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
return;
}

double lml_column_vec_double_get(lml_column_vec_double *vector,index_t index)
{
double value=0.0;
if(vector==NULL) return value;
if(index<0 || index>=vector->size) return value; 
return vector->data[index];
}

void lml_column_vec_double_set(lml_column_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return;
vector->data[index]=value;
}

lml_column_vec_double * lml_column_vec_double_create_new_filled(dimension_t size,double value)
{
index_t index;
lml_column_vec_double *vector;
vector=lml_column_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(index=0;index<vector->size;index++)
{
vector->data[index]=value;
}
return vector;
}

lml_row_vec_double * lml_column_vec_double_transpose(lml_column_vec_double *vector)
{
index_t index;
if(vector==NULL) return NULL;
lml_row_vec_double *transposedVector;
transposedVector=lml_row_vec_double_create_new(vector->size);
if(transposedVector==NULL) return NULL;
for(index=0;index<transposedVector->size;index++)
{
transposedVector->data[index]=vector->data[index];
}
return transposedVector;
}

dimension_t lml_column_vec_double_get_size(lml_column_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}

double lml_column_vec_double_get_mean(lml_column_vec_double *vector)
{
double mean;
double sum;
index_t i;
if(vector==NULL) return 0.0;
sum=0;
for(i=0;i<vector->size;i++)
{
sum=sum+vector->data[i];
}
mean=(sum/(double)vector->size);
return mean;
}

lml_column_vec_double * lml_column_vec_double_from_csv(char *csv_file_name)
{
lml_column_vec_double *vector;
FILE *file;
index_t i;
index_t index;
dimension_t size;
char m;
char double_string[1025];
double value;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',') size++;
}
size++;
vector=lml_column_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
index=0;
i=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',' || m=='\n')
{
double_string[index]='\0';
value=strtod(double_string,NULL);
lml_column_vec_double_set(vector,i,value);
i++;
index=0;
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return vector;
}

void lml_column_vec_double_to_csv(lml_column_vec_double *vector,char *csv_file_name)
{
FILE *file;
index_t i;
if(vector==NULL || csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}


//row
lml_row_vec_double * lml_row_vec_double_create_new(dimension_t size)
{
lml_row_vec_double *vector;
if(size<=0) return NULL;
vector=(lml_row_vec_double *)malloc(sizeof(lml_row_vec_double));
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

void lml_row_vec_double_destroy(lml_row_vec_double *vector)
{
if(vector==NULL) return;
free(vector->data);
free(vector);
return;
}

double lml_row_vec_double_get(lml_row_vec_double *vector,index_t index)
{
double value=0.0;
if(vector==NULL) return value;
if(index<0 || index>=vector->size) return value; 
return vector->data[index];
}

void lml_row_vec_double_set(lml_row_vec_double *vector,index_t index,double value)
{
if(vector==NULL) return;
if(index<0 || index>=vector->size) return; 
vector->data[index]=value;
}

lml_row_vec_double * lml_row_vec_double_create_new_filled(dimension_t size,double value)
{
index_t i;
lml_row_vec_double *vector;
vector=lml_row_vec_double_create_new(size);
if(vector==NULL) return NULL;
for(i=0;i<vector->size;i++)
{
vector->data[i]=value;
}
return vector;
}

lml_column_vec_double * lml_row_vec_double_transpose(lml_row_vec_double *vector)
{
index_t i;
if(vector==NULL) return NULL;
lml_column_vec_double *transposedVector;
transposedVector=lml_column_vec_double_create_new(vector->size);
if(transposedVector==NULL) return NULL;
for(i=0;i<transposedVector->size;i++)
{
transposedVector->data[i]=vector->data[i];
}
return transposedVector;
}

dimension_t lml_row_vec_double_get_size(lml_row_vec_double *vector)
{
if(vector==NULL) return 0;
return vector->size;
}

double lml_row_vec_double_get_mean(lml_row_vec_double *vector)
{
double mean;
double sum;
index_t i;
if(vector==NULL) return 0.0;
sum=0;
for(i=0;i<vector->size;i++)
{
sum=sum+vector->data[i];
}
mean=(sum/(double)vector->size);
return mean;
}

lml_row_vec_double * lml_row_vec_double_from_csv(char *csv_file_name)
{
lml_row_vec_double *vector;
FILE *file;
index_t i;
index_t index;
dimension_t size;
char m;
char double_string[1025];
double value;
if(csv_file_name==NULL) return NULL;
file=fopen(csv_file_name,"r");
if(file==NULL) return NULL;
size=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',') size++;
}
size++;
vector=lml_row_vec_double_create_new(size);
if(vector==NULL)
{
fclose(file);
return NULL;
}
rewind(file);
index=0;
i=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',' || m=='\n')
{
double_string[index]='\0';
value=strtod(double_string,NULL);
lml_row_vec_double_set(vector,i,value);
i++;
index=0;
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return vector;
}

void lml_row_vec_double_to_csv(lml_row_vec_double *vector,char *csv_file_name)
{
FILE *file;
index_t i;
if(vector==NULL || csv_file_name==NULL) return;
file=fopen(csv_file_name,"w");
if(file==NULL) return;
for(i=0;i<vector->size;i++)
{
fprintf(file,"%lf",vector->data[i]);
if(i==vector->size-1) fputc('\n',file);
else fputc(',',file);
}
fclose(file);
}

