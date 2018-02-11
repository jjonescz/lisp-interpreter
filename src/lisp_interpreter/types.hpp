// types.hpp
//

// TODO: check that shared_ptrs are copied only where they should

#ifndef _H_TYPES
#define _H_TYPES

#include <memory>
#include <list>

class token;
class t_left_paren;
class t_right_paren;
class t_quote;
class t_dot;
class t_int;
class t_double;
class t_string;
using tlist = std::list<std::unique_ptr<token>>;
using tp = std::unique_ptr<token>;

class expression;
class e_pair;
class e_token;

class visitor;
class evaluator;

class environment;
using ep = std::shared_ptr<environment>;

class value;
class internal_value;
class v_primitive;
class v_lambda;
using vp = std::shared_ptr<value>;
using prim_func = vp(*)(evaluator&, vp);

class common_values;

#endif
