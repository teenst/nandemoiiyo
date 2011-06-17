/* parser.c */
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<ctype.h>
#include"object.h"
#include"make_obj.h"
#include"parser.h"
#include"env.h"

#define BUFFER_SIZE 256


char skip_space_getchar(FILE *fp){
  char buf;
  do{
    buf = getc(fp);
  }while(isspace(buf));//空白除去
  return buf;
}
  
//SYMのパース
object_t *parse_sym(FILE *fp){
  int i=0;
  char buf;
  char tmp[BUFFER_SIZE];
  buf=skip_space_getchar(fp);
 
  while(isalpha(buf)){
    tmp[i]=buf;    
    buf = getc(fp);
    i++;
  }
  tmp[i]='\0';
  ungetc(buf,fp);

  return make_sym(tmp);
}

//NUMのパース
object_t *parse_num(FILE *fp){
  int i=0;
  char buf;
  char tmp[BUFFER_SIZE];
  buf=skip_space_getchar(fp); 
  
  while(isdigit(buf)){
    tmp[i]=buf;    
    buf = getc(fp);
    i++;
  }
  tmp[i]='\0';
  ungetc(buf,fp);

  return make_num(atoi(tmp));
}

object_t *parse_list_inner(FILE *fp){
  cons_t tmp_cons;
  char buf;
  buf=skip_space_getchar(fp);   

  ungetc(buf,fp);
  
  tmp_cons.car = parse_sexp(fp);
  buf=skip_space_getchar(fp);   


  if(buf == ')'){
    tmp_cons.cdr = NULL;
  }
  else{
    ungetc(buf,fp);
    tmp_cons.cdr = parse_list_inner(fp);
  }
  
  return make_cons(tmp_cons.car,tmp_cons.cdr);
}


object_t *parse_list(FILE *fp){
  cons_t tmp_cons;
  char buf;
  buf=skip_space_getchar(fp);


  tmp_cons.car = parse_sexp(fp);
  buf=skip_space_getchar(fp);

  if(buf == ')'){
    tmp_cons.cdr = NULL;
  }
  else{
    ungetc(buf,fp);
    tmp_cons.cdr = parse_list_inner(fp);
  }
  
  return make_cons(tmp_cons.car,tmp_cons.cdr);
}


object_t *parse_sexp(FILE *fp){
  char buf;
  buf=skip_space_getchar(fp);

  ungetc(buf,fp);

  if(isalpha(buf)){
    return parse_sym(fp);
  }
  else if(isdigit(buf)){
    return parse_num(fp);
  }
  else if(buf=='('){
    return parse_list(fp);
  }
  return (object_t*)NULL;
}


object_t *parse_program(FILE *fp){
  char  buf; 
  
  buf = getc(fp);
  
  if(buf==EOF){
    return NULL;
  }

  else{
    ungetc(buf,fp);
    return  parse_sexp(fp);
  }
}
