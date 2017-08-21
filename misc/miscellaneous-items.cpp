#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"

// Simple int-wrapper that prints constructor calls
struct wrapper {
    explicit wrapper(int val) : val(val) {
        std::cout << "constructor " << val << std::endl;
    }
    wrapper(const wrapper& w) {
        val = w.val;
        std::cout << "copy constructor " << val << std::endl;
    }
    wrapper(wrapper&& w) noexcept {
        using std::swap;
        swap(val, w.val);
        std::cout << "move constructor " << val << std::endl;
    }
    ~wrapper() noexcept {
        std::cout << "destructor " << val << std::endl;
    }
    wrapper& operator=(const wrapper& w) {
        std::cout << "assignment " << val << std::endl;
        this->val = w.val;
        return *this;
    }
    wrapper& operator=(wrapper&& w) noexcept {
        std::cout << "move assignment " << val << std::endl;
        using std::swap;
        swap(val, w.val);
        return *this;
    }
    int val{-1};
};


// Memory allocation differences between push_back vs emplace_back
void push_vs_emplace() {
    std::vector<wrapper> v; v.reserve(2);
    v.push_back(wrapper(1));
    v.push_back(wrapper(2));
}

// Memory allocation differences in for-each with auto and auto&
void range_for_auto() {
    std::vector<wrapper> v; v.reserve(2);
    v.emplace_back(1);
    v.emplace_back(2);

    std::cout << "\nvector initialized\n" << std::endl;

    for (auto x : v) {
        std::cout << x.val << std::endl;
    }
}

int main(void) {
    //push_vs_emplace();
    //range_for_auto();
}
