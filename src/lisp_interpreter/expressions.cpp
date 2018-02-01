// expressions.cpp
//

#include "expressions.hpp"
#include "tokens.hpp"
#include "visitors.hpp"

using namespace std;

e_pair::e_pair(ep car, ep cdr) : car_(move(car)), cdr_(move(cdr)) {
    if (cdr_->is_pair()) {
        list_ = cdr_->is_list();
    }
    else {
        // proper list must end with empty list
        auto& token = cdr_->get_token();
        list_ = token->is_string() && token->get_string() == "()";
    }
}

void e_pair::accept(visitor& v, cvp& p) const {
    v.visit_pair(static_pointer_cast<e_pair>(p));
}

void e_token::accept(visitor& v, cvp& p) const {
    v.visit_token(static_pointer_cast<e_token>(p));
}
