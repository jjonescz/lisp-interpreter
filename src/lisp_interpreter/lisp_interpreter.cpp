// lisp_interpreter.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <exception>

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
// TODO: ignore comments

using tlist = list<unique_ptr<token>>;

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
            if (ss >> d) { // TODO: this will never be true...
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

// === AST ===

class expression;
using ep = shared_ptr<expression>;
using cep = const ep;
using tp = unique_ptr<token>;
using ctp = const tp;

class expression {
public:
    virtual bool is_pair() { return false; }
    // TODO: maybe use const expression* and const token*
    virtual cep& get_car() { throw runtime_error("not a pair"); }
    virtual cep& get_cdr() { throw runtime_error("not a pair"); }
    virtual ctp& get_token() { throw runtime_error("not a token"); }
};

class e_pair : public expression {
public:
    e_pair(ep car, ep cdr) : car_(move(car)), cdr_(move(cdr)) {}
    bool is_pair() override { return true; }
    cep& get_car() override { return car_; }
    cep& get_cdr() override { return cdr_; }
private:
    cep car_, cdr_;
};

class e_token : public expression {
public:
    e_token(tp val) : val_(move(val)) {}
    ctp& get_token() override { return val_; }
private:
    ctp val_;
};

// === PARSER ===

class parser_error : public runtime_error {
public:
    parser_error(const char *msg) : runtime_error(msg) {}
};

class parser {
public:
    parser(tlist& toks) : toks_(toks),
        empty_list_(make_shared<e_token>(make_unique<t_string>("()"))),
        quote_(make_shared<e_token>(make_unique<t_string>("quote"))) {}
    ep parse() {
        if (!toks_.empty()) {
            if (toks_.front()->is_left_paren()) {
                toks_.pop_front();
                return parse_list();
            }
            if (toks_.front()->is_quote()) {
                toks_.pop_front();
                return make_shared<e_pair>(quote_, make_shared<e_pair>(parse(), empty_list_));
            }
            if (toks_.front()->is_right_paren()) { throw parser_error("unexpected closing bracket"); }
            tp tok(move(toks_.front()));
            toks_.pop_front();
            return make_shared<e_token>(move(tok));
        }
        throw parser_error("syntax error");
    }
private:
    ep parse_list() {
        if (toks_.empty()) { throw parser_error("missing closing bracket"); }
        if (toks_.front()->is_right_paren()) {
            toks_.pop_front();
            return empty_list_;
        }
        ep car(parse());
        ep cdr(parse_list());
        return make_shared<e_pair>(move(car), move(cdr));
    }
    tlist& toks_;
    ep empty_list_, quote_;
};

// === MAIN ===

int main()
{
    tlist tokens;
    for (string line; getline(cin, line);)
    {
        // tokenize
        stringstream ss(line);
        tokenizer(tokens).tokenize(ss);

        parser p(tokens);
        do {
            // parse
            ep expr;
            try {
                expr = p.parse();
            }
            catch (const parser_error& e) {
                cerr << "Parsing error: " << e.what() << endl;
                break;
            }

            // evaluate
            // TODO.
            cout << expr << endl;
        } while (!tokens.empty());

        tokens.clear();
    }
    return 0;
}
