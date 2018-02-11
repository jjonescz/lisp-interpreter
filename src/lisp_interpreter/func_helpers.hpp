// func_helpers.hpp
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

template<typename F, typename N = F>
struct func_wrapper {
    static vp f(evaluator& eval, vp args) {
        list_helper list(args);
        size_t c = list.count();
        if (c < F::params::args) {
            throw eval_error(N::name + " was called with less than required number of arguments (" + std::to_string(F::params::args) + ")");
        }
        if (c > F::params::args && !F::params::can_have_more_args) {
            throw eval_error(N::name + " was called with more than required number of arguments (" + std::to_string(F::params::args) + ")");
        }
        vector<vp> vec;
        vec.reserve(c);
        size_t i = 0;
        for (auto& a : list) {
            vp val = a;
            if (F::eval::f(i++)) {
                val = eval.visit(val);
            }
            vec.push_back(move(val));
        }
        return F::handler_(eval, vec);
    }
};

template<typename O>
struct op_func {
    using params = func_params<0, true>;
    using eval = const_eval<true>;
    static vp handler_(evaluator& eval, vector<vp>& args) {
        if (!all_of(args.begin(), args.end(), [](vp& x) { return x->is_token(); })) {
            throw eval_error(O::name + " requires tokens for arguments");
        }
        if (all_of(args.begin(), args.end(), [](vp& x) { return x->get_token()->is_int(); })) {
            return make_shared<e_token>(make_unique<t_int>(accumulate(args.begin(), args.end(), O::neutral_,
                [](int32_t a, vp& b) { return O::template op_<int32_t>(a, b->get_token()->get_int()); })));
        }
        if (all_of(args.begin(), args.end(), [](vp& x) { return  x->get_token()->is_int() || x->get_token()->is_double(); })) {
            return make_shared<e_token>(make_unique<t_double>(accumulate(args.begin(), args.end(), (double)O::neutral_,
                [](double a, vp& b) { return O::template op_<double>(a, b->get_token()->to_double()); })));
        }
        throw eval_error(O::name + " requires only numeric tokens");
    }
};

template<typename T> using op_wrapper = func_wrapper<op_func<T>, T>;

#endif
