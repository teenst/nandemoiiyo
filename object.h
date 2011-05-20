/* object.h */
#ifndef OBJECT_H
#define OBJECT_H

typedef struct Object Object;

/* car とcdr */
struct cons{
  Object *car;
  Object *cdr;
};

/* 列挙型でObjecttype*/
enum objecttype{
  SYM,
  NUM,
  CONS,
  NIL,
  ENV,
};

/* 保持のためのノード*/
typedef struct NodeName{
  char *key;
  struct Object *value;
  struct NodeName *right;
  struct NodeName *left;
}Node;

/* オブジェクトの構造体作成 */
struct Object{
  enum objecttype type;
  union {
    char *sp;
    int iv;
    struct cons pair;
    Node *env;
  }value;
};
#endif