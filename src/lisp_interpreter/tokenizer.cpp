// tokenizer.cpp
//

#include <iostream>
#include <sstream>
#include "tokenizer.hpp"

using namespace std;

void tokenizer::tokenize(istream& input) {
    char c;
    string comment;
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
        case ';':
            getline(input, comment);
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

void tokenizer::flush() {
    if (!s_.empty()) {
        if (s_ == ".") {
            tokens_.push_back(make_unique<t_dot>());
            s_.clear();
            return;
        }
        stringstream ss(s_);
        uint32_t i;
        if (ss >> i && ss.eof()) {
            tokens_.push_back(make_unique<t_int>(i));
            s_.clear();
            return;
        }
        ss = stringstream(s_);
        double d;
        if (ss >> d && ss.eof()) {
            tokens_.push_back(make_unique<t_double>(d));
            s_.clear();
            return;
        }
        tokens_.push_back(make_unique<t_string>(s_));
        s_.clear();
    }
}
