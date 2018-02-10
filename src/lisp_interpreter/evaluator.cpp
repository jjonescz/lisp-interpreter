// evaluator.cpp
//

#include "evaluator.hpp"
#include "expressions.hpp"
#include "tokens.hpp"
#include "func_helper.hpp"
#include "funcs.hpp"
#include "list_helper.hpp"

using namespace std;

evaluator::evaluator() : env_(make_shared<environment>(nullptr)) {
    // initialize environment with default values
    add_primitive<quote_func>();
    add_primitive<car_func>();
    add_primitive<lambda_func>();
}

vp evaluator::visit_pair(shared_ptr<e_pair> pair) {
    if (!pair->is_list()) { throw eval_error("only proper lists can be evaluated"); }
    // TODO: implement function (probably lambdas only) overloading (by number of arguments)
    // - most likely by creating new internal_value (lambda_group) which will be created or updated by define
    vp car = visit(pair->get_car());
    if (car->is_primitive()) {
        return car->eval(*this, pair->get_cdr());
    }
    if (car->is_lambda()) {
        vp args = car->get_args();
        const vp& body = car->get_body();
        size_t lambda_count = list_helper(args.get()).count();
        size_t call_count = list_helper(pair->get_cdr().get()).count();
        if (lambda_count != call_count) {
            throw eval_error("lambda called with unexpected number of arguments (" + to_string(call_count)
                + " instead of " + to_string(lambda_count) + ")");
        }

        // create an environment for the lambda
        ep env = make_shared<environment>(car->get_env());
        vp vals = pair->get_cdr();
        for (size_t i = 0; i < lambda_count; ++i) { // TODO: use list_helper
            env->map[args->get_car()->get_token()->get_string()] = visit(vals->get_car());
            args = args->get_cdr();
            vals = vals->get_cdr();
        }

        // evaluate body in that new environment
        swap(env_, env);
        vp res = visit(body);
        swap(env_, env);
        return move(res);
    }
    throw eval_error("value cannot be aplied");
}

vp evaluator::visit_token(shared_ptr<e_token> token) {
    auto& t = token->get_token();
    if (t->is_string()) {
        auto& s = t->get_string();
        vp res = env_->try_find(s);
        if (!res) { throw eval_error("undefined symbol (" + s + ")"); }
        return res;
    }
    if (t->is_int() || t->is_double()) {
        return move(token);
    }
    throw runtime_error("unexpected token found");
}

vp evaluator::visit_primitive(shared_ptr<v_primitive> token) {
    throw eval_error("primitive cannot be evaluated");
}

vp evaluator::visit_lambda(std::shared_ptr<v_lambda> lambda) {
    throw eval_error("lambda cannot be evaluated");
}
