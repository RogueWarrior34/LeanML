#include<lml_matrix.h>
#include<lml_set.h>
#include<lml_encoder.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void lml_encoder_one_hot_encoding(char *source,char *target,int *encode_columns,int size,int header_exists)
{
FILE *targetFile;
lml_mat_string *matrix;
lml_set_string **sets;
char *string;
char *setString;
dimension_t setSize;
index_t r;
index_t dataStartRowIndex;
index_t i;
index_t c;
index_t j;
dimension_t matrixRows,matrixColumns;
if(source==NULL || target==NULL || encode_columns==NULL || size<=0) return;
matrix=lml_mat_string_from_csv(source);
lml_mat_string_get_dimensions(matrix,&matrixRows,&matrixColumns);
for(i=0;i<size;i++)
{
c=encode_columns[i];
if(c<0 || c>=matrixColumns)
{
lml_mat_string_destroy(matrix);
return;
}
}
sets=(lml_set_string **)malloc(sizeof(lml_mat_string *)*size);
if(sets==NULL)
{
lml_mat_string_destroy(matrix);
return;
}
for(i=0;i<size;i++)
{
sets[i]=lml_set_string_create_new();
if(sets[i]==NULL)
{
for(j=0;j<i;j++) lml_set_string_destroy(sets[j]);
free(sets);
lml_mat_string_destroy(matrix);
return;
}
}
if(header_exists) dataStartRowIndex=1;
else dataStartRowIndex=0;
for(r=dataStartRowIndex;r<matrixRows;r++)
{
for(i=0;i<size;i++)
{
c=encode_columns[i];
lml_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(j=0;j<i;j++) lml_set_string_destroy(sets[j]);
free(sets);
lml_mat_string_destroy(matrix);
return;
}
else
{
if(lml_set_string_add(sets[i],string)==-1)
{
free(string);
for(j=0;j<i;j++) lml_set_string_destroy(sets[j]);
free(sets);
lml_mat_string_destroy(matrix);
return;
}
free(string);
}
}
}

//code to test the contents of the sets
/*for(i=0;i<size;i++)
{
setSize=lml_set_string_get_size(sets[i]);
for(j=0;j<setSize;j++)
{
lml_set_string_get(sets[i],j,&string);
if(string!=NULL)
{
printf("%s\n",string);
free(string);
}
}
}*/

//logic to create encoded file
targetFile=fopen(target,"w");
if(targetFile==NULL)
{
for(i=0;i<size;i++) lml_set_string_destroy(sets[i]);
free(sets);
lml_mat_string_destroy(matrix);
return;
}
if(header_exists)
{
for(c=0;c<matrixColumns;c++)
{
lml_mat_string_get(matrix,0,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) lml_set_string_destroy(sets[i]);
free(sets);
lml_mat_string_destroy(matrix);
fclose(targetFile);
targetFile=fopen(target,"w"); //create a blank file
fclose(targetFile);
return;
}
for(i=0;i<size;i++) 
{
if(c==encode_columns[i]) break;
}
if(i<size)
{
setSize=lml_set_string_get_size(sets[i]);
for(j=0;j<setSize;j++)
{
lml_set_string_get(sets[i],j,&setString);
if(setString==NULL)
{
for(r=0;r<size;r++) lml_set_string_destroy(sets[r]);
free(sets);
lml_mat_string_destroy(matrix);
fclose(targetFile);
targetFile=fopen(target,"w"); //create a blank file
fclose(targetFile);
free(string);
return;
}
fputs(string,targetFile);
fputc('_',targetFile);
fputs(setString,targetFile);
free(setString);
if(j<setSize-1) fputc(',',targetFile);
}
}
else
{
fputs(string,targetFile);
}
free(string);
if(c==matrixColumns-1) fputc('\n',targetFile);
else fputc(',',targetFile);
}
}//header part ends
//encode data
for(r=dataStartRowIndex;r<matrixRows;r++)
{
for(c=0;c<matrixColumns;c++)
{
lml_mat_string_get(matrix,r,c,&string);
if(string==NULL)
{
for(i=0;i<size;i++) lml_set_string_destroy(sets[i]);
free(sets);
lml_mat_string_destroy(matrix);
fclose(targetFile);
targetFile=fopen(target,"w"); //create a blank file
fclose(targetFile);
return;
}
for(i=0;i<size;i++) 
{
if(c==encode_columns[i]) break;
}
if(i<size)
{
setSize=lml_set_string_get_size(sets[i]);
for(j=0;j<setSize;j++)
{
lml_set_string_get(sets[i],j,&setString);
if(setString==NULL)
{
for(r=0;r<size;r++) lml_set_string_destroy(sets[r]);
free(sets);
lml_mat_string_destroy(matrix);
fclose(targetFile);
targetFile=fopen(target,"w"); //create a blank file
fclose(targetFile);
free(string);
return;
}
if(strcmp(string,setString)==0) fputc('1',targetFile);
else fputc('0',targetFile);
free(setString);
if(j<setSize-1) fputc(',',targetFile);
}
}
else
{
fputs(string,targetFile);
}
free(string);
if(c==matrixColumns-1) fputc('\n',targetFile);
else fputc(',',targetFile);
}
}
fclose(targetFile);
}