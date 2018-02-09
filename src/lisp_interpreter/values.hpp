// values.hpp
//

#ifndef _H_VALUES
#define _H_VALUES

#include <memory>
#include "types.hpp"

class value {
public:
    virtual ~value() = default;
    virtual bool is_pair() { return false; }
    virtual bool is_token() { return false; }
    virtual const vp& get_car() const { throw std::runtime_error("not a pair"); }
    virtual const vp& get_cdr() const { throw std::runtime_error("not a pair"); }
    virtual const tp& get_token() const { throw std::runtime_error("not a token"); }
    virtual bool is_list() const { throw std::runtime_error("not a pair"); }
    virtual bool is_primitive() { return false; }
    virtual bool is_lambda() { return false; }
    virtual vp eval(evaluator& eval, vp args) { throw std::runtime_error("not a function"); }
    virtual vp accept(visitor& v, vp& p) const = 0;
};

class internal_value : public value {};

class v_primitive : public internal_value {
public:
    v_primitive(prim_func func) : func_(func) {}
    bool is_primitive() override { return true; }
    vp eval(evaluator& eval, vp args) override { return func_(eval, args); }
    vp accept(visitor& v, vp& p) const override;
private:
    const prim_func func_;
};

class v_lambda : public internal_value {
private:
    const e_pair& val_;
    const environment& env_; // TODO: shouldn't this be shared_ptr, too?
};

#endif
