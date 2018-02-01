// evaluator.cpp
//

#include "evaluator.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

evaluator::evaluator() : root_(nullptr) {
    // initialize environment with default values
    root_.map["quote"] = make_shared<v_primitive>([](const shared_ptr<e_pair> args) -> cvp {
        if (!args->get_cdr()->get_cdr()->is_token()) { throw eval_error("quote cannot have more than 1 argument"); }
        return args->get_cdr()->get_car();
    });
    root_.map["car"] = make_shared<v_primitive>([](const shared_ptr<e_pair> args) -> cvp { return args->get_car(); }); // TODO
}

cvp evaluator::visit_pair(const std::shared_ptr<e_pair> pair) {
    if (!pair->is_list()) { throw eval_error("only proper lists can be evaluated"); }
    cvp car = visit(pair->get_car());
    if (car->is_primitive()) {
        return car->eval(pair);
    }
    throw eval_error("value cannot be aplied");
}

cvp evaluator::visit_token(const std::shared_ptr<e_token> token) {
    ctp& t = token->get_token();
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

cvp evaluator::visit_primitive(const std::shared_ptr<v_primitive> token) {
    throw eval_error("primitive cannot be evaluated");
}
