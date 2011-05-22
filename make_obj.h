// make_obj.h
#ifndef MAKE_OBJ_H
#define MAKE_OBJ_H
#include"object.h"

object_t *make_num(int);
object_t *make_sym(const char*);
object_t *make_cons(object_t*, object_t*);

#endif
