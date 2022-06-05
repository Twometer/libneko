//
// Created by twome on 30/05/2022.
//

#ifndef PRISM_MATH_HPP
#define PRISM_MATH_HPP

namespace nk {
    template<typename T>
    T max(const T &left, const T &right) {
        return left > right ? left : right;
    }

    template<typename T>
    T min(const T &left, const T &right) {
        return left < right ? left : right;
    }
};

#endif //PRISM_MATH_HPP
