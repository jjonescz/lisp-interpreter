// expressions.hpp
//

#ifndef _H_EXPRESSIONS
#define _H_EXPRESSIONS

#include <memory>
#include <exception>
#include "tokens.hpp"

class expression;
using ep = std::shared_ptr<expression>;
using cep = const ep;
using tp = std::unique_ptr<token>;
using ctp = const tp;

class e_pair;
class e_token;

class visitor {
public:
    void visit(const expression& e);
    virtual void visit_pair(const e_pair& pair) = 0;
    virtual void visit_token(const e_token& token) = 0;
};

class expression {
public:
    virtual bool is_pair() { return false; } // TODO: not used (yet?)
    virtual cep& get_car() const { throw std::runtime_error("not a pair"); }
    virtual cep& get_cdr() const { throw std::runtime_error("not a pair"); }
    virtual ctp& get_token() const { throw std::runtime_error("not a token"); }
    virtual bool is_list() const { throw std::runtime_error("not a pair"); }
    virtual void accept(visitor& v) const = 0;
};

class e_pair : public expression {
public:
    e_pair(ep car, ep cdr) : car_(move(car)), cdr_(move(cdr)) {
        if (cdr_->is_pair()) {
            list_ = cdr_->is_list();
        }
        else {
            // proper list must end with empty list
            auto& token = cdr_->get_token();
            list_ = token->is_string() && token->get_string() == "()";
        }
    }
    bool is_pair() override { return true; }
    cep& get_car() const override { return car_; }
    cep& get_cdr() const override { return cdr_; }
    bool is_list() const override { return list_; }
    void accept(visitor& v) const override { v.visit_pair(*this); }
private:
    cep car_, cdr_;
    bool list_;
};

class e_token : public expression {
public:
    e_token(tp val) : val_(move(val)) {}
    ctp& get_token() const override { return val_; }
    void accept(visitor& v) const override { v.visit_token(*this); }
private:
    ctp val_;
};

#endif
