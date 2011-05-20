// make_obj.h
#ifndef MAKE_OBJ_H
#define MAKE_OBJ_H
#include"object.h"

struct Object *make_num(int);
struct Object *make_sym(const char*);
struct Object *make_cons(struct Object*, struct Object*);

#endif