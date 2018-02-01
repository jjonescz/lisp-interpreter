// tokenizer.hpp
//

#ifndef _H_TOKENIZER
#define _H_TOKENIZER

#include <list>
#include <string>
#include <memory>
#include <iostream>
#include "types.hpp"

class tokenizer {
public:
    tokenizer(tlist& tokens) : tokens_(tokens) {}
    void tokenize(std::istream& input);
private:
    void flush();

    std::string s_;
    tlist& tokens_;
};

#endif
