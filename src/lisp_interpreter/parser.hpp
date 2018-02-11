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

// this class analyzes list of tokens and tries to parse expressions out of it
class parser {
public:
    parser(tlist& toks, common_values& com);
    vp parse();
private:
    template<bool can_be_dotted_pair>
    vp parse_list();

    tlist& toks_;
    common_values& com_;
};

#endif
