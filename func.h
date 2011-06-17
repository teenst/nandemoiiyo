#include"object.h"


object_t *make_func(object_t *(*func)(object_t*));
object_t *plus_func(object_t* args);

