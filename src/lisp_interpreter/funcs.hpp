// funcs.hpp
//

using namespace std;

#include <vector>
#include <set>
#include "types.hpp"
#include "values.hpp"
#include "evaluator.hpp"

// basic macro building blocks
#define func_struct(n, s, a, m) struct n##_func { \
    static const string name; \
    static const size_t args = a; \
    static const bool more = m; \
    static bool eval(size_t index); \
    static vp handler(ep env, vector<vp> args); \
}; \
const string n##_func::name = s;
#define func_eval(n) bool n##_func::eval(size_t index)
#define func_handler(n) vp n##_func::handler(ep env, vector<vp> args)

// macro shortcuts
#define func(n, s, a, e, m) func_struct(n, s, a, m) \
func_eval(n) { return e; } \
func_handler(n)
#define func_auto(n, a, e, m) func(n, #n, a, e, m)
#define func_exact(n, a, e) func_auto(n, a, e, false)
#define func_more(n, a, e) func_auto(n, a, e, true)

// definitions of internal functions
func_exact(quote, 1, false) {
    return args[0];
}
func_exact(car, 1, true) {
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
func_struct(set, "set!", 2, false)
func_eval(set) { return index != 0; }
func_handler(set) {
    vp& tok = args[0];
    vp& val = args[1];
    if (!tok->is_token() || !tok->get_token()->is_string()) {
        throw eval_error("set! expects string token as its first argument");
    }
    env->map[tok->get_token()->get_string()] = val;
    return move(val);
}

#undef func_struct, func_eval, func_handler, func, func_auto, func_exact, func_more
