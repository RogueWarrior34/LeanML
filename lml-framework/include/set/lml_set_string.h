#ifndef __LML__SET__STRING__
#define __LML__SET__STRING__
struct __lml_set_string;
typedef struct __lml_set_string lml_set_string;

lml_set_string * lml_set_string_create_new();
void lml_set_string_destroy(lml_set_string *set);
void lml_set_string_get(lml_set_string *set,index_t index,char **string);
int lml_set_string_add(lml_set_string *set,char *string); //returns -1 if unable or 0 incase of added/not added
dimension_t lml_set_string_get_size(lml_set_string *set);

#endif