// parser.hpp
//

#ifndef _H_PARSER
#define _H_PARSER

#include <stdexcept>
#include "types.hpp"

class parser_error : public std::runtime_error {
public:
    parser_error(const std::string& msg) : std::runtime_error(msg) {}
};

class parser {
public:
    parser(tlist& toks, common_values& com);
    vp parse();
private:
    vp parse_list(bool can_be_dotted_pair);

    tlist& toks_;
    common_values& com_;
};

#endif
