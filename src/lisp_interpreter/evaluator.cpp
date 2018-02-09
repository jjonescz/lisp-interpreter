// evaluator.cpp
//

#include "evaluator.hpp"
#include "expressions.hpp"
#include "tokens.hpp"
#include "func_helper.hpp"

using namespace std;

evaluator::evaluator() : root_(nullptr) {
    // initialize environment with default values
    root_.map["quote"] = make_shared<v_primitive>(func_helper::exact<quote_func>);
    root_.map["car"] = make_shared<v_primitive>(func_helper::exact<car_func>);
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

const string quote_func::name = "quote";
vp quote_func::handler(vp arg) {
    return arg;
}

const string car_func::name = "car";
vp car_func::handler(vp arg) {
    if (!arg->is_pair() || !arg->is_list()) { throw eval_error("car must be applied to a list"); }
    return arg->get_car();
}
