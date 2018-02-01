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
    virtual uint32_t get_int() { throw std::runtime_error("not an int token"); }
    virtual double get_double() { throw std::runtime_error("not a double token"); }
    virtual std::string get_string() { throw std::runtime_error("not a string token"); }
    virtual std::string to_string() { throw std::runtime_error("not a stringifiable token"); }
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
    t_int(uint32_t val) : val_(val) {}
    bool is_int() override { return true; }
    uint32_t get_int() override { return val_; }
    std::string to_string() override { return std::to_string(val_); }
private:
    uint32_t val_;
};
class t_double : public token {
public:
    t_double(double val) : val_(val) {}
    bool is_double() override { return true; }
    double get_double() override { return val_; }
    std::string to_string() override {
        std::stringstream ss;
        ss << val_;
        return ss.str();
    }
private:
    double val_;
};
class t_string : public token {
public:
    t_string(const std::string& val) : val_(val) {}
    bool is_string() override { return true; }
    std::string get_string() override { return val_; }
    std::string to_string() override { return val_; }
private:
    std::string val_;
};

#endif
