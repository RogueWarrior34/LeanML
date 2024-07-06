#include<lml_encoder.h>
#include<stdio.h>

int main()
{
int encode_columns[3]={1,4,5};
lml_encoder_one_hot_encoding("insurance.csv","encoded_insurance.csv",encode_columns,3,1);
return 0;
}