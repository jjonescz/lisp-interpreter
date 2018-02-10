// func_helper.hpp
//

#ifndef _H_FUNC_HELPER
#define _H_FUNC_HELPER

#include <array>
#include "types.hpp"
#include "list_helper.hpp"

class func_helper {
public:
    template<typename F>
    inline static vp create(evaluator& eval, vp args) {
        list_helper list(args);
        size_t c = list.count();
        if (c < F::args) {
            throw eval_error(F::name + " was called with less than required number of arguments (" + std::to_string(F::args) + ")");
        }
        if (c > F::args) {
            throw eval_error(F::name + " was called with more than required number of arguments (" + std::to_string(F::args) + ")");
        }
        array<vp, F::args> arr;
        size_t i = 0;
        for (auto& a : list) {
            vp val = a;
            if (F::eval) {
                val = eval.visit(val);
            }
            arr[i++] = move(val);
        }
        return F::handler(eval.get_current_env(), arr);
    }
};

#endif
