// evaluator.cpp
//

#include "evaluator.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

void check_one_arg(const shared_ptr<e_pair> args) {
    if (!args->get_cdr()->is_pair()) {
        throw eval_error(args->get_car()->get_token()->get_string() + " must have at least 1 argument");
    }
    if (!args->get_cdr()->get_cdr()->is_token()) {
        throw eval_error(args->get_car()->get_token()->get_string() + " cannot have more than 1 argument");
    }
}

evaluator::evaluator() : root_(nullptr) {
    // initialize environment with default values
    root_.map["quote"] = make_shared<v_primitive>([](evaluator& eval, shared_ptr<e_pair> args) -> vp {
        check_one_arg(args);
        return args->get_cdr()->get_car();
    });
    root_.map["car"] = make_shared<v_primitive>([](evaluator& eval, shared_ptr<e_pair> args) -> vp {
        check_one_arg(args);
        vp list = eval.visit(args->get_cdr()->get_car());
        if (!list->is_pair() || !list->is_list()) { throw eval_error("car must be applied to a list"); }
        return list->get_car();
    });
}

vp evaluator::visit_pair(std::shared_ptr<e_pair> pair) {
    if (!pair->is_list()) { throw eval_error("only proper lists can be evaluated"); }
    vp car = visit(pair->get_car());
    if (car->is_primitive()) {
        return car->eval(*this, pair);
    }
    throw eval_error("value cannot be aplied");
}

vp evaluator::visit_token(std::shared_ptr<e_token> token) {
    auto& t = token->get_token();
    if (t->is_string()) {
        auto& s = t->get_string();
        auto v = root_.map.find(s);
        if (v != root_.map.end()) {
            return v->second;
        }
        throw eval_error("undefined symbol");
    }
    throw runtime_error("not implemented"); // TODO
}

vp evaluator::visit_primitive(std::shared_ptr<v_primitive> token) {
    throw eval_error("primitive cannot be evaluated");
}
