/* object.c */
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
  object_t *tmp,*args,*func,*head,*pre;

  switch(object->type){
  case SYM:
    return env_search(env,object);
  case NUM:
    return object;
    break;
  case CONS:
    tmp =object;
    func = eval(tmp->value.pair.car,env);
    
    tmp = tmp->value.pair.cdr;
    if(tmp==NULL){
      head = NULL;
    }
    else{
      args = malloc(sizeof(object_t));
      args->type = CONS;
      head = args;
      while(tmp!=NULL){
        args->value.pair.car = eval(tmp->value.pair.car,env);
        pre = args;
        args = malloc(sizeof(object_t));
        args ->type =CONS;
        pre->value.pair.cdr = args;
        tmp = tmp->value.pair.cdr;
      }
      free(args);
      pre->value.pair.cdr = NULL;
    }
    
    return func->value.func(head);
    
    /*     /\* listから要素を取り出す   *\/ */
    /* tmp = object; */
    /* for(i=0;i<3;i++){ */
    /*   args[i] = tmp->value.pair.car; */
    /*   tmp = tmp->value.pair.cdr; */
    /* } */
    /* if(!strcmp(args[0]->value.sp,"setq")){ */
    /*   return env_set(env,args[1],args[2]); */
    /* } */
        
    break;
  case NIL:
    break;
  default:
    break;
  }
  return (object_t*)NULL;
}
