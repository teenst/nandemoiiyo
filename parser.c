#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
#define BUFFER_SIZE 256

typedef struct Object Object;
struct cons{
  Object *car;
  Object *cdr;
};

enum objecttype{
  SYM,
  NUM,
  CONS,
  NIL,
};

struct Object{
  enum objecttype type;
  union {
    char *sp;
    int iv;
    struct cons pair;
  }value;
};


struct Object *parse_sexp(FILE *);




void print_object(struct Object *object){
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

struct Object *make_cons(struct Object *car, struct Object *cdr){
    struct Object* tmp_object;
    tmp_object= (struct Object*)malloc(sizeof(struct Object));
    tmp_object->type = CONS;
    tmp_object->value.pair.car =car;
    tmp_object->value.pair.cdr =cdr;
    return tmp_object;
  }

//SYMのパース
struct Object *parse_sym(FILE *fp){
  int i=0;
  char buf;
  char tmp[BUFFER_SIZE];
  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去
  
  while(isalpha(buf)){
    tmp[i]=buf;    
    buf = getc(fp);
    i++;
  }
  tmp[i]='\0';
  ungetc(buf,fp);

  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = SYM;
  object->value.sp = strdup(tmp);//なにこれ
    
  return object;
}

//NUMのパース
struct Object *parse_num(FILE *fp){
  int i=0;
  char buf;
  char tmp[BUFFER_SIZE];
  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去
  
  while(isdigit(buf)){
    tmp[i]=buf;    
    buf = getc(fp);
    i++;
  }
  tmp[i]='\0';
  ungetc(buf,fp);

  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = NUM;
  object->value.iv = atoi(tmp);

  return object;
}

struct Object *parse_list_inner(FILE *fp){
  struct cons tmp_cons;
  char buf;
  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去と先頭の'('の除去
  ungetc(buf,fp);
  
  tmp_cons.car = parse_sexp(fp);

  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去

  if(buf == ')'){
    tmp_cons.cdr = NULL;
  }
  else{
    ungetc(buf,fp);
    tmp_cons.cdr = parse_list_inner(fp);
  }
  
  return make_cons(tmp_cons.car,tmp_cons.cdr);
}


struct Object *parse_list(FILE *fp){
  struct cons tmp_cons;
  char buf;
  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去と先頭の'('の除去

  tmp_cons.car = parse_sexp(fp);

  do{
    buf = getc(fp);
  }while(buf==' ');//空白除去

  if(buf == ')'){
    tmp_cons.cdr = NULL;
  }
  else{
    ungetc(buf,fp);
    tmp_cons.cdr = parse_list_inner(fp);
  }
  
  return make_cons(tmp_cons.car,tmp_cons.cdr);
}


struct Object *parse_sexp(FILE *fp){
  char buf;
  do{
    buf = getc(fp);
  }while(buf==' ');

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
  
}




void parse_program(FILE *fp){
  char  buf; 
  
  buf = getc(fp);
  
  if(buf==EOF){
    return;
  }

  else{
    ungetc(buf,fp);
    print_object(parse_sexp(fp));
  }
}


int main(){

  parse_program(stdin);
  
  return 0;
}


