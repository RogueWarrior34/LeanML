#include <stdio.h>
#include <stdlib.h>
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
#include <mlfw_operations.h>

void train_it()
{
mlfw_mat_double *dataset;
dimension_t datasetRows;
dimension_t datasetColumns;
mlfw_mat_double *I;
dimension_t IRows, IColumns;
mlfw_column_vec_double *A;
mlfw_column_vec_double *M;
mlfw_column_vec_double *P;
mlfw_column_vec_double *E;
mlfw_row_vec_double *ET;
mlfw_column_vec_double *sum;
double squared_sum;
double finalErrorValue;
dataset=mlfw_mat_double_from_csv("IceCreamSales.csv");
if(dataset==NULL)
{
printf("Unable to load dataset from CSV.\n");
return;
}
mlfw_mat_double_get_dimensions(dataset,&datasetRows,&datasetColumns);
IRows=datasetRows;
IColumns=datasetColumns-1+1;
I=mlfw_mat_double_create_new(IRows,IColumns);
if(I==NULL)
{
printf("Low memory.\n");
mlfw_mat_double_destroy(dataset);
return;
}
mlfw_mat_double_copy(I,dataset,0,1,0,0,datasetRows-1,0);
mlfw_mat_double_fill(I,0,0,IRows-1,0,1.0);
A=mlfw_mat_double_create_column_vec(dataset,1);
if(A==NULL)
{
printf("Unable to create column vector.\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
return;
}
M=mlfw_column_vec_double_create_new_filled(IColumns,0.0);
if(M==NULL)
{
printf("Low Memory.\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
return;
}
//Op starts
P=mlfw_mult_double_mat_cvec(I,M);
if(P==NULL)
{
printf("Error in mult\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(M);
return;
}
E=mlfw_subtract_double_column_vec(P,A);
if(E==NULL)
{
printf("Error in subt\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(P);
return;
}
ET=mlfw_column_vec_double_transpose(E);
if(ET==NULL)
{
printf("Error in transp\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
return;
}
sum=mlfw_mult_double_rvec_cvec(ET,E);
if(sum==NULL)
{
printf("Error in mult\n");
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
return;
}
squared_sum=mlfw_column_vec_double_get(sum,0);
printf("sq.\n");
printf("%20.10lf\n",squared_sum);

finalErrorValue=squared_sum/IRows;
printf("Done.\n");
printf("%20.10lf\n",finalErrorValue);




//release resources
mlfw_column_vec_double_destroy(A);
mlfw_column_vec_double_destroy(M);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(sum);


mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(I);
}

int main()
{
train_it();
return 0;
}