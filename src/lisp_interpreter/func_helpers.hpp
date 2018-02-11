// func_helpers.hpp : contains templates that are used to generate embedded primitive functions at compile-time
// which share lot of common boilerplate code (which we try to avoid repeating by using these templates)
//

#ifndef _H_FUNC_HELPERS
#define _H_FUNC_HELPERS

#include "list_helper.hpp"

using namespace std;

template<size_t A, bool M = false>
struct func_params {
    static const size_t args = A;
    static const bool can_have_more_args = M;
};

template<bool E>
struct const_eval {
    static bool f(size_t index) { return E; }
};

struct eval_except_first {
    static bool f(size_t index) { return index != 0; }
};

// this is a basic skeleton for every primitive function
template<typename F, typename N = F>
struct func_wrapper {
    static vp f(evaluator& eval, vp args) {
        list_helper list(args);

        // check argument count
        size_t c = list.count();
        if (c < F::params::args) {
            throw eval_error(N::name + " was called with less than required number of arguments (" + to_string(F::params::args) + ")");
        }
        if (c > F::params::args && !F::params::can_have_more_args) {
            throw eval_error(N::name + " was called with more than required number of arguments (" + to_string(F::params::args) + ")");
        }

        // assemble a vector of arguments
        vector<vp> vec;
        vec.reserve(c);
        size_t i = 0;
        for (auto& a : list) {
            vp val = a;
            if (F::eval::f(i++)) { // evaluate argument if required
                val = eval.visit(val);
            }
            vec.push_back(move(val));
        }

        // process the arguments
        return F::handler_(eval, vec);
    }
};

// this is a common code shared by all primitive numeric operators
template<typename O>
struct op_func {
    using params = func_params<0, true>;
    using eval = const_eval<true>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        // check that arguments are tokens
        if (!all_of(args.begin(), args.end(), [](vp& x) { return x->is_token(); })) {
            throw eval_error(O::name + " requires tokens for arguments");
        }

        // if they are integer numbers, we use integer version of the operator
        if (all_of(args.begin(), args.end(), [](vp& x) { return x->get_token()->is_int(); })) {
            int32_t first = args.empty() ? O::neutral_ : args[0]->get_token()->get_int();
            return make_shared<e_token>(make_unique<t_int>(accumulate(++args.begin(), args.end(), first,
                [](int32_t a, vp& b) { return O::template op_<int32_t>(a, b->get_token()->get_int()); })));
        }

        // if some or all of them are decimal, we use decimal version of the operator
        if (all_of(args.begin(), args.end(), [](vp& x) { return  x->get_token()->is_int() || x->get_token()->is_double(); })) {
            double first = args.empty() ? O::neutral_ : args[0]->get_token()->to_double();
            return make_shared<e_token>(make_unique<t_double>(accumulate(++args.begin(), args.end(), first,
                [](double a, vp& b) { return O::template op_<double>(a, b->get_token()->to_double()); })));
        }

        throw eval_error(O::name + " requires only numeric tokens");
    }
};

template<typename T> using op_wrapper = func_wrapper<op_func<T>, T>;

#endif
