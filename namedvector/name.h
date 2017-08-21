#pragma once

#include <string>

// Bad C++ object do not fix this, consider it a char*
// It's just a wrapper to verify memory management use in named_vector
struct Name {
    Name()
    {
        ++names_in_memory;
    }

    Name(const std::string& name)
        : v(name)
    {
        ++names_in_memory;
    }

    Name(const Name& other)
    {
        v = other.v;
        ++names_in_memory;
    }

    Name& operator=(const Name& other)
    {
        v = other.v;
        return *this;
    }

    bool operator==(const Name& other) const
    {
        return v == other.v;
    }

    ~Name() noexcept
    {
        --names_in_memory;
    }

    std::string v = "";

    // Use this to make a copy of Name objects
    static Name* copy(const Name* name);

    // How many Name objects are active?
    static int names_in_memory;
};
