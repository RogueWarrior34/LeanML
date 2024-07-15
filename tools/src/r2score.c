#include <stdio.h>
#include <stdlib.h>
#include <lml_matrix.h>
#include <lml_vector.h>
#include <lml_operations.h>

void score_it(char *resultsFileName)
{
lml_mat_double *dataset;
lml_column_vec_double *A;
lml_column_vec_double *P;
lml_column_vec_double *R; //A-P
lml_row_vec_double *RT; //R transposed
lml_column_vec_double *RTR; // R*RT
lml_column_vec_double *AM; //mean of A
lml_column_vec_double *J; //A-AM
lml_row_vec_double *JT; //J transposed
lml_column_vec_double *JTJ; //J*JT
double SSR;
double SST;
double mean;
double R2Score;
dimension_t datasetRows;
dimension_t datasetColumns;
dataset=lml_mat_double_from_csv(resultsFileName);
if(dataset==NULL)
{
printf("Unable to load the file: %s\n",resultsFileName);
return;
}
lml_mat_double_get_dimensions(dataset,&datasetRows,&datasetColumns);

A=lml_mat_double_create_column_vec(dataset,datasetColumns-2); //Vector of Actual values
if(A==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
return;
}
P=lml_mat_double_create_column_vec(dataset,datasetColumns-1); //Vector of Predicted values
if(P==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
return;
}
R=lml_subtract_double_column_vec(A,P);
if(R==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
return;
}
RT=lml_column_vec_double_transpose(R);
if(RT==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
return;
}
RTR=lml_mult_double_rvec_cvec(RT,R);
if(RTR==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
return;
}
mean=lml_column_vec_double_get_mean(A);
AM=lml_column_vec_double_create_new_filled(datasetRows,mean);
if(AM==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
lml_column_vec_double_destroy(RTR);
return;
}
J=lml_subtract_double_column_vec(A,AM);
if(J==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
lml_column_vec_double_destroy(RTR);
lml_column_vec_double_destroy(AM);
return;
}
JT=lml_column_vec_double_transpose(J);
if(JT==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
lml_column_vec_double_destroy(RTR);
lml_column_vec_double_destroy(AM);
lml_column_vec_double_destroy(J);
return;
}
JTJ=lml_mult_double_rvec_cvec(JT,J);
if(JTJ==NULL)
{
printf("Low memory.\n");
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
lml_column_vec_double_destroy(RTR);
lml_column_vec_double_destroy(AM);
lml_column_vec_double_destroy(J);
lml_row_vec_double_destroy(JT);
return;
}
SSR=lml_column_vec_double_get(RTR,0);
SST=lml_column_vec_double_get(JTJ,0);
R2Score=1-(SSR/SST);
printf("R2Score of the results: %lf\n",R2Score);


//release memory
lml_mat_double_destroy(dataset);
lml_column_vec_double_destroy(A);
lml_column_vec_double_destroy(P);
lml_column_vec_double_destroy(R);
lml_row_vec_double_destroy(RT);
lml_column_vec_double_destroy(RTR);
lml_column_vec_double_destroy(AM);
lml_column_vec_double_destroy(J);
lml_row_vec_double_destroy(JT);
lml_column_vec_double_destroy(JTJ);
}


int main(int argc, char *argv[])
{
if(argc!=2)
{
printf("Usage : [score_it.out results_file_name]\n");
return 0;
}
score_it(argv[1]);
return 0;
}