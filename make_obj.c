// make_obj.c 
#include<stdlib.h>
#include<string.h>
#include"object.h"

object_t *make_num(int num){
  object_t *object;
  object = malloc(sizeof(object_t));
  object->type = NUM;
  object->value.iv = num;
  return object;
}

object_t *make_sym(const char *sym){
  object_t *object;
  object = malloc(sizeof(object_t));
  object->type = SYM;
  object->value.sp = strdup(sym);//なにこれ
  return object;
}

object_t *make_cons(object_t *car, object_t *cdr){
  object_t* tmp_object;
  tmp_object= (object_t*)malloc(sizeof(object_t));
  tmp_object->type = CONS;
  tmp_object->value.pair.car =car;
  tmp_object->value.pair.cdr =cdr;
  return tmp_object;
}
