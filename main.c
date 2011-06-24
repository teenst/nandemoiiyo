/* main.c */
#include <stdio.h>
#include "object.h"
#include "make_obj.h"
#include "env.h"
#include "parser.h"
#include "func.h"

void read_eval_print_loop(FILE *fp,object_t *env){
  char buf;
  while((buf=getc(fp))!=EOF){
    ungetc(buf,fp);
    print_object(eval(parse_sexp(fp),env));
  }
}

int main(){
  // eval a to 1
  object_t *env = make_env();
  // for add func
  object_t *symbol; 
  object_t *function;
  
  // add plus func
  symbol=make_sym("+");
  function=make_func(plus_func);
  env_set(env,symbol,function);

  // add multiply func
  symbol=make_sym("*");
  function=make_func(multiply_func);
  env_set(env,symbol,function);
  
  // add subtraction func
  symbol=make_sym("-");
  function=make_func(subtraction_func);
  env_set(env,symbol,function);

  //roop
  read_eval_print_loop(stdin,env);
  return 0;
}
