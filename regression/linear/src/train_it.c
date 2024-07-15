#include <stdio.h>
#include <stdlib.h>
#include <lml_matrix.h>
#include <lml_vector.h>
#include <lml_operations.h>
#include <pthread.h>

//global
uint64_t numberOfIterations=-1;
char *datasetFileName=NULL;
double learningRate=1.0;
dimension_t historySize=0;
char *historyFileName=NULL;
char *parametersFileName=NULL;
char *graphFileName=NULL;
uint32_t stopFlag=0;


void train_it()
{
lml_mat_double *history;
dimension_t historyRows;
dimension_t historyColumns;
index_t historyRow;
index_t historyColumn;
uint64_t k;
lml_mat_double *dataset;
dimension_t datasetRows;
dimension_t datasetColumns;
lml_mat_double *I;
dimension_t IRows, IColumns;
lml_column_vec_double *A;
lml_column_vec_double *M;
lml_column_vec_double *P;
lml_column_vec_double *E;
lml_row_vec_double *ET;
lml_column_vec_double *sum;
lml_mat_double *IT;
lml_column_vec_double *ITE;
lml_column_vec_double *TMP;
lml_column_vec_double *UM;
double squared_sum;
double finalErrorValue;
double iterationNumber;
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
lml_mat_double_copy(I,dataset,0,1,0,0,datasetRows-1,datasetColumns-2);
lml_mat_double_fill(I,0,0,IRows-1,0,1.0);
IT=lml_mat_double_transpose(I);
if(IT==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(I);
return;
}
A=lml_mat_double_create_column_vec(dataset,datasetColumns-1);
if(A==NULL)
{
printf("Unable to create column vector.\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
return;
}
M=lml_column_vec_double_create_new_filled(IColumns,0.0);
if(M==NULL)
{
printf("Low Memory.\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
return;
}
historyRows=historySize;
historyColumns=IColumns+2; //1 extra for iteration Number at 0 index, 1 extra for error value at 1 index
history=lml_mat_double_create_new(historyRows,historyColumns);

if(history==NULL)
{
printf("Low Memory.\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
return;
}
lml_mat_double_fill(history,0,0,historyRows-1,historyColumns-1,0.0);
historyRow=0;
//Op starts
k=1;
while(stopFlag==0)
{
if(k==(numberOfIterations+1)) break;
P=lml_mult_double_mat_cvec(I,M);
if(P==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_mat_double_destroy(history);
return;
}
E=lml_subtract_double_column_vec(P,A);
if(E==NULL)
{
printf("Error in subt\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_mat_double_destroy(history);
return;
}
ET=lml_column_vec_double_transpose(E);
if(ET==NULL)
{
printf("Error in transp\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_mat_double_destroy(history);
return;
}
sum=lml_mult_double_rvec_cvec(ET,E);
if(sum==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_row_vec_double_destroy(ET);
lml_mat_double_destroy(history);
return;
}
//print
squared_sum=lml_column_vec_double_get(sum,0);
finalErrorValue=squared_sum/(2*IRows);
printf("%ld: FinalError: ",k);
printf("%41.15lf\n",finalErrorValue);
iterationNumber=(double)k;
//logic to add to history starts
if(historyRow==historySize)
{
for(i=1;i<historySize;i++)
{
for(j=0;j<historyColumns;j++)
{
lml_mat_double_set(history,i-1,j,lml_mat_double_get(history,i,j));
}
}
historyRow--;
}
lml_mat_double_set(history,historyRow,0,iterationNumber);
lml_mat_double_set(history,historyRow,1,finalErrorValue);
j=lml_column_vec_double_get_size(M);
for(i=0;i<j;i++)
{
lml_mat_double_set(history,historyRow,i+2,lml_column_vec_double_get(M,i));
}
historyRow++;
//logic to add to history ends

//logic to update m and c

ITE=lml_mult_double_mat_cvec(IT,E);
if(ITE==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_row_vec_double_destroy(ET);
lml_column_vec_double_destroy(sum);
lml_mat_double_destroy(history);
return;
}
TMP=lml_mult_double_scalar_cvec((learningRate*(1.0/IRows)),ITE);
if(TMP==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_row_vec_double_destroy(ET);
lml_column_vec_double_destroy(sum);
lml_column_vec_double_destroy(ITE);
lml_mat_double_destroy(history);
return;
}
UM=lml_subtract_double_column_vec(M,TMP);
if(UM==NULL)
{
printf("Error in mult\n");
lml_mat_double_destroy(I);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(IT);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_row_vec_double_destroy(ET);
lml_column_vec_double_destroy(sum);
lml_column_vec_double_destroy(ITE);
lml_column_vec_double_destroy(TMP);
lml_mat_double_destroy(history);
return;
}
lml_column_vec_double_destroy(M);
M=UM;
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(E);
lml_row_vec_double_destroy(ET);
lml_column_vec_double_destroy(sum); //ETE
lml_column_vec_double_destroy(ITE);
lml_column_vec_double_destroy(TMP);
k++;
}//iterations loop ends
lml_mat_double_to_csv(history,historyFileName);
lml_column_vec_double_to_csv(M,parametersFileName);

//release resources
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(M);
lml_mat_double_destroy(IT);
lml_mat_double_destroy(dataset);
lml_mat_double_destroy(I);
lml_mat_double_destroy(history);
}


void * thread_function(void *p)
{
train_it();
return NULL;
}

int main(int argc,char *argv[])
{
pthread_t thread_id;
int result;
char m;
if(argc!=7 && argc!=8)
{
printf("Usage: [train_it.exe dataset_name learning_rate history_size history_file_name parameter_file_name graph_file_name number_of_iterations(optional)]\n");
return 0;
}
datasetFileName=argv[1];
learningRate=strtod(argv[2],NULL);
historySize=(dimension_t)strtoull(argv[3],NULL,10);
if(historySize<5)
{
printf("History size should be greater than 5.\n");
return 0;
}
historyFileName=argv[4];
parametersFileName=argv[5];
graphFileName=argv[6];
if(argc==8) numberOfIterations=strtoull(argv[7],NULL,10);

result=pthread_create(&thread_id,NULL,thread_function,NULL);
if(result!=0)
{
printf("Unable to create thread.\n");
return 0;
}
while(1)
{
m=getchar();
if(m=='\n')
{
stopFlag=1;
break;
}
}
pthread_join(thread_id,NULL);

return 0;
}