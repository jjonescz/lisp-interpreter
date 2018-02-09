// list_helper.cpp
//

#include "list_helper.hpp"
#include "values.hpp"

using namespace std;

list_helper::list_helper(value* val) : val_(val) {
    if (!val->is_list_or_nil()) {
        throw runtime_error("not a list");
    }
}

size_t list_helper::count() {
    size_t c = 0;
    for (value * v = val_; v->is_pair(); v = v->get_cdr().get()) {
        ++c;
    }
    return c;
}
