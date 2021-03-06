//
// Created by Twometer on 11 Nov 2021.
//

#ifndef LIBNEKO_STRING_HPP
#define LIBNEKO_STRING_HPP

#include <stddef.h>

#include "Vector.hpp"
#include "ToString.hpp"

namespace nk {

    class String {
    private:
        char *m_buffer{};
        size_t m_length{};

    private:
        void init_from(const char *c_str, size_t length);

    public:
        /* Constructors */
        String();

        String(char chr); // NOLINT(google-explicit-constructor)

        String(const char *c_str); // NOLINT(google-explicit-constructor)

        String(const char *c_str, size_t length);

        String(const String &other);

        String(String &&other) noexcept;

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

        String substring(size_t start_idx) const;

        String substring(size_t start_idx, size_t end_idx) const;

        String remove(size_t end_idx) const;

        String replace(const String &replace, const String &with) const;

        Vector<String> split(const String &separator) const;

        Vector<String> split(char separator) const;

        String trim();

        /* Iterator implementation */
        char front() const;

        char back() const;

        const char *begin() const;

        const char *end() const;

        /* Operators */
        bool operator==(const String &other) const;

        String operator+(const String &other) const;

        template<typename T>
        String operator+(T other) const {
            return this->append(nk::to_string(other));
        }

        String &operator+=(const String &other);

        String &operator=(const String &other);

        String &operator=(String &&other) noexcept;

        char operator[](size_t index) const;
    };

}

#endif //LIBNEKO_STRING_HPP
