#include<stdio.h>
#include<stdlib.h>
#include"env.h"
#include"object.h"

void print_object(object_t *object){
  if(object==NULL){
    printf("NIL\n");
    return;
  }
  switch(object ->type){
  case SYM:
    printf("SYM %s\n",object->value.sp);
    break;
  case NUM:
    printf("NUM %d\n",object->value.iv);
    break;
  case CONS:
    print_object(object->value.pair.car);
    print_object(object->value.pair.cdr);
    break;
  default:
    break;
  }
  return;
}

object_t *eval(object_t *object,object_t *env){
  switch(object->type){
  case SYM:
    return env_search(env,object);
  case NUM:
    return object;
    break;
  case CONS:
    break;
  case NIL:
    break;
  default:
    break;
  }
  return (object_t*)NULL;
}
