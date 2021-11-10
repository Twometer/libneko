//
// Created by Twometer on 11 Nov 2021.
//

#ifndef LIBNEKO_STRING_HPP
#define LIBNEKO_STRING_HPP

#include "Vector.hpp"
#include <cstddef>

namespace nk {

    class String {
    private:
        const char *m_buffer = nullptr;
        size_t m_length = 0;

    public:
        /* Constructors */
        String();

        String(char chr);

        String(const char *c_str);

        String(const char *c_str, size_t length);

        String(const String &other);

        String(const String &&other);

        ~String();

        /* Operations */
        const char *c_str() const;

        size_t length() const;

        bool is_empty() const;

        bool starts_with(const String &other) const;

        bool ends_with(const String &other) const;

        int index_of(const String &other) const;

        bool contains(const String &other) const;

        String append(const String &other) const;

        String substring(size_t offset) const;

        String remove(size_t offset) const;

        String replace(const String &replace, const String &with) const;

        Vector<String> split(const String &separator) const;

        String trim();

        /* Iterator implementation */
        char front() const;

        char back() const;

        const char *begin() const;

        const char *end() const;
    };

}

#endif //LIBNEKO_STRING_HPP
