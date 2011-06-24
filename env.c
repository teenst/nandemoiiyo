#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"object.h"

struct node_tag{
  char *key;
  object_t *value;
  node_t *right;
  node_t *left;
};

static node_t *new_node(node_t* mother,char* name){
  node_t *node;
  node = (node_t*)malloc(sizeof(node_t));
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

static node_t *search(node_t* node,char *key,node_t*(*callback)(node_t*,char*)){
  if(node == NULL){
    return callback ? callback(NULL,key):NULL;
  }
  int diff = strcmp(node->key,key);

  if(diff==0){
    return callback ? callback(node,key):node;
  }
  
  node_t* next = (diff >0)?node->left : node->right;
  
  return 
    (next==NULL  && callback) ? callback(node,key): 
    next ? search(next,key,callback): NULL;
}

object_t *make_env(){
  object_t *env;
  env = (object_t *)malloc(sizeof(object_t));
  env->type = ENV;
  env->value.env = NULL;
  return env;
}

object_t *env_search(object_t *env,object_t *symbol){
  node_t *tmp = search(env->value.env,symbol->value.sp,NULL);
  if(tmp == NULL){
    printf("安心してください．\n");
    exit(1);
  }
  else
    return tmp->value;
}

object_t *env_set(object_t *env,object_t *symbol,object_t *value){
  node_t *tmp = search(env->value.env,symbol->value.sp,new_node);
  tmp->value = value;

  if(env->value.env ==NULL){
    env->value.env =  tmp;
  }
  return value;
}

