// environment.cpp
//

#include "environment.hpp"

using namespace std;

vp environment::try_find(string key) {
    auto v = map.find(key);
    if (v != map.end()) {
        return v->second;
    }
    if (parent) { return move(parent->try_find(key)); }
    return nullptr;
}
