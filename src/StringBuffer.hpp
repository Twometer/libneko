//
// Created by Twometer on 12 Nov 2021.
//

#ifndef LIBNEKO_STRINGBUFFER_HPP
#define LIBNEKO_STRINGBUFFER_HPP

#include <stddef.h>

#include "Vector.hpp"
#include "String.hpp"

namespace nk {

    class StringBuffer {
    private:
        Vector<char> m_buffer{};

    public:
        size_t length() const;

        bool is_empty() const;

        String to_string() const;

        StringBuffer &append(char chr);

        StringBuffer &append(const char *c_str);

        StringBuffer &append(const String &string);

        StringBuffer &append_newline();

        void clear();
    };

};

#endif //LIBNEKO_STRINGBUFFER_HPP
