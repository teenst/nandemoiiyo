#include<stdlib.h>
#include"object.h"
#include"make_obj.h"

/* 関数オブジェクトの生成 */
object_t *make_func(object_t *(*func)(object_t*)){
  object_t* object = (object_t*)malloc((sizeof(object_t)));

  object->type = FUNC;
  object->value.func = func;
  return object;
}


/* 足し算の実装 */
object_t *plus_func(object_t* args){
  int num=0;
  object_t *tmp=args;

  while(tmp!=NULL){
    num += tmp->value.pair.car->value.iv;
    tmp=tmp->value.pair.cdr;
  }
  return make_num(num);
}

/* かけ算 */
object_t *multiply_func(object_t* args){
  int num=1;
  object_t *tmp=args;

  while(tmp!=NULL){
    num = num * tmp->value.pair.car->value.iv;
    tmp=tmp->value.pair.cdr;
  }
  return make_num(num);
}

