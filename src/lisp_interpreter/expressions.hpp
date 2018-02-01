// expressions.hpp
//

#ifndef _H_EXPRESSIONS
#define _H_EXPRESSIONS

#include <memory>
#include <exception>
#include "tokens.hpp"
#include "values.hpp"

class expression;
using ep = std::shared_ptr<expression>;
using cep = const ep;
using tp = std::unique_ptr<token>;
using ctp = const tp;

class visitor;

class expression : public value {
public:
    virtual bool is_pair() { return false; }
    virtual cep& get_car() const { throw std::runtime_error("not a pair"); }
    virtual cep& get_cdr() const { throw std::runtime_error("not a pair"); }
    virtual ctp& get_token() const { throw std::runtime_error("not a token"); }
    virtual bool is_list() const { throw std::runtime_error("not a pair"); }
};

class e_pair : public expression {
public:
    e_pair(ep car, ep cdr);
    bool is_pair() override { return true; }
    cep& get_car() const override { return car_; }
    cep& get_cdr() const override { return cdr_; }
    bool is_list() const override { return list_; }
    void accept(visitor& v) const override;
private:
    cep car_, cdr_;
    bool list_;
};

class e_token : public expression {
public:
    e_token(tp val) : val_(move(val)) {}
    ctp& get_token() const override { return val_; }
    void accept(visitor& v) const override;
private:
    ctp val_;
};

#endif
