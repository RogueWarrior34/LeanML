#include<lml_encoder.h>
#include<stdio.h>
#include<stdlib.h>


int main(int argc,char *argv[])
{
int *encodeColumns;
dimension_t size;
char *s;
char *e;
char *columnString;
char *inputFileName;
char *outputFileName;
char hasHeader;
int headerExists;
index_t i;
if(argc!=5)
{
printf("[Usage: encode_dataset.out input_file_name output_file_name columns_to_encode has_header(y/n)]\n");
return 0;
}
inputFileName=argv[1];
outputFileName=argv[2];
columnString=argv[3];
hasHeader=argv[4][0];
if(hasHeader=='y' || hasHeader=='Y') headerExists=1;
else if(hasHeader=='n' || hasHeader=='N') headerExists=0;
else 
{
printf("Invalid input\n");
return 0;
}
size=0;
for(i=0;columnString[i]!='\0';i++)
{
if(columnString[i]==',') size++;
}
size++;
encodeColumns=(int *)malloc(sizeof(int)*size);
if(encodeColumns==NULL)
{
printf("Low memory.\n");
return 0;
}
i=0;
s=columnString;
while(1)
{
e=s+1;
while(*e!='\0' && *e!=',') e++;
if(*e=='\0')
{
encodeColumns[i]=atoi(s);
break;
}
else
{
*e='\0';
encodeColumns[i]=atoi(s);
i++;
s=e+1;
}
}
/*
printf("Size: %u\n",size);
for(i=0;i<size;i++)
{
printf("%u\n",encodeColumns[i]);
}*/
lml_encoder_one_hot_encoding(inputFileName,outputFileName,encodeColumns,size,headerExists);
free(encodeColumns);
return 0;
}