// evaluator.cpp
//

#include "evaluator.hpp"
#include "expressions.hpp"
#include "tokens.hpp"
#include "func_helper.hpp"
#include "funcs.hpp"

using namespace std;

evaluator::evaluator() : root_(nullptr) {
    // initialize environment with default values
    add_primitive<quote_func>();
    add_primitive<car_func>();
}

vp evaluator::visit_pair(shared_ptr<e_pair> pair) {
    if (!pair->is_list()) { throw eval_error("only proper lists can be evaluated"); }
    // TODO: implement function (probably lambdas only) overloading (by number of arguments)
    vp car = visit(pair->get_car());
    if (car->is_primitive()) {
        return car->eval(*this, pair->get_cdr());
    }
    throw eval_error("value cannot be aplied");
}

vp evaluator::visit_token(shared_ptr<e_token> token) {
    auto& t = token->get_token();
    if (t->is_string()) {
        auto& s = t->get_string();
        auto v = root_.map.find(s);
        if (v != root_.map.end()) {
            return v->second;
        }
        throw eval_error("undefined symbol");
    }
    if (t->is_int() || t->is_double()) {
        return move(token);
    }
    throw runtime_error("unexpected token found");
}

vp evaluator::visit_primitive(shared_ptr<v_primitive> token) {
    throw eval_error("primitive cannot be evaluated");
}
