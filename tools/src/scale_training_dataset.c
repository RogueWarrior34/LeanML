#include<lml_scale.h>
#include<lml_matrix.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
char *inputFileName;
char *outputFileName;
char *minMaxFile;
index_t fromColumn;
index_t toColumn;
lml_mat_double *inputMatrix;
lml_mat_double *outputMatrix;
dimension_t inputMatrixRows;
dimension_t inputMatrixColumns;
if(argc!=6)
{
printf("Usage: [scale_training_dataset.out input_file_name output_file_name from_column to_column min_max_file]\n");
return 0;
}
inputFileName=argv[1];
outputFileName=argv[2];
fromColumn=atoi(argv[3]);
toColumn=atoi(argv[4]);
minMaxFile=argv[5];
inputMatrix=lml_mat_double_from_csv(inputFileName);
if(inputMatrix==NULL)
{
printf("Error in loading input file.\n");
return 0;
}
lml_mat_double_get_dimensions(inputMatrix,&inputMatrixRows,&inputMatrixColumns);
outputMatrix=lml_scale_double_min_max(inputMatrix,0,fromColumn,inputMatrixRows-1,toColumn,minMaxFile);
if(outputMatrix==NULL)
{
printf("Error in scaling.\n");
lml_mat_double_destroy(inputMatrix);
return 0;
}
lml_mat_double_to_csv(outputMatrix,outputFileName);
lml_mat_double_destroy(inputMatrix);
lml_mat_double_destroy(outputMatrix);
return 0;
}