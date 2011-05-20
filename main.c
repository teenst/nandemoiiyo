/* main.c */
#include<stdio.h>
#include "parser.h"
#include "object.h"

int main(){
  struct Object *env = make_env();
  struct Object *symbol=make_sym("a");
  struct Object *number=make_num(1);
  env_set(env,symbol,number);
  
  read_eval_print_loop(stdin,env);

  
  return 0;
}

