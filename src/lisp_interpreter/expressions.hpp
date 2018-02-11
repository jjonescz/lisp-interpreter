// expressions.hpp : contains the expression base class and its descendants
//

#ifndef _H_EXPRESSIONS
#define _H_EXPRESSIONS

#include <memory>
#include <exception>
#include "types.hpp"
#include "values.hpp"

// the base class for all parseable expressions
class expression : public value {};

// this class represents a LISP pair
class e_pair : public expression {
public:
    e_pair(vp car, vp cdr);
    bool is_pair() override { return true; }
    const vp& get_car() const override { return car_; }
    const vp& get_cdr() const override { return cdr_; }
    // returns true iff the whole chain of pairs ends with nil token (i.e., it is a proper list)
    bool is_list() const override { return list_; }
    vp accept(visitor& v, vp& p) const override;
private:
    const vp car_, cdr_;
    const bool list_;
};

// this class represents a LISP token (int, double or string)
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
