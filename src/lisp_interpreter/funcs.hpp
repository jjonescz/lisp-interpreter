// funcs.hpp
//

using namespace std;

#include "types.hpp"
#include "values.hpp"
#include "evaluator.hpp"

#define func(n, a, e) struct n##_func { \
    static const string name; \
    static const size_t args = a; \
    static const bool eval = e; \
    static vp handler(vp arg); \
}; \
const string n##_func::name = #n; \
vp n##_func::handler

func(quote, 1, false)(vp arg) {
    return arg;
}
func(car, 1, true)(vp arg) {
    if (!arg->is_pair() || !arg->is_list()) { throw eval_error("car must be applied to a list"); }
    return arg->get_car();
}

#undef func
