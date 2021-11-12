//
// Created by Twometer on 12 Nov 2021.
//

#include <stdio.h>

#include "String.hpp"
#include "StringBuffer.hpp"

template<>
nk::String nk::to_string(const int &value) {
    char str[32];
    sprintf(str, "%d", value);
    return str;
}

template<>
nk::String nk::to_string(const long &value) {
    char str[32];
    sprintf(str, "%ld", value);
    return str;
}

template<>
nk::String nk::to_string(const char *const &value) {
    return nk::String(value);
}

template<>
nk::String nk::to_string(const nk::Vector<char> &value) {
    return nk::String(value.begin(), value.length());
}

template<>
nk::String nk::to_string(const nk::StringBuffer &value) {
    return value.to_string();
}