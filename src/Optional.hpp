//
// Created by Twometer on 13 Nov 2021.
//

#ifndef LIBNEKO_OPTIONAL_HPP
#define LIBNEKO_OPTIONAL_HPP

namespace nk {

    template<typename T>
    class Optional {
    private:
        T *m_value_store = new T[1];
        bool m_filled = false;

    public:
        Optional() = default;

        Optional(const T &value) : m_filled(true) { // NOLINT(google-explicit-constructor)
            m_value_store[0] = value;
        }

        ~Optional() {
            delete[] m_value_store;
        }

        T value() {
            assert(m_filled);
            return m_value_store[0];
        }

        bool has_value() {
            return m_filled;
        }
    };

}

#endif //LIBNEKO_OPTIONAL_HPP
