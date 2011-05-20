/* parser.h */
#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include "object.h"

Node *new_node(Node*,char*);
Node *search(Node* ,char*,Node*(*)(Node*,char*));

struct Object *make_env();
struct Object *env_search(struct Object *,struct Object *);
struct Object *env_set(struct Object *,struct Object *,struct Object *);
void print_object(struct Object *);
char skip_space_getchar(FILE *);
struct Object *parse_sym(FILE *);
struct Object *parse_num(FILE *);
struct Object *parse_list_inner(FILE *);
struct Object *parse_list(FILE *);
struct Object *eval(struct Object *,struct Object *);
struct Object *parse_sexp(FILE *);
void read_eval_print_loop(FILE *,struct Object *);
struct Object *parse_program(FILE *);

#endif PARSER_H
