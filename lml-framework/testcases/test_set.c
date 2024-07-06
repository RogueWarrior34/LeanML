#include<lml_set.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
lml_set_string *set;
dimension_t size;
index_t i;
char *str;
set=lml_set_string_create_new();
lml_set_string_add(set,"good");
lml_set_string_add(set,"bad");
lml_set_string_add(set,"Good");
lml_set_string_add(set,"good");
lml_set_string_add(set,"sat");
size=lml_set_string_get_size(set);
printf("Size of set is %u.\n",size);
for(i=0;i<size;i++)
{
lml_set_string_get(set,i,&str);
if(str!=NULL) 
{
printf("%s\n",str);
free(str);
}
}
printf("1\n");
lml_set_string_destroy(set);
printf("2\n");
return 0;
}