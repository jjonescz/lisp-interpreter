// values.cpp
//

#include "values.hpp"
#include "visitors.hpp"

using namespace std;

vp v_primitive::accept(visitor& v, vp& p) const {
    return v.visit_primitive(static_pointer_cast<v_primitive>(p));
}
