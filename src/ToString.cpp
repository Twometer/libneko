//
// Created by Twometer on 12 Nov 2021.
//

#include <stdio.h>

#include "String.hpp"

template<>
nk::String nk::to_string(int value) {
    char str[32];
    sprintf(str, "%d", value);
    return str;
}

template<>
nk::String nk::to_string(long value) {
    char str[32];
    sprintf(str, "%ld", value);
    return str;
}

template<>
nk::String nk::to_string(const char *value) {
    return nk::String(value);
}

