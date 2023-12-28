#include <stdint.h>
#include <string.h>
#include "shared/runtime/context_manager_helpers.h"
#include "py/objproperty.h"
#include "py/runtime.h"
#include "py/runtime0.h"
#include "shared-bindings/mymodule/MyClass.h"
#include "shared-bindings/util.h"

// Forward declarations from the implementation in shared-module
extern void shared_module_mymodule_myclass_construct(mymodule_myclass_obj_t* self);
extern void shared_module_mymodule_myclass_deinit(mymodule_myclass_obj_t* self);
extern bool shared_module_mymodule_myclass_deinited(mymodule_myclass_obj_t* self);
extern const char * shared_module_mymodule_myclass_get_question(mymodule_myclass_obj_t* self);
extern mp_int_t shared_module_mymodule_myclass_get_answer(mymodule_myclass_obj_t* self);

// Constructor
STATIC mp_obj_t mymodule_myclass_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *all_args) {
    mymodule_myclass_obj_t *self = m_new_obj(mymodule_myclass_obj_t);
    self->base.type = type;
    shared_module_mymodule_myclass_construct(self);
    return MP_OBJ_FROM_PTR(self);
}

// Deinitializer
STATIC mp_obj_t mymodule_myclass_deinit(mp_obj_t self_in) {
    mymodule_myclass_obj_t *self = MP_OBJ_TO_PTR(self_in);
    shared_module_mymodule_myclass_deinit(self);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mymodule_myclass_deinit_obj, mymodule_myclass_deinit);

// Define property accessors for 'answer'
STATIC mp_obj_t mymodule_myclass_answer_getter(mp_obj_t self_in) {
    mymodule_myclass_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(shared_module_mymodule_myclass_get_answer(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(mymodule_myclass_answer_getter_obj, mymodule_myclass_answer_getter);

STATIC const mp_obj_property_t mymodule_myclass_answer_property = {
    .base.type = &mp_type_property,
    .proxy = {(mp_obj_t)&mymodule_myclass_answer_getter_obj,
              mp_const_none,
              mp_const_none},
};

// Define property accessors for 'question'
STATIC mp_obj_t mymodule_myclass_question_getter(mp_obj_t self_in) {
    mymodule_myclass_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_str(shared_module_mymodule_myclass_get_question(self), strlen(shared_module_mymodule_myclass_get_question(self)));
}
MP_DEFINE_CONST_FUN_OBJ_1(mymodule_myclass_question_getter_obj, mymodule_myclass_question_getter);

STATIC const mp_obj_property_t mymodule_myclass_question_property = {
    .base.type = &mp_type_property,
    .proxy = {(mp_obj_t)&mymodule_myclass_question_getter_obj,
              mp_const_none,
              mp_const_none},
};

// Define all the class methods, properties, etc. here before using it
STATIC const mp_rom_map_elem_t mymodule_myclass_locals_dict_table[] = {
    { MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&mymodule_myclass_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR_answer), MP_ROM_PTR(&mymodule_myclass_answer_property) },
    { MP_ROM_QSTR(MP_QSTR_question), MP_ROM_PTR(&mymodule_myclass_question_property) },
    // ... add other methods and properties ...
};

// Define the locals_dict right after its content definition
STATIC MP_DEFINE_CONST_DICT(mymodule_myclass_locals_dict, mymodule_myclass_locals_dict_table);

// Define the Python object type for MyClass in this module
const mp_obj_type_t mymodule_myclass_type = {
    { &mp_type_type },
    .name = MP_QSTR_MyClass,
    .make_new = mymodule_myclass_make_new,
    .locals_dict = (void*)&mymodule_myclass_locals_dict,
    // ... other type properties like print, call, unary/binary operators ...
};
