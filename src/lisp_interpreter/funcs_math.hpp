// funcs_math.hpp
//

#include <vector>
#include <algorithm>
#include <numeric>
#include "evaluator.hpp"
#include "func_helpers.hpp"
#include "expressions.hpp"
#include "tokens.hpp"

using namespace std;

struct plus_func {
    static const string name;
    using handler = op_wrapper<plus_func>;
    static const int32_t neutral_ = 0;
    template<typename T> static T op_(T x, T y) { return x + y; }
};
const string plus_func::name = "+";

struct minus_func {
    static const string name;
    using handler = op_wrapper<minus_func>;
    static const int32_t neutral_ = 0;
    template<typename T> static T op_(T x, T y) { return x - y; }
};
const string minus_func::name = "-";

struct mult_func {
    static const string name;
    using handler = op_wrapper<mult_func>;
    static const int32_t neutral_ = 1;
    template<typename T> static T op_(T x, T y) { return x * y; }
};
const string mult_func::name = "*";

struct div_func {
    static const string name;
    using handler = op_wrapper<div_func>;
    static const int32_t neutral_ = 1;
    template<typename T> static T op_(T x, T y) {
        if (y == 0) { throw eval_error("division by zero"); }
        return x / y;
    }
};
const string div_func::name = "/";
