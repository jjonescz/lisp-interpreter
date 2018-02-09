// parser.cpp
//

#include <memory>
#include "parser.hpp"
#include "tokens.hpp"
#include "expressions.hpp"

using namespace std;

parser::parser(tlist& toks) : toks_(toks),
    empty_list_(std::make_shared<e_token>(std::make_unique<t_string>("()"))),
    quote_(std::make_shared<e_token>(std::make_unique<t_string>("quote"))) {}

vp parser::parse() {
    if (!toks_.empty()) {
        if (toks_.front()->is_left_paren()) {
            toks_.pop_front();
            return parse_list(true);
        }
        if (toks_.front()->is_quote()) {
            toks_.pop_front();
            return make_shared<e_pair>(quote_, make_shared<e_pair>(parse(), empty_list_));
        }
        if (toks_.front()->is_right_paren()) { throw parser_error("unexpected closing bracket"); }
        if (toks_.front()->is_dot()) { throw parser_error("unexpected dot"); }
        tp tok(move(toks_.front()));
        toks_.pop_front();
        return make_shared<e_token>(move(tok));
    }
    throw parser_error("syntax error");
}

vp parser::parse_list(bool can_be_dotted_pair) {
    if (toks_.empty()) { throw parser_error("missing closing bracket"); }
    if (toks_.front()->is_right_paren()) {
        toks_.pop_front();
        return empty_list_;
    }
    vp car(parse());
    vp cdr;
    if (can_be_dotted_pair && !toks_.empty() && toks_.front()->is_dot()) {
        toks_.pop_front();
        cdr = parse();
        if (toks_.empty() || !toks_.front()->is_right_paren()) { throw parser_error("missing closing bracket of dotted pair"); }
        toks_.pop_front();
    }
    else {
        cdr = parse_list(false);
    }
    return make_shared<e_pair>(move(car), move(cdr));
}
