// common_values.cpp
//

#include "common_values.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

common_values::common_values() : nil_token(make_shared<e_token>(make_unique<t_string>("()"))),
    quote_token(make_shared<e_token>(make_unique<t_string>("quote"))),
    true_token(make_shared<e_token>(make_unique<t_string>("#t"))) {}
