/* parser.h */
#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "object.h"

void print_object(object_t *);
char skip_space_getchar(FILE *);
object_t *parse_sym(FILE *);
object_t *parse_num(FILE *);
object_t *parse_list_inner(FILE *);
object_t *parse_list(FILE *);
object_t *parse_sexp(FILE *);
object_t *parse_program(FILE *);

#endif
