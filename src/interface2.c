#include "interface2.h"

const InterfaceID Interface2_ID = "Interface2";

Result Interface2_query_interface(const Interface2 *self, const InterfaceID *iid, void **value) {
    return self->_vtbl->query_interface(self, iid, value);
}
Result Interface2_get_value(const Interface2 *self, Value *value) {
    return self->_vtbl->get_value(self, value);
}
Result Interface2_set_value(Interface2 *self, const Value *value) {
    return self->_vtbl->set_value(self, value);
}
Result Interface2_get_objects(const Interface2 *self, Value *value) {
    return self->_vtbl->get_objects(self, value);
}
Result Interface2_set_objects(Interface2 *self, const Value *value) {
    return self->_vtbl->set_objects(self, value);
}
