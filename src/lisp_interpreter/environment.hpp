// environment.hpp
//

#ifndef _H_ENVIRONMENT
#define _H_ENVIRONMENT

#include <map>
#include "expressions.hpp"

class environment {
public:
    environment(const environment& parent) : parent(parent) {}
    const environment& parent;
    std::map<std::string, cep> map;
};

#endif
