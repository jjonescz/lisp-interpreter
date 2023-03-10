// tokenizer.cpp
//

#include <iostream>
#include <sstream>
#include "tokenizer.hpp"
#include "tokens.hpp"

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
        // dot can actually be part of a valid string token, so it is only
        // considered special if it stands alone (as a "whole word")
        if (s_ == ".") {
            tokens_.push_back(make_unique<t_dot>());
            s_.clear();
            return;
        }

        // try to parse int or double
        stringstream ss(s_);
        int32_t i;
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

        // everything else is a string token
        tokens_.push_back(make_unique<t_string>(s_));
        s_.clear();
    }
}
