#ifndef __LML__MAT__STRING__
#define __LML__MAT__STRING__
struct __lml_mat_string;
typedef struct __lml_mat_string lml_mat_string;

lml_mat_string * lml_mat_string_create_new(dimension_t rows,dimension_t columns);
void lml_mat_string_destroy(lml_mat_string *matrix);
lml_mat_string * lml_mat_string_from_csv(const char *csv_file_name);
void lml_mat_string_get(lml_mat_string *matrix,index_t row,index_t column,char **string);
void lml_mat_string_set(lml_mat_string *matrix,index_t row,index_t column,char *string);
void lml_mat_string_get_dimensions(lml_mat_string *matrix,dimension_t *rows,dimension_t *columns);

#endif