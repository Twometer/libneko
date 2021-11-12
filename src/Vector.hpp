//
// Created by Twometer on 11 Nov 2021.
//

#ifndef LIBNEKO_VECTOR_HPP
#define LIBNEKO_VECTOR_HPP

#include <stddef.h>
#include <assert.h>

namespace nk {

    template<typename T>
    class Vector {
    private:
        constexpr static int growth_factor = 2;

        T *m_buffer = nullptr;
        size_t m_length = 0;
        size_t m_capacity = 0;

    public:
        /* Constructors */
        Vector() = default;

        explicit Vector(size_t capacity) {
            m_capacity = capacity;
            m_buffer = new T[capacity];
        }

        Vector(const Vector &other) {
            m_capacity = other.m_capacity;
            m_length = other.m_length;

            for (size_t i = 0; i < m_length; i++) {
                m_buffer[i] = other.m_buffer[i];
            }
        }

        Vector(Vector &&other) noexcept {
            m_capacity = other.m_capacity;
            m_length = other.m_length;
            m_buffer = other.m_buffer;

            other.m_capacity = 0;
            other.m_length = 0;
            other.m_buffer = nullptr;
        }

        ~Vector() {
            delete[] m_buffer;
        }

        /* Operations */
        size_t length() const {
            return m_length;
        }

        size_t capacity() const {
            return m_capacity;
        }

        bool is_empty() const {
            return m_length == 0;
        }

        int index_of(const T &other) const {
            for (size_t i = 0; i < m_length; i++) {
                if (m_buffer[i] == other)
                    return (int) i;
            }
            return -1;
        }

        bool contains(const T &other) const {
            return index_of(other) != -1;
        }

        void push(const T &other) {
            ensure_capacity(++m_length);
            m_buffer[m_length - 1] = other;
        }

        void clear() {
            m_length = 0;
        }

        /* Iterator implementation */
        T &front() const {
            return m_buffer[0];
        }

        T &back() const {
            return m_buffer[m_length - 1];
        }

        T *begin() const {
            return &m_buffer[0];
        }

        T *end() const {
            return &m_buffer[m_length - 1];
        }

        /* Operators */
        T &operator[](size_t index) const {
            assert(index < m_length);
            return m_buffer[index];
        }

    private:
        void ensure_capacity(size_t min_capacity) {
            if (min_capacity < m_capacity)
                return;

            auto new_capacity = min_capacity * growth_factor;
            auto new_buffer = new T[new_capacity];

            if (m_buffer != nullptr) {
                for (size_t i = 0; i < m_length; i++) {
                    new_buffer[i] = m_buffer[i];
                }
                delete[] m_buffer;
            }

            m_capacity = new_capacity;
            m_buffer = new_buffer;
        }

    };

}


#endif //LIBNEKO_VECTOR_HPP
