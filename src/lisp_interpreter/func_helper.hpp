// func_helper.hpp
//

#ifndef _H_FUNC_HELPER
#define _H_FUNC_HELPER

#include "types.hpp"
#include "list_helper.hpp"

class func_helper {
public:
    template<typename F>
    inline static vp exact(evaluator& eval, vp args) {
        size_t c = list_helper(args.get()).count();
        if (c < F::args) {
            throw eval_error(F::name + " was called with less than required number of arguments (" + std::to_string(F::args) + ")");
        }
        if (c > F::args) {
            throw eval_error(F::name + " was called with more than required number of arguments (" + std::to_string(F::args) + ")");
        }
        // TODO: use F::args in the following code
        vp arg = args->get_car();
        if (F::eval) {
            arg = eval.visit(arg);
        }
        return F::handler(arg);
    }
};

#endif
