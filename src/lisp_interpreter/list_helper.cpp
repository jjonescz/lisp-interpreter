// list_helper.cpp
//

#include "list_helper.hpp"
#include "values.hpp"

using namespace std;

list_helper::list_helper(const vp& val) : val_(val) {
    if (!val->is_list_or_nil()) {
        throw runtime_error("not a list");
    }
}

size_t list_helper::count() {
    size_t c = 0;
    for (auto& x : *this) {
        ++c;
    }
    return c;
}

list_helper::iterator& list_helper::iterator::operator++() {
    val_ = val_->get_cdr();
    if (val_->is_token()) { // end of list is represented by nullptr, instead of "()" token
        val_ = nullptr;
    }
    return *this;
}

const vp& list_helper::iterator::operator*() {
    return val_->get_car();
}

const vp* list_helper::iterator::operator->() {
    return &val_->get_car();
}
