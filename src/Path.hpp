//
// Created by Twometer on 13 Nov 2021.
//

#ifndef LIBNEKO_PATH_HPP
#define LIBNEKO_PATH_HPP

#include "Vector.hpp"
#include "String.hpp"

namespace nk {

    class Path {
    private:
        Vector<String> m_parts{};
        bool m_absolute = false;

        Path() = default;

    public:
        explicit Path(const String &value);

        const Vector<String> &parts() const;

        String name() const;

        String to_string() const;

        bool is_root() const;

        bool is_absolute() const;

        Path operator+(const Path &other) const;

        static String join(const String &a, const String &b);
    };

}

#endif //LIBNEKO_PATH_HPP
