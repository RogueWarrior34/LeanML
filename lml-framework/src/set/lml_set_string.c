#include<lml_set.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct __lml_set_string
{
char **data;
dimension_t size;
}lml_set_string;

lml_set_string * lml_set_string_create_new()
{
lml_set_string *set;
set=(lml_set_string *)malloc(sizeof(lml_set_string));
if(set==NULL) return NULL;
set->data=NULL;
set->size=0;
return set;
}

void lml_set_string_destroy(lml_set_string *set)
{
index_t i;
if(set==NULL) return;
for(i=0;i<set->size;i++)
{
free(set->data[i]);
}
if(set->data!=NULL) free(set->data);
free(set);
}

void lml_set_string_get(lml_set_string *set,index_t index,char **string)
{
if(string==NULL) return;
if(set==NULL)
{
*string=NULL;
return;
}
if(index<0 || index>=set->size)
{
*string=NULL;
return;
}
*string=(char *)malloc(sizeof(char)*(strlen(set->data[index])+1));
if(*string!=NULL)
{
strcpy(*string,set->data[index]);
}
}

int lml_set_string_add(lml_set_string *set,char *string)
{
index_t i;
char *str;
char **tmp;
if(set==NULL || string==NULL) return -1;
if(set->size==0)
{
set->data=(char **)malloc(sizeof(char *)*1);
if(set->data==NULL) return -1;
set->data[0]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(set->data[0]==NULL)
{
free(set->data);
set->data=NULL;
return -1;
}
strcpy(set->data[0],string);
set->size++;
return 0;
}
else
{
for(i=0;i<set->size;i++)
{
if(strcmp(set->data[i],string)==0)
{
return 0;
}
}
str=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(str==NULL) return -1;
strcpy(str,string);
tmp=(char **)realloc(set->data,sizeof(char *)*(set->size+1));
if(tmp==NULL) 
{
free(str);
return -1;
}
set->data=tmp;
set->data[set->size]=str;
set->size++;
return 0;
}
}

dimension_t lml_set_string_get_size(lml_set_string *set)
{
if(set==NULL) return 0;
return set->size;
}
