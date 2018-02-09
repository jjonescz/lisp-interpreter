// list_helper.hpp
//

#ifndef _H_LIST_HELPER
#define _H_LIST_HELPER

#include "types.hpp"

class list_helper {
public:
	list_helper(value* val);
	std::size_t count();
private:
	value * val_;
};

#endif
