/* main.c */
#include <stdio.h>
#include "object.h"
#include "make_obj.h"
#include "parser.h"

int main(){

  // eval a to 1
  struct Object *env = make_env();
  struct Object *symbol=make_sym("a");
  struct Object *number=make_num(1);
  env_set(env,symbol,number);

  //roop
  read_eval_print_loop(stdin,env);
  return 0;
}

