#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
#include"parser.h"
#define BUFFER_SIZE 256




struct Object *make_num(int num){
  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = NUM;
  object->value.iv = num;
  return object;
}
struct Object *make_sym(const char *sym){
  struct Object *object;
  object = malloc(sizeof(struct Object));
  object->type = SYM;
  object->value.sp = strdup(sym);//なにこれ
  return object;
}


Node *new_node(Node* mother,char* name){ //PTSD
  Node *node;
  node = (Node*)malloc(sizeof(Node));
  node->key = name;

  if(mother==NULL){
    return node;
  }
  if(strcmp(mother->key,name)>0){
    mother->left = node;
  }else
    mother->right =node;

  return node;
}


Node *search(Node* node,char *key,Node*(*callback)(Node*,char*)){
  if(node ==NULL){
    return callback ? callback(NULL,key):NULL;
  }
  int diff = strcmp(node->key,key);


  if(diff==0){
    return callback ? callback(node,key):node;
  }
  
  Node* next = (diff >0)?node->left : node->right;
  
  return 
    (next==NULL  && callback) ? callback(node,key): 
    next ? search(next,key,callback): NULL;
}


struct Object *make_env(){
  struct Object *env;
  env = (struct Object *)malloc(sizeof(struct Object));
  env->type = ENV;
  env->value.env = NULL;
  return env;
}


struct Object *env_search(struct Object *env,struct Object *symbol){
  Node *tmp = search(env->value.env,symbol->value.sp,NULL);
  if(tmp == NULL){
    exit(1);
  }
  else
    return tmp->value;
}
struct Object *env_set(struct Object *env,struct Object *symbol,struct Object *value){
  Node *tmp = search(env->value.env,symbol->value.sp,new_node);
  tmp->value = value;

  if(env->value.env ==NULL){
    env->value.env =  tmp;
  }
  return value;
}


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

char skip_space_getchar(FILE *fp){
  char buf;
  do{
    buf = getc(fp);
  }while(isspace(buf));//空白除去
  return buf;
}
  
//SYMのパース
struct Object *parse_sym(FILE *fp){
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
struct Object *parse_num(FILE *fp){
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


struct Object *parse_list_inner(FILE *fp){
  struct cons tmp_cons;
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


struct Object *parse_list(FILE *fp){
  struct cons tmp_cons;
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

struct Object *eval(struct Object *object,struct Object *env){
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
}

struct Object *parse_sexp(FILE *fp){
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
  
}
void read_eval_print_loop(FILE *fp,struct Object *env){
  char buf;
  while((buf=getc(fp))!=EOF){
    ungetc(buf,fp);
    print_object(eval(parse_sexp(fp),env));
    
  }
}


struct Object *parse_program(FILE *fp){
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


int main(){
  struct Object *env = make_env();
  struct Object *symbol=make_sym("a");
  struct Object *number=make_num(1);
  env_set(env,symbol,number);
  
  read_eval_print_loop(stdin,env);

  
  return 0;
}

