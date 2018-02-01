// types.hpp
//

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

class expression;
class e_pair;
class e_token;
using ep = std::shared_ptr<expression>;
using cep = const ep;
using tp = std::unique_ptr<token>;
using ctp = const tp;

class visitor;
class evaluator;

class environment;

class value;
class internal_value;
class v_primitive;
class v_lambda;
using vp = std::shared_ptr<value>;
using cvp = const vp;
using prim_func = cvp(*)(evaluator&, const std::shared_ptr<e_pair>);

// TODO: are const ptrs a good idea?

#endif
