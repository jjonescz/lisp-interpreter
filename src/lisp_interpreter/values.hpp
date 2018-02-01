// values.hpp
//

#ifndef _H_VALUES
#define _H_VALUES

class visitor;

class value {
public:
    virtual void accept(visitor& v) const = 0;
};

class internal_value : public value {
public:
    virtual bool is_primitive() { return false; }
    virtual bool is_lambda() { return false; }
};

#endif
