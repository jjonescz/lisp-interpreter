// funcs.hpp
//

using namespace std;

#include <vector>
#include <set>
#include "types.hpp"
#include "values.hpp"
#include "evaluator.hpp"

#define func_(n, a, e, m) struct n##_func { \
    static const string name; \
    static const size_t args = a; \
    static const bool more = m; \
    static const bool eval = e; \
    static vp handler(ep env, vector<vp> args); \
}; \
const string n##_func::name = #n; \
vp n##_func::handler(ep env, vector<vp> args) // TODO: maybe make eval a function

#define func(n, a, e) func_(n, a, e, false)
#define func_more(n, a, e) func_(n, a, e, true)

func(quote, 1, false) {
    return args[0];
}
func(car, 1, true) {
    vp& arg = args[0];
    if (!arg->is_pair() || !arg->is_list()) { throw eval_error("car must be applied to a list"); }
    return arg->get_car();
}
func_more(lambda, 2, false) {
    vp& sign = args[0];
    vp& body = args[1]; // TODO: process also other statements inside the body
    if (!sign->is_list_or_nil()) { throw eval_error("lambda expects a list for arguments"); }

    set<string> names;
    for (auto& a : list_helper(sign)) {
        if (!a->is_token() || !a->get_token()->is_string()) {
            throw eval_error("lambda arguments must be string tokens");
        }
        if (!names.insert(a->get_token()->get_string()).second) {
            throw eval_error("lambda argument names must be distinct");
        }
    }

    return make_shared<v_lambda>(sign, body, move(env));
}

#undef func_, func, func_more
