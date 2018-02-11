// environment.hpp
//

#ifndef _H_ENVIRONMENT
#define _H_ENVIRONMENT

#include <map>
#include "types.hpp"

// this class represents an environment of a lambda (or a global, root environment);
// environment is simply a dictionary containing values of variables
// possibly with a pointer to a parent environment
class environment {
public:
    environment(ep parent) : parent(move(parent)) {}
    // tries to find a slot corresponding to the specified key (recursively in parent environments, too);
    // it returns a pointer, so that the slot's value can be changed using this function, as well
    vp* try_find(std::string key);

    const ep parent;
    std::map<std::string, vp> map;
};

#endif
