// values.cpp
//

#include "tokens.hpp"
#include "values.hpp"
#include "visitors.hpp"
#include "list_helper.hpp"

using namespace std;

bool value::is_list_or_nil() {
    if (is_pair() && is_list()) { return true; }
    if (is_token()) {
        const tp& t = get_token();
        return t->is_string() && t->get_string() == "()";
    }
}

vp v_primitive::accept(visitor& v, vp& p) const {
    return v.visit_primitive(static_pointer_cast<v_primitive>(p));
}

vp v_lambda::accept(visitor& v, vp& p) const {
    return v.visit_lambda(static_pointer_cast<v_lambda>(p));
}
