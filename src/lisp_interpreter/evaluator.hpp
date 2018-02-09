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
    template<typename F>
    void add_primitive() {
        root_.map[F::name] = make_shared<v_primitive>(func_helper::exact<F>);
    }

    environment root_;
};

#endif
