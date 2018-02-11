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

template<typename F>
struct func_wrapper {
    static vp f(evaluator& eval, vp args) {
        list_helper list(args);
        size_t c = list.count();
        if (c < F::params::args) {
            throw eval_error(F::name + " was called with less than required number of arguments (" + std::to_string(F::params::args) + ")");
        }
        if (c > F::params::args && !F::params::can_have_more_args) {
            throw eval_error(F::name + " was called with more than required number of arguments (" + std::to_string(F::params::args) + ")");
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

#endif
