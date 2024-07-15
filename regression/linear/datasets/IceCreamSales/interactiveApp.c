#include <lml_matrix.h>
#include <lml_vector.h>
#include <lml_operations.h>
#include <stdio.h>
#include <stdio_ext.h>

int main()
{
double tempC;
double tempF;
double profit;
lml_column_vec_double *paramsVector;
lml_row_vec_double *featuresVector;
lml_column_vec_double *predictedVector;
FILE *file;
printf("----------------------------------------------\n");
printf("      Ice Cream Sales Profit Predictor      \n");
printf("----------------------------------------------\n");
file=fopen("parameters.csv","r");
if(file==NULL)
{
printf("parameters.csv does not exist.\n");
return 0;
}
printf("Enter temperature(in Celsius):- ");
scanf("%lf",&tempC);
__fpurge(stdin);
tempF=(tempC*(9.0/5.0))+32.0;
featuresVector=lml_row_vec_double_create_new(2);
if(featuresVector==NULL)
{
printf("Low memory.\n");
return 0;
}
lml_row_vec_double_set(featuresVector,0,1.0); //bias
lml_row_vec_double_set(featuresVector,1,tempF);
paramsVector=lml_column_vec_double_from_csv("parameters.csv");
if(paramsVector==NULL)
{
lml_row_vec_double_destroy(featuresVector);
printf("Low memory.\n");
return 0;
}
predictedVector=lml_mult_double_rvec_cvec(featuresVector,paramsVector);
if(predictedVector==NULL)
{
lml_row_vec_double_destroy(featuresVector);
lml_column_vec_double_destroy(paramsVector);
printf("Low memory.\n");
return 0;
}
profit=lml_column_vec_double_get(predictedVector,0);
lml_row_vec_double_destroy(featuresVector);
lml_column_vec_double_destroy(paramsVector);
lml_column_vec_double_destroy(predictedVector);
printf("Expected profit:- %10.2lf\n",profit);
return 0;
}