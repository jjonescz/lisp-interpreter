// funcs_list.hpp
//

#include <vector>
#include "func_helpers.hpp"
#include "expressions.hpp"
#include "evaluator.hpp"

using namespace std;

struct car_func {
    static const string name;
    using params = func_params<1>;
    using eval = const_eval<true>;
    using handler = func_wrapper<car_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        vp& arg = args[0];
        if (!arg->is_pair() || !arg->is_list()) { throw eval_error("car must be applied to a list"); }
        return arg->get_car();
    }
};
const string car_func::name = "car";

struct cdr_func {
    static const string name;
    using params = func_params<1>;
    using eval = const_eval<true>;
    using handler = func_wrapper<cdr_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        vp& arg = args[0];
        if (!arg->is_pair() || !arg->is_list()) { throw eval_error("cdr must be applied to a list"); }
        return arg->get_cdr();
    }
};
const string cdr_func::name = "cdr";

struct cons_func {
    static const string name;
    using params = func_params<2>;
    using eval = const_eval<true>;
    using handler = func_wrapper<cons_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        return make_shared<e_pair>(move(args[0]), move(args[1]));
    }
};
const string cons_func::name = "cons";
