// visitors.cpp
//

#include "visitors.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

vp visitor::visit(vp v) {
    return v->accept(*this, v);
}

vp printer::visit_pair(shared_ptr<e_pair> pair) {
    if (in_list_) {
        str_ << " ";
        in_list_ = false;
        visit(pair->get_car());
        in_list_ = true;
        visit(pair->get_cdr());
    }
    else if (pair->is_list()) {
        str_ << "(";
        visit(pair->get_car());
        in_list_ = true;
        visit(pair->get_cdr());
    }
    else {
        str_ << "(";
        visit(pair->get_car());
        str_ << " . ";
        visit(pair->get_cdr());
        str_ << ")";
    }
    return move(pair);
}

vp printer::visit_token(shared_ptr<e_token> token) {
    auto& t = token->get_token();
    if (in_list_ && t->is_string() && t->get_string() == "()") {
        str_ << ")";
    }
    else {
        str_ << t->to_string();
    }
    return move(token);
}

vp printer::visit_primitive(shared_ptr<v_primitive> token) {
    str_ << "'[primitive function]";
    return move(token);
}
