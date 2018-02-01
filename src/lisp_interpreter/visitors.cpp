// visitors.cpp
//

#include <cassert>
#include "visitors.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

void visitor::visit(const value& v) {
    v.accept(*this);
}

void printer::visit_pair(const e_pair& pair) {
    if (in_list_) {
        str_ << " ";
        in_list_ = false;
        visit(*pair.get_car());
        in_list_ = true;
        visit(*pair.get_cdr());
    }
    else if (pair.is_list()) {
        str_ << "(";
        visit(*pair.get_car());
        in_list_ = true;
        visit(*pair.get_cdr());
    }
    else {
        str_ << "(";
        visit(*pair.get_car());
        str_ << " . ";
        visit(*pair.get_cdr());
        str_ << ")";
    }
}

void printer::visit_token(const e_token& token) {
    auto& t = token.get_token();
    if (in_list_ && t->is_string() && t->get_string() == "()") {
        str_ << ")";
    }
    else {
        str_ << t->to_string();
    }
}
