// list_helper.hpp
//

#ifndef _H_LIST_HELPER
#define _H_LIST_HELPER

#include "types.hpp"

// this class wraps a list (even empty, i.e., the nil token)
// and provides helpful functions to work with it
class list_helper {
public:
    list_helper(const vp& val);
    std::size_t count();

    class iterator {
    public:
        iterator(const vp& val) : val_(val) {}
        iterator& operator++();
        const vp& operator*();
        bool operator==(const iterator& other) const { return val_ == other.val_; }
        bool operator!=(const iterator& other) const { return val_ != other.val_; }
        const vp* operator->();
    private:
        vp val_;
    };

    iterator begin();
    iterator end() { return iterator(nullptr); }
private:
    const vp& val_;
};

#endif
