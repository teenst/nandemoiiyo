#ifndef PARSER_H
#define PARSER_H

typedef struct Object Object;

/* car とcdr */
struct cons{
  Object *car;
  Object *cdr;
};

/* 列挙型でObjecttype*/
enum objecttype{
  SYM,
  NUM,
  CONS,
  NIL,
  ENV,
};
/* 保持のためのノード*/
typedef struct NodeName{
  char *key;
  struct Object *value;
  struct NodeName *right;
  struct NodeName *left;
}Node;

/* オブジェクトの構造体作成 */
struct Object{
  enum objecttype type;
  union {
    char *sp;
    int iv;
    struct cons pair;
    Node *env;
  }value;
};


struct Object *parse_sexp(FILE *);
struct Object *make_num(int);
struct Object *make_sym(const char *);
Node *new_node(Node*,char*);
Node *search(Node* ,char*,Node*(*)(Node*,char*));
struct Object *make_env();
struct Object *env_search(struct Object *,struct Object *);
struct Object *env_set(struct Object *,struct Object *,struct Object *);
void print_object(struct Object *);
struct Object *make_cons(struct Object *, struct Object *);
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
