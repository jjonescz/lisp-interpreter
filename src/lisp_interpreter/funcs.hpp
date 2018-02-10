// funcs.hpp
//

using namespace std;

#include <array>
#include "types.hpp"
#include "values.hpp"
#include "evaluator.hpp"

#define func(n, a, e) struct n##_func { \
    static const string name; \
    static const size_t args = a; \
    static const bool eval = e; \
    static vp handler(ep env, array<vp, a> args); \
}; \
const string n##_func::name = #n; \
vp n##_func::handler(ep env, array<vp, a> args)

func(quote, 1, false) {
    return args[0];
}
func(car, 1, true) {
    vp& arg = args[0];
    if (!arg->is_pair() || !arg->is_list()) { throw eval_error("car must be applied to a list"); }
    return arg->get_car();
}
func(lambda, 2, false) {
    vp& sign = args[0];
    vp& body = args[1];
    if (!sign->is_list_or_nil()) { throw eval_error("lambda expects a list for arguments"); }

    // TODO: use iterators and functional style for this (and similar)?
    for (vp pair = sign; pair->is_pair(); pair = pair->get_cdr()) {
        const vp& car = pair->get_car();
        if (!car->is_token() || !car->get_token()->is_string()) {
            throw eval_error("lambda arguments must be string tokens");
        }
    }

    return make_shared<v_lambda>(sign, body, move(env));
}

#undef func
