// evaluator.hpp
//

#ifndef _H_EVALUATOR
#define _H_EVALUATOR

#include "types.hpp"
#include "visitors.hpp"
#include "environment.hpp"

class eval_error : public std::runtime_error {
public:
	eval_error(const char *msg) : std::runtime_error(msg) {}
};

class evaluator : public visitor {
public:
	evaluator();
	cvp visit_pair(const std::shared_ptr<e_pair> pair) override;
	cvp visit_token(const std::shared_ptr<e_token> token) override;
	cvp visit_primitive(const std::shared_ptr<v_primitive> token) override;
private:
	environment root_;
};

#endif
