#ifndef MICROPY_INCLUDED_MYMODULE_MYCLASS_H
#define MICROPY_INCLUDED_MYMODULE_MYCLASS_H

#include "py/obj.h"

// Structure for your module's object
typedef struct {
  mp_obj_base_t base;
  bool deinited;
} mymodule_myclass_obj_t;

// Function prototypes for MyClass.c functions
void shared_module_mymodule_myclass_construct(mymodule_myclass_obj_t* self);
void shared_module_mymodule_myclass_deinit(mymodule_myclass_obj_t* self);
bool shared_module_mymodule_myclass_deinited(mymodule_myclass_obj_t* self);
const char * shared_module_mymodule_myclass_get_question(mymodule_myclass_obj_t* self);
mp_int_t shared_module_mymodule_myclass_get_answer(mymodule_myclass_obj_t* self);

#endif // MICROPY_INCLUDED_MYMODULE_MYCLASS_H
