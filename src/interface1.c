#include "interface1.h"

const InterfaceID Interface1_ID = "Interface1";

Result Interface1_query_interface(const Interface1 *self, const InterfaceID *iid, void **value) {
    return self->_vtbl->query_interface(self, iid, value);
}
Result Interface1_get_value(const Interface1 *self, Value *value) {
    return self->_vtbl->get_value(self, value);
}
Result Interface1_set_value(Interface1 *self, Value *value) {
    return self->_vtbl->set_value(self, value);
}
