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
    e_pair(vp car, vp cdr);
    bool is_pair() override { return true; }
    const vp& get_car() const override { return car_; }
    const vp& get_cdr() const override { return cdr_; }
    bool is_list() const override { return list_; }
    vp accept(visitor& v, vp& p) const override;
private:
    const vp car_, cdr_;
    const bool list_;
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
