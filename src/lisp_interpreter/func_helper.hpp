// func_helper.hpp
//

#ifndef _H_FUNC_HELPER
#define _H_FUNC_HELPER

#include "types.hpp"
#include "list_helper.hpp"

class func_helper {
public:
    template<typename F>
    inline static vp one_arg(evaluator& eval, vp args) {
        size_t c = list_helper(args.get()).count();
        if (c < 1) {
            throw eval_error(F::name + " must have at least 1 argument");
        }
        if (c > 1) {
            throw eval_error(F::name + " cannot have more than 1 argument");
        }
        vp arg = args->get_car();
        if (F::eval) {
            arg = eval.visit(arg);
        }
        return F::handler(arg);
    }
};

#endif
