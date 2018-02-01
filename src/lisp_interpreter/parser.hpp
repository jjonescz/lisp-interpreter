// parser.hpp
//

#ifndef _H_PARSER
#define _H_PARSER

#include <stdexcept>
#include "expressions.hpp"
#include "tokens.hpp"

class parser_error : public std::runtime_error {
public:
    parser_error(const char *msg) : std::runtime_error(msg) {}
};

class parser {
public:
    parser(tlist& toks) : toks_(toks),
        empty_list_(std::make_shared<e_token>(std::make_unique<t_string>("()"))),
        quote_(std::make_shared<e_token>(std::make_unique<t_string>("quote"))) {}
    ep parse();
private:
    ep parse_list();

    tlist & toks_;
    ep empty_list_, quote_;
};

#endif
