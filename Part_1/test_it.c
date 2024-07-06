#include <stdio.h>
#include <stdlib.h>
#include <lml_matrix.h>
#include <lml_vector.h>
#include <lml_operations.h>
#include <pthread.h>

//global

char *datasetFileName=NULL;
char *resultFileName=NULL;
char *parametersFileName=NULL;


void test_it()
{
FILE *resultsFile;
FILE *historyFile;
lml_mat_double *dataset;
dimension_t datasetRows;
dimension_t datasetColumns;
lml_mat_double *I;
dimension_t IRows, IColumns;
lml_column_vec_double *M;
lml_column_vec_double *P;
index_t r,c,i,j;

dataset=lml_mat_double_from_csv(datasetFileName);
if(dataset==NULL)
{
printf("Unable to load dataset from %s.\n",datasetFileName);
return;
}
lml_mat_double_get_dimensions(dataset,&datasetRows,&datasetColumns);
IRows=datasetRows;
IColumns=datasetColumns-1+1;
I=lml_mat_double_create_new(IRows,IColumns);
if(I==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
return;
}
lml_mat_double_copy(I,dataset,0,1,0,0,datasetRows-1,datasetColumns-1);
lml_mat_double_fill(I,0,0,IRows-1,0,1.0);

M=lml_column_vec_double_from_csv(parametersFileName);
if(M==NULL)
{
printf("Can't load parameters file.\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
return;
}

P=lml_mult_double_mat_cvec(I,M);
if(P==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(M);
return;
}

resultsFile=fopen(resultFileName,"w");
//fprintf(resultsFile,"input(1),    actual_output,     predicted_output\n");
for(r=0;r<datasetRows;r++)
{
for(c=datasetColumns-1;c<datasetColumns;c++)
{
fprintf(resultsFile,"%lf,",lml_mat_double_get(dataset,r,c));
}
fprintf(resultsFile,"%lf\n",lml_column_vec_double_get(P,r));
}

fclose(resultsFile);


//release resources
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(I);
}



int main(int argc,char *argv[])
{

if(argc!=4)
{
printf("Usage: [test_it.exe dataset_name parameters_file_name results_file_name]\n");
return 0;
}
datasetFileName=argv[1];
parametersFileName=argv[2];
resultFileName=argv[3];
test_it();
printf("Results are stored in %s.\n",resultFileName);
return 0;
}