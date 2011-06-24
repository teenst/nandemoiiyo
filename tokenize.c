#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE (256)

typedef struct Atom Atom;


struct cons{
  Atom *car;
  Atom *cdr;
};

enum atomtype{
  A_SYM,
  A_NUM,
  CONS,
  NIL,
};

struct Atom{
  enum atomtype type;
  union {
    char *sp; //文字
    int iv; //数字
    struct cons pair; //括弧
  }value;
};



enum tokentype{
  LP,
  RP,
  SYM,
  NUM,
  TEOF,
};

  

struct token{
  enum tokentype type;
  union{
    int ival;
    char *sp;
  }val;
};


enum type{
  
};



struct object{
  enum type type;
  union{
    int num;
    char *cp;
  }val;
};

struct token token[200];
struct Atom *atom[20];
struct Atom *get_atom();
struct Atom *make_sym_atom(struct token);
struct Atom *make_num_atom(struct token);
struct Atom *get_cons();
struct Atom *make_cons(struct Atom *,struct Atom *);
void print_atom(struct Atom *);
void print_token(struct token *);
int token_place=0;

object * parse_s_expr(*);

void get_program(){
  int i;
  for(i=0;i<20;i++){
    if(token[token_place].type ==TEOF){
      return;
    }
    else{
     atom[i] = get_atom();
     print_atom(atom[i]);
    }
  }
}

struct Atom *get_atom(){
  struct token *tmp_token;
  tmp_token=&token[token_place];
  print_token(tmp_token);
  token_place++;
  switch(tmp_token->type){
  case NUM:
    return make_num_atom(*tmp_token);
    break;
  case SYM:
    return make_sym_atom(*tmp_token);
    break;
  case LP:
    return get_cons();
    break;
  case RP:
    return NULL;
    break;
  default:
    return NULL;
  }
}

struct Atom *make_sym_atom(struct token t){
  struct Atom* tmp_atom;
  tmp_atom= (struct Atom*)malloc(sizeof(struct Atom));
  tmp_atom->type = A_SYM;
  tmp_atom->value.sp = t.val.sp;
  return tmp_atom;
}

struct Atom *make_num_atom(struct token t){
  struct Atom* tmp_atom;
  tmp_atom= (struct Atom*)malloc(sizeof(struct Atom));
  tmp_atom->type = A_NUM;
  tmp_atom->value.iv = t.val.ival;
  return tmp_atom;
}

struct Atom *get_cons(){
  struct cons tmp_cons;
  tmp_cons.car = get_atom();
  if(token[token_place].type == RP){
    tmp_cons.cdr = NULL;
    token_place++;
  }
  else{
    tmp_cons.cdr = get_cons();
  }
  return make_cons(tmp_cons.car,tmp_cons.cdr);
}

struct Atom *make_cons(struct Atom *car, struct Atom *cdr){
  struct Atom* tmp_atom;
  tmp_atom= (struct Atom*)malloc(sizeof(struct Atom));
  tmp_atom->type = CONS;
  tmp_atom->value.pair.car =car;
  tmp_atom->value.pair.cdr =cdr;
  return tmp_atom;
}


int main(){
  char buf[BUFFER_SIZE];
  int i,j,tmp_i=0;
  char tmp[BUFFER_SIZE];
  int token_i=0; 

  fgets(buf,BUFFER_SIZE,stdin);
  for(i=0;i<BUFFER_SIZE;i++){
    if(buf[i]=='('){
      token[token_i].type = LP;
      token_i++;
    }
    else if(buf[i]==')'){
      token[token_i].type = RP;
      token_i++;
    }
    else if(isalpha(buf[i])){
      tmp[tmp_i]=buf[i];
      if(isalpha(buf[i+1])){
        tmp_i++;
      }
      else{
        size_t tmp_size = sizeof(char)*(tmp_i+2);
        tmp[tmp_i+1] = '\0';
        token[token_i].type = SYM;        
        token[token_i].val.sp = malloc(tmp_size);
        memcpy(token[token_i].val.sp,tmp, tmp_size);
        tmp_i=0;
        token_i++;
      }
    }
    else if(isdigit(buf[i])){
      tmp[tmp_i]=buf[i];
      if(isdigit(buf[i+1])){
        tmp_i++;
      }
      else{
        tmp[tmp_i+1] = '\0';
        token[token_i].type = NUM;
        sscanf(tmp,"%d",&token[token_i].val.ival);
        tmp_i=0;
        token_i++;
      }       
    }
    else if(buf[i]=='\0'){
      break;
    }
  }
  token[token_i++].type = TEOF;
  for(j=0;j<token_i;j++){
    print_token(&token[j]);
  }
  get_program();
  return 0;
}

void print_token(struct token *token){
  switch(token->type){
  case LP:
    printf("LP (\n");
    break;
  case RP:
    printf("RP )\n");
    break;
  case SYM:
    printf("SYM %s\n",token->val.sp);
    break;
  case NUM:
    printf("NUM %d\n",token->val.ival);
    break;
  default:
    break;
  }
}

void print_atom(struct Atom *atom){
  if(atom==NULL){
    printf("NIL\n");
    return;
  }
  switch(atom ->type){
  case A_SYM:
    printf("A_SYM %s\n",atom->value.sp);
    break;
  case A_NUM:
    printf("A_NUM %d\n",atom->value.iv);
    break;
  case CONS:
    print_atom(atom->value.pair.car);
    print_atom(atom->value.pair.cdr);
    break;
  default:
    break;
  }
  return;
}

