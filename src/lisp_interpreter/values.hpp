// values.hpp
//

#ifndef _H_VALUES
#define _H_VALUES

#include <memory>

class visitor;
class e_pair;
class environment;

class value {
public:
    virtual ~value() = default;
    virtual void accept(visitor& v) const = 0;
};

using vp = std::shared_ptr<value>;
using cvp = const vp;

class internal_value : public value {
public:
    virtual bool is_primitive() { return false; }
    virtual bool is_lambda() { return false; }
    virtual cvp eval(const e_pair& args) { throw std::runtime_error("not a function"); }
};

using prim_func = cvp(*)(const e_pair&);

class v_primitive : public internal_value {
public:
    v_primitive(prim_func func) : func_(func) {}
    bool is_primitive() override { return true; }
    cvp eval(const e_pair& args) override { return func_(args); }
private:
    prim_func func_;
};

class v_lambda : public internal_value {
private:
    const e_pair& val_;
    const environment& env_;
};

#endif
