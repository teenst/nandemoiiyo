/* environment.h */
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include"object.h"

object_t *make_env();
object_t *env_search(object_t*,object_t*);
object_t *env_set(object_t*,object_t*,object_t*);

#endif
