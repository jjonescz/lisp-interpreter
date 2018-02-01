// tokens.hpp
//

#ifndef _H_TOKENS
#define _H_TOKENS

#include <string>
#include <list>

class token {
public:
    virtual bool is_left_paren() { return false; }
    virtual bool is_right_paren() { return false; }
    virtual bool is_quote() { return false; }
    virtual bool is_int() { return false; }
    virtual bool is_double() { return false; }
    virtual uint32_t get_int() { throw std::runtime_error("not int token"); }
    virtual double get_double() { throw std::runtime_error("not double token"); }
    virtual std::string get_string() { throw std::runtime_error("not string token"); }
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
class t_int : public token {
public:
    t_int(uint32_t val) : val_(val) {}
    bool is_int() override { return true; }
    uint32_t get_int() override { return val_; }
private:
    uint32_t val_;
};
class t_double : public token {
public:
    t_double(double val) : val_(val) {}
    bool is_double() override { return true; }
    double get_double() override { return val_; }
private:
    double val_;
};
class t_string : public token {
public:
    t_string(const std::string& val) : val_(val) {}
    std::string get_string() override { return val_; }
private:
    std::string val_;
};

using tlist = std::list<std::unique_ptr<token>>;

#endif