// funcs_list.hpp : functions for LISt Processing
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
        if (!arg->is_pair()) { throw eval_error("car must be applied to a list"); }
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
        if (!arg->is_pair()) { throw eval_error("cdr must be applied to a list"); }
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

struct list_func {
    static const string name;
    using params = func_params<0, true>;
    using eval = const_eval<true>;
    using handler = func_wrapper<list_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        return make_list(eval, args.begin(), args.end());
    }
private:
    static vp make_list(evaluator& eval, vector<vp>::iterator start, vector<vp>::iterator end) {
        if (start == end) { return eval.com.nil_token; }
        return make_shared<e_pair>(move(*start), make_list(eval, start + 1, end));
    }
};
const string list_func::name = "list";
