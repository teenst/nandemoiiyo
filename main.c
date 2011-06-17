/* main.c */
#include <stdio.h>
#include "object.h"
#include "make_obj.h"
#include "env.h"
#include "parser.h"

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
  /* object_t *symbol=make_sym("a"); */
  /* object_t *number=make_num(1); */
  /* env_set(env,symbol,number); */

  //roop
  read_eval_print_loop(stdin,env);
  return 0;
}
