// visitors.cpp
//

#include "expressions.hpp"
#include "visitors.hpp"

void visitor::visit(const expression& e) {
    e.accept(*this);
}

void printer::visit_pair(const e_pair& pair) {
    str_ << "(";
    visit(*pair.get_car());
    str_ << " . ";
    visit(*pair.get_cdr());
    str_ << ")";
}

void printer::visit_token(const e_token& token) {
    str_ << token.get_token()->to_string();
}
