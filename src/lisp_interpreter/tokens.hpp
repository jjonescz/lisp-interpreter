// tokens.hpp
//

#ifndef _H_TOKENS
#define _H_TOKENS

#include <string>
#include <sstream>
#include "types.hpp"

class token {
public:
    virtual ~token() = default;
    virtual bool is_left_paren() { return false; }
    virtual bool is_right_paren() { return false; }
    virtual bool is_quote() { return false; }
    virtual bool is_dot() { return false; }
    virtual bool is_int() { return false; }
    virtual bool is_double() { return false; }
    virtual bool is_string() { return false; }
    virtual int32_t get_int() { throw std::runtime_error("not an int token"); }
    virtual double get_double() { throw std::runtime_error("not a double token"); }
    virtual double to_double() { throw std::runtime_error("not a numeric token"); }
    virtual const std::string& get_string() { throw std::runtime_error("not a string token"); }
    virtual std::string to_string() { throw std::runtime_error("not a stringifiable token"); }
    virtual bool equals(token& other) { throw std::runtime_error("not a comparable token"); }
    bool is_nil() { return is_string() && get_string() == "()"; }
};

class t_left_paren : public token {
public:
    bool is_left_paren() override { return true; }
};
class t_right_paren : public token {
public:
    bool is_right_paren() override { return true; }
};
class t_quote : public token {
public:
    bool is_quote() override { return true; }
};
class t_dot : public token {
public:
    bool is_dot() override { return true; }
};
class t_int : public token {
public:
    t_int(int32_t val) : val_(val) {}
    bool is_int() override { return true; }
    int32_t get_int() override { return val_; }
    double to_double() override { return val_; }
    std::string to_string() override { return std::to_string(val_); }
    bool equals(token& other) override { return other.is_int() && val_ == other.get_int(); }
private:
    int32_t val_;
};
class t_double : public token {
public:
    t_double(double val) : val_(val) {}
    bool is_double() override { return true; }
    double get_double() override { return val_; }
    double to_double() override { return val_; }
    std::string to_string() override {
        std::stringstream ss;
        ss << val_;

        // if double has no fractional part, print decimal point anyway,
        // so that it can be distinguished from integer
        double x;
        if (modf(val_, &x) == 0) { ss << ".0"; }

        return ss.str();
    }
    bool equals(token& other) override { return other.is_double() && val_ == other.get_double(); }
private:
    double val_;
};
class t_string : public token {
public:
    t_string(const std::string& val) : val_(val) {}
    bool is_string() override { return true; }
    const std::string& get_string() override { return val_; }
    std::string to_string() override { return val_; }
    bool equals(token& other) override { return other.is_string() && val_ == other.get_string(); }
private:
    std::string val_;
};

#endif
