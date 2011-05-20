// make_obj.c 
#include<stdlib.h>
#include<string.h>
#include"object.h"


struct Object *make_num(int num){
  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = NUM;
  object->value.iv = num;
  return object;
}

struct Object *make_sym(const char *sym){
  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = SYM;
  object->value.sp = strdup(sym);//なにこれ
  return object;
}

struct Object *make_cons(struct Object *car, struct Object *cdr){
  struct Object* tmp_object;
  tmp_object= (struct Object*)malloc(sizeof(struct Object));
  tmp_object->type = CONS;
  tmp_object->value.pair.car =car;
  tmp_object->value.pair.cdr =cdr;
  return tmp_object;
}
