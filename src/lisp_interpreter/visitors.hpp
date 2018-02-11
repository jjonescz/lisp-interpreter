// visitors.hpp : the visitor base class and a simple printer visitor class;
// more complex visitor, the evaluator, is in a separate file
//

#ifndef _H_VISITORS
#define _H_VISITORS

#include <iostream>
#include "types.hpp"

// the base class for implementors of the visitor pattern of the abstract syntax tree
// and the runtime "value tree" of LISP programs
class visitor {
public:
    virtual ~visitor() = default;
    vp visit(vp v);
    virtual vp visit_pair(std::shared_ptr<e_pair> pair) = 0;
    virtual vp visit_token(std::shared_ptr<e_token> token) = 0;
    virtual vp visit_primitive(std::shared_ptr<v_primitive> primitive) = 0;
    virtual vp visit_lambda(std::shared_ptr<v_lambda> lambda) = 0;
};

// this visitor just pretty-prints the values and doesn't change them in any way
class printer : public visitor {
public:
    printer(std::ostream& str) : str_(str), in_list_(false) {}
    vp visit_pair(std::shared_ptr<e_pair> pair) override;
    vp visit_token(std::shared_ptr<e_token> token) override;
    vp visit_primitive(std::shared_ptr<v_primitive> primitive) override;
    vp visit_lambda(std::shared_ptr<v_lambda> lambda) override;
private:
    std::ostream& str_;
    bool in_list_;
};

#endif
