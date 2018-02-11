// common_values.hpp
//

#ifndef _H_COMMON_VALUES
#define _H_COMMON_VALUES

#include "types.hpp"

// this class just holds pointers to values used by primitive functions
// and parser (when parsing some syntactic sugar, for example) over the
// whole program run, so that they don't have to be created every time
class common_values {
public:
	common_values();

	const vp nil_token, quote_token, true_token, eval_token;
};

#endif
