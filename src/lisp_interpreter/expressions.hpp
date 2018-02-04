// expressions.hpp
//

#ifndef _H_EXPRESSIONS
#define _H_EXPRESSIONS

#include <memory>
#include <exception>
#include "types.hpp"
#include "values.hpp"

class expression : public value {};

class e_pair : public expression {
public:
    e_pair(ep car, ep cdr);
    bool is_pair() override { return true; }
    const ep& get_car() const override { return car_; }
    const ep& get_cdr() const override { return cdr_; }
    bool is_list() const override { return list_; }
    vp accept(visitor& v, vp& p) const override;
private:
    const ep car_, cdr_;
    bool list_;
};

class e_token : public expression {
public:
    e_token(tp val) : val_(move(val)) {}
    bool is_token() override { return true; }
    const tp& get_token() const override { return val_; }
    vp accept(visitor& v, vp& p) const override;
private:
    const tp val_;
};

#endif
