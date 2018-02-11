// values.cpp
//

#include "tokens.hpp"
#include "values.hpp"
#include "visitors.hpp"
#include "list_helper.hpp"

using namespace std;

bool value::is_nil() {
    return is_token() && get_token()->is_nil();
}

vp v_primitive::accept(visitor& v, vp& p) const {
    return v.visit_primitive(static_pointer_cast<v_primitive>(p));
}

vp v_lambda::accept(visitor& v, vp& p) const {
    return v.visit_lambda(static_pointer_cast<v_lambda>(p));
}
