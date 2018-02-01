// parser.cpp
//

#include "parser.hpp"

using namespace std;

ep parser::parse() {
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

ep parser::parse_list() {
    if (toks_.empty()) { throw parser_error("missing closing bracket"); }
    if (toks_.front()->is_right_paren()) {
        toks_.pop_front();
        return empty_list_;
    }
    ep car(parse());
    ep cdr(parse_list());
    return make_shared<e_pair>(move(car), move(cdr));
}
