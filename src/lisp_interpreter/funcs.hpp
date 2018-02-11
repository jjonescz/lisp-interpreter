// funcs.hpp
//

// TODO: do this somehow without macros?

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
#define func_struct_auto(n, a, m) func_struct(n, #n, a, m)
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

    return make_shared<v_lambda>(sign, vector<vp>(++args.begin(), args.end()), move(env));
}

// TODO: advance this further
func_struct_auto(define, 2, false)
func_eval(define) { return index != 0; }
func_handler(define) {
    vp& tok = args[0];
    vp& val = args[1];
    if (!tok->is_token() || !tok->get_token()->is_string()) {
        throw eval_error("define expects string token as its first argument");
    }
    env->map[tok->get_token()->get_string()] = val;
    return move(val);
}

func_struct(set, "set!", 2, false)
func_eval(set) { return index != 0; }
func_handler(set) {
    vp& tok = args[0];
    vp& val = args[1];
    if (!tok->is_token() || !tok->get_token()->is_string()) {
        throw eval_error("set! expects string token as its first argument");
    }
    auto& key = tok->get_token()->get_string();
    vp *entry = env->try_find(key);
    if (!entry) { throw eval_error(key + " is undefined"); }
    *entry = val;
    return move(val);
}

#undef func_struct
#undef func_eval
#undef func_handler
#undef func_struct_auto
#undef func
#undef func_auto
#undef func_exact
#undef func_more
