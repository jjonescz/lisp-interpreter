// funcs.hpp
//

using namespace std;

#include <vector>
#include <set>
#include "func_helpers.hpp"
#include "expressions.hpp"
#include "common_values.hpp"

struct quote_func {
    static const string name;
    using params = func_params<1>;
    using eval = const_eval<false>;
    using handler = func_wrapper<quote_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        return move(args[0]);
    }
};
const string quote_func::name = "quote";

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

struct lambda_func {
    static const string name;
    using params = func_params<1, true>;
    using eval = const_eval<true>;
    using handler = func_wrapper<lambda_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
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

        return make_shared<v_lambda>(sign, vector<vp>(++args.begin(), args.end()), eval.get_current_env());
    }
};
const string lambda_func::name = "lambda";

struct define_func {
    static const string name;
    using params = func_params<2>;
    using eval = eval_except_first;
    using handler = func_wrapper<define_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        vp& tok = args[0];
        vp& val = args[1];
        if (!tok->is_token() || !tok->get_token()->is_string()) {
            throw eval_error("define expects string token as its first argument");
        }
        eval.get_current_env()->map[tok->get_token()->get_string()] = val;
        return move(val);
    }
};
const string define_func::name = "define";

struct set_func {
    static const string name;
    using params = func_params<2>;
    using eval = eval_except_first;
    using handler = func_wrapper<set_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        vp& tok = args[0];
        vp& val = args[1];
        if (!tok->is_token() || !tok->get_token()->is_string()) {
            throw eval_error("set! expects string token as its first argument");
        }
        auto& key = tok->get_token()->get_string();
        vp *entry = eval.get_current_env()->try_find(key);
        if (!entry) { throw eval_error(key + " is undefined"); }
        *entry = val;
        return move(val);
    }
};
const string set_func::name = "set!";

struct pair_func {
    static const string name;
    using params = func_params<1>;
    using eval = const_eval<true>;
    using handler = func_wrapper<pair_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        return args[0]->is_pair() ? eval.com.true_token : eval.com.nil_token;
    }
};
const string pair_func::name = "pair?";


struct eq_func {
    static const string name;
    using params = func_params<2>;
    using eval = const_eval<true>;
    using handler = func_wrapper<eq_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        vp& first = args[0];
        vp& second = args[1];
        if (first->is_pair() || second->is_pair()) {
            throw eval_error("eq? can only compare tokens");
        }
        return are_equal(first, second) ? eval.com.true_token : eval.com.nil_token;
    }
private:
    static bool are_equal(vp& first, vp& second) {
        if (first->is_token() && second->is_token()) {
            return first->get_token()->equals(*second->get_token());
        }
        return first == second;
    }
};
const string eq_func::name = "eq?";
