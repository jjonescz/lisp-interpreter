// lisp_interpreter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

// === TOKENS ===

class token {
public:
    virtual bool is_left_paren() { return false; }
    virtual bool is_right_paren() { return false; }
    virtual bool is_quote() { return false; }
    virtual bool is_int() { return false; }
    virtual bool is_double() { return false; }
    virtual uint32_t get_int() { throw runtime_error("not int token"); }
    virtual double get_double() { throw runtime_error("not double token"); }
    virtual string get_string() { throw runtime_error("not string token"); }
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
    t_string(const string& val) : val_(val) {}
    string get_string() override { return val_; }
private:
    string val_;
};

// === TOKENIZER ===

using tlist = vector<unique_ptr<token>>;

class tokenizer {
public:
    tokenizer(tlist& tokens) : tokens_(tokens) {}
    void tokenize(istream& input) {
        char c;
        while (input.good() && (c = input.get()) >= 0) {
            switch (c) {
            case '(':
                flush();
                tokens_.push_back(make_unique<t_left_paren>());
                break;
            case ')':
                flush();
                tokens_.push_back(make_unique<t_right_paren>());
                break;
            case '\'':
                flush();
                tokens_.push_back(make_unique<t_quote>());
                break;
            default:
                if (isspace(c)) {
                    flush();
                }
                else {
                    s_.push_back(c);
                }
                break;
            }
        }
        flush();
    }
private:
    void flush() {
        if (!s_.empty()) {
            stringstream ss(s_);
            uint32_t i;
            if (ss >> i) {
                tokens_.push_back(make_unique<t_int>(i));
                s_.clear();
                return;
            }
            double d;
            if (ss >> d) {
                tokens_.push_back(make_unique<t_double>(d));
                s_.clear();
                return;
            }
            tokens_.push_back(make_unique<t_string>(s_));
            s_.clear();
        }
    }

    string s_;
    tlist& tokens_;
};

// === PARSER ===

class parser {

};

// === MAIN ===

int main()
{
    tlist tokens;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        tokenizer(tokens).tokenize(ss);
        // TODO: do something with tokens
        tokens.clear();
    }
    return 0;
}
