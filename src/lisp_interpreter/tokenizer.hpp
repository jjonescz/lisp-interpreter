// tokenizer.hpp
//

#ifndef _H_TOKENIZER
#define _H_TOKENIZER

#include <list>
#include <string>
#include <memory>
#include <iostream>
#include "types.hpp"

// this class parses input stream of characters into a list of tokens
class tokenizer {
public:
    tokenizer(tlist& tokens) : tokens_(tokens) {}
    void tokenize(std::istream& input);
private:
    void flush();

    std::string s_; // character buffer
    tlist& tokens_;
};

#endif
