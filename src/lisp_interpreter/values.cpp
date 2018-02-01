// values.cpp
//

#include "values.hpp"
#include "visitors.hpp"

using namespace std;

cvp v_primitive::accept(visitor& v, cvp& p) const {
    return v.visit_primitive(static_pointer_cast<v_primitive>(p));
}
