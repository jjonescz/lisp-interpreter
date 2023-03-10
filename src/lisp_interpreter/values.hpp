// values.hpp : contains the value class, internal_value class, and descendants of internal_value class
//

#ifndef _H_VALUES
#define _H_VALUES

#include <memory>
#include <vector>
#include "types.hpp"

// the base class for all values that can appear in a LISP program at runtime
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
    virtual const vp& get_args() { throw std::runtime_error("not a lambda"); }
    virtual const std::vector<vp>& get_body() { throw std::runtime_error("not a lambda"); }
    virtual const ep& get_env() { throw std::runtime_error("not a lambda"); }
    virtual vp accept(visitor& v, vp& p) const = 0;
    bool is_list_or_nil() { return (is_pair() && is_list()) || is_nil(); }
    bool is_nil();
};

// the base class for values that cannot be user-written, only generated during the evaluation
class internal_value : public value {};

// this class represents a primitive function (its code is written in C++)
class v_primitive : public internal_value {
public:
    v_primitive(prim_func func) : func_(func) {}
    bool is_primitive() override { return true; }
    vp eval(evaluator& eval, vp args) override { return func_(eval, args); }
    vp accept(visitor& v, vp& p) const override;
private:
    const prim_func func_;
};

// this class represents an user function (its code is written in LISP) together with captured environment
class v_lambda : public internal_value {
public:
    v_lambda(vp args, std::vector<vp> body, ep env) : args_(move(args)), body_(move(body)), env_(move(env)) {}
    bool is_lambda() override { return true; }
    const vp& get_args() override { return args_; }
    const std::vector<vp>& get_body() override { return body_; }
    const ep& get_env() override { return env_; }
    vp accept(visitor& v, vp& p) const override;
private:
    const vp args_;
    const std::vector<vp> body_;
    const ep env_;
};

#endif
