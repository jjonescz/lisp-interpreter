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
    evaluator(common_values& com);
    vp visit_pair(std::shared_ptr<e_pair> pair) override;
    vp visit_token(std::shared_ptr<e_token> token) override;
    vp visit_primitive(std::shared_ptr<v_primitive> primitive) override;
    vp visit_lambda(std::shared_ptr<v_lambda> lambda) override;
    const ep& get_current_env() { return env_; }

    common_values& com;
private:
    template<typename F>
    void add_primitive() {
        env_->map[F::name] = std::make_shared<v_primitive>(F::handler::f);
    }

    ep env_;
};

#endif
