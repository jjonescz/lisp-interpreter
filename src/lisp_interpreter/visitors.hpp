// visitors.hpp
//

#ifndef _H_VISITORS
#define _H_VISITORS

#include <iostream>
#include "expressions.hpp"

class visitor {
public:
    virtual ~visitor() = default;
    void visit(const value& v);
    virtual void visit_pair(const e_pair& pair) = 0;
    virtual void visit_token(const e_token& token) = 0;
};

class printer : public visitor {
public:
    printer(std::ostream& str) : str_(str), in_list_(false) {}
    void visit_pair(const e_pair& pair) override;
    void visit_token(const e_token& token) override;
private:
    std::ostream& str_;
    bool in_list_;
};

#endif
