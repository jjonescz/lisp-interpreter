// environment.hpp
//

#ifndef _H_ENVIRONMENT
#define _H_ENVIRONMENT

#include <map>
#include "types.hpp"

class environment {
public:
    environment(ep parent) : parent(move(parent)) {}
    const ep parent;
    std::map<std::string, vp> map;
};

#endif
