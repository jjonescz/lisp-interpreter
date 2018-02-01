// environment.hpp
//

#ifndef _H_ENVIRONMENT
#define _H_ENVIRONMENT

#include <map>
#include "types.hpp"

class environment {
public:
    environment(const environment& parent) : parent(parent) {}
    const environment& parent;
    std::map<std::string, ep> map; // TODO: map field should be read-only
};

#endif
