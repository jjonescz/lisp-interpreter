// environment.hpp
//

#ifndef _H_ENVIRONMENT
#define _H_ENVIRONMENT

#include <map>
#include "types.hpp"

class environment {
public:
    environment(std::unique_ptr<environment> parent) : parent(move(parent)) {}
    const std::unique_ptr<environment> parent;
    std::map<std::string, vp> map;
};

#endif
