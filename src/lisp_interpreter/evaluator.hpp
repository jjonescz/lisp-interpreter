// evaluator.hpp
//

#ifndef _H_EVALUATOR
#define _H_EVALUATOR

#include "types.hpp"
#include "visitors.hpp"
#include "environment.hpp"

class eval_error : public std::runtime_error {
public:
    eval_error(const std::string& msg) : std::runtime_error(msg) {}
};

class evaluator : public visitor {
public:
    evaluator();
    vp visit_pair(std::shared_ptr<e_pair> pair) override;
    vp visit_token(std::shared_ptr<e_token> token) override;
    vp visit_primitive(std::shared_ptr<v_primitive> token) override;
private:
    environment root_;
};

#define func(n, a, e) struct n##_func { \
    static const std::string name; \
    static const int args = a; \
    static const bool eval = e; \
    static vp handler(vp arg); \
};

func(quote, 1, false)
func(car, 1, true)

#undef func

#endif
