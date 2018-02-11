// parser.cpp
//

#include <memory>
#include "parser.hpp"
#include "tokens.hpp"
#include "expressions.hpp"
#include "common_values.hpp"

using namespace std;

parser::parser(tlist& toks, common_values& com) : toks_(toks), com_(com) {}

vp parser::parse() {
    if (!toks_.empty()) {
        // beginning of a list (or a dotted pair)
        if (toks_.front()->is_left_paren()) {
            toks_.pop_front();
            return parse_list(true);
        }

        // quote special syntax
        if (toks_.front()->is_quote()) {
            toks_.pop_front();
            return make_shared<e_pair>(com_.quote_token, make_shared<e_pair>(parse(), com_.nil_token));
        }

        if (toks_.front()->is_right_paren()) { throw parser_error("unexpected closing bracket"); }
        if (toks_.front()->is_dot()) { throw parser_error("unexpected dot"); }

        // int/double/string token
        tp tok(move(toks_.front()));
        toks_.pop_front();
        return make_shared<e_token>(move(tok));
    }
    throw parser_error("syntax error");
}

// helper function for parsing lists recursively
// TODO: make this generic?
vp parser::parse_list(bool can_be_dotted_pair) {
    if (toks_.empty()) { throw parser_error("missing closing bracket"); }

    // end of list
    if (toks_.front()->is_right_paren()) {
        toks_.pop_front();
        return com_.nil_token;
    }

    // head
    vp car(parse());

    // tail
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
