#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFER_SIZE (256)

enum tokentype{
  LP,
  RP,
  SYM,
  NUM,
};

struct token{
  enum tokentype type;
  union{
    int ival;
    char *sp;
  }val;
};
void print_token(struct token *);

int main(){
  char buf[BUFFER_SIZE];
  int i,j,tmp_i=0;
  char tmp[BUFFER_SIZE];
  struct token token[200];
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
    if(buf[i]=='\0'){
      break;
    }
  }

  for(j=0;j<token_i;j++){
    print_token(&token[j]);
  }
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
  }
}
