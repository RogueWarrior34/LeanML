#include <mlfw_matrix.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
mlfw_mat_double *shuffledMatrix;
mlfw_mat_double *dataset;
mlfw_mat_double *minorMatrix;
mlfw_mat_double *majorMatrix;
dimension_t minorRows;
dimension_t majorRows;
dimension_t shuffledMatrixRows;
dimension_t shuffledMatrixColumns;
char *datasetFile;
char *testFile;
char *trainFile;
int minorPercentage;
index_t r,c;
if(argc!=5)
{
printf("Usage: [create_test_train_dataset dataset test_file train_file minor_percentage]\n");
return 0;
}
datasetFile=argv[1];
testFile=argv[2];
trainFile=argv[3];
minorPercentage=atoi(argv[4]);
if(minorPercentage<=0 || minorPercentage>50)
{
printf("Invalid minor percentage: %d\n",minorPercentage);
return 0;
}
dataset=mlfw_mat_double_from_csv(datasetFile);
if(dataset==NULL) 
{
printf("Unable to load dataset: %s\n",datasetFile);
return 0;
}
/*printf("Original Matrix: \n");
dimension_t datasetRows;
dimension_t datasetColumns;
mlfw_mat_double_get_dimensions(dataset,&datasetRows,&datasetColumns);
for(r=0;r<datasetRows;r++)
{
for(c=0;c<datasetColumns;c++)
{
printf("%20.10lf ",mlfw_mat_double_get(dataset,r,c));
}
printf("\n");
}*/
shuffledMatrix=mlfw_mat_double_shuffle(dataset,3);
if(shuffledMatrix==NULL)
{
printf("Unable to create test/train data files.\n");
mlfw_mat_double_destroy(dataset);
return 0;
}
mlfw_mat_double_get_dimensions(shuffledMatrix,&shuffledMatrixRows,&shuffledMatrixColumns);
minorRows=(dimension_t)((minorPercentage*shuffledMatrixRows)/100);
majorRows=shuffledMatrixRows-minorRows;;
minorMatrix=mlfw_mat_double_create_new(minorRows,shuffledMatrixColumns);
if(minorMatrix==NULL)
{
printf("2 Unable to create test/train data.\n");
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(shuffledMatrix);
return 0;
}
majorMatrix=mlfw_mat_double_create_new(majorRows,shuffledMatrixColumns);
if(majorMatrix==NULL)
{
printf("3 Unable to create test/train data.\n");
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(shuffledMatrix);
mlfw_mat_double_destroy(minorMatrix);
return 0;
}

/*printf("Shuffled Matrix: \n");
for(r=0;r<shuffledMatrixRows;r++)
{
for(c=0;c<shuffledMatrixColumns;c++)
{
printf("%20.10lf ",mlfw_mat_double_get(shuffledMatrix,r,c));
}
printf("\n");
}*/

mlfw_mat_double_copy(minorMatrix,shuffledMatrix,0,0,0,0,minorRows-1,shuffledMatrixColumns-1);
mlfw_mat_double_copy(majorMatrix,shuffledMatrix,0,0,minorRows,0,shuffledMatrixRows-1,shuffledMatrixColumns-1);
mlfw_mat_double_to_csv(minorMatrix,testFile);
mlfw_mat_double_to_csv(majorMatrix,trainFile);

mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(shuffledMatrix);
mlfw_mat_double_destroy(minorMatrix);
mlfw_mat_double_destroy(majorMatrix);
return 0;
}