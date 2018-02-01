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

class expression {
public:
    virtual bool is_pair() { return false; }
    // TODO: maybe use const expression* and const token*
    virtual cep& get_car() { throw std::runtime_error("not a pair"); }
    virtual cep& get_cdr() { throw std::runtime_error("not a pair"); }
    virtual ctp& get_token() { throw std::runtime_error("not a token"); }
};

class e_pair : public expression {
public:
    e_pair(ep car, ep cdr) : car_(move(car)), cdr_(move(cdr)) {}
    bool is_pair() override { return true; }
    cep& get_car() override { return car_; }
    cep& get_cdr() override { return cdr_; }
private:
    cep car_, cdr_;
};

class e_token : public expression {
public:
    e_token(tp val) : val_(move(val)) {}
    ctp& get_token() override { return val_; }
private:
    ctp val_;
};

#endif
