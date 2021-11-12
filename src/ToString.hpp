//
// Created by Twometer on 12 Nov 2021.
//

#ifndef LIBNEKO_TOSTRING_HPP
#define LIBNEKO_TOSTRING_HPP

namespace nk {

    class String;

    template<typename T>
    String to_string(const T &value);

};

#endif //LIBNEKO_TOSTRING_HPP
