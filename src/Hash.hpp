//
// Created by Twometer on 13 Nov 2021.
//

#ifndef LIBNEKO_HASH_HPP
#define LIBNEKO_HASH_HPP

namespace nk {

    typedef unsigned long long hash_t;

    template<typename T>
    hash_t hash(const T &value);

}


#endif //LIBNEKO_HASH_HPP
