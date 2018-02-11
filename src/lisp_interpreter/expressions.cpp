// expressions.cpp
//

#include "expressions.hpp"
#include "tokens.hpp"
#include "visitors.hpp"

using namespace std;

e_pair::e_pair(vp car, vp cdr) : car_(move(car)), cdr_(move(cdr)),
    list_(cdr_->is_list_or_nil()) {}

vp e_pair::accept(visitor& v, vp& p) const {
    return v.visit_pair(static_pointer_cast<e_pair>(p));
}

vp e_token::accept(visitor& v, vp& p) const {
    return v.visit_token(static_pointer_cast<e_token>(p));
}
