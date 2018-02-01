// visitors.hpp
//

#ifndef _H_VISITORS
#define _H_VISITORS

#include <iostream>
#include "types.hpp"

class visitor {
public:
    virtual ~visitor() = default;
    cvp visit(cvp v);
    virtual cvp visit_pair(const std::shared_ptr<e_pair> pair) = 0;
    virtual cvp visit_token(const std::shared_ptr<e_token> token) = 0;
    virtual cvp visit_primitive(const std::shared_ptr<v_primitive> token) = 0;
};

class printer : public visitor {
public:
    printer(std::ostream& str) : str_(str), in_list_(false) {}
    cvp visit_pair(const std::shared_ptr<e_pair> pair) override;
    cvp visit_token(const std::shared_ptr<e_token> token) override;
    cvp visit_primitive(const std::shared_ptr<v_primitive> token) override;
private:
    std::ostream& str_;
    bool in_list_;
};

#endif
