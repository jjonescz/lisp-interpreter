// funcs_math.hpp
//

#include <vector>
#include <algorithm>
#include <numeric>
#include "evaluator.hpp"
#include "func_helpers.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

struct plus_func {
    static const string name;
    using params = func_params<0, true>;
    using eval = const_eval<true>;
    using handler = func_wrapper<plus_func>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        if (!all_of(args.begin(), args.end(), [](vp& x) { return x->is_token(); })) {
            throw eval_error("+ requires tokens for arguments");
        }
        if (all_of(args.begin(), args.end(), [](vp& x) { return x->get_token()->is_int(); })) {
            return make_shared<e_token>(make_unique<t_int>(accumulate(args.begin(), args.end(), 0,
                [](int a, vp& b) { return a + b->get_token()->get_int(); })));
        }
        if (all_of(args.begin(), args.end(), [](vp& x) { return  x->get_token()->is_int() || x->get_token()->is_double(); })) {
            return make_shared<e_token>(make_unique<t_double>(accumulate(args.begin(), args.end(), 0.0,
                [](double a, vp& b) { return a + b->get_token()->to_double(); })));
        }
        throw eval_error("+ requires only numeric tokens");
    }
};
const string plus_func::name = "+";
