//
// Created by Twometer on 13 Nov 2021.
//

#include "Hash.hpp"
#include "String.hpp"

template<>
nk::hash_t nk::hash(const char &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const unsigned char &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const int &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const unsigned int &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const long &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const unsigned long &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const long long &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const unsigned long long &value) {
    return value;
}

template<>
nk::hash_t nk::hash(const nk::String &value) {
    hash_t hash = 0;
    for (auto c : value) {
        hash = 31 * hash + c;
    }
    return hash;
}

template<>
nk::hash_t nk::hash(const char *const &value) {
    return nk::hash(nk::String(value));
}