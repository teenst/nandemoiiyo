/* object.h */
#ifndef OBJECT_H
#define OBJECT_H

typedef struct object_tag object_t;
typedef struct node_tag node_t;

/* car とcdr */
typedef struct{
  object_t *car;
  object_t *cdr;
}cons_t;

/* 列挙型でObjecttype*/
enum object_type{
  SYM,
  NUM,
  CONS,
  NIL,
  ENV,
};


/* オブジェクトの構造体作成 */
struct object_tag{
  enum object_type type;
  union {
    char *sp;
    int iv;
    cons_t pair;
    node_t *env;
  }value;
};

void print_object(object_t *object);
object_t *eval(object_t *object,object_t *env);
#endif
