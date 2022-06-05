//
// Created by Twometer on 14 Nov 2021.
//

#ifndef LIBNEKO_BYTEBUFFER_HPP
#define LIBNEKO_BYTEBUFFER_HPP

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "Types.hpp"

namespace nk {

    class ByteBuffer {
    private:
        uint8_t *m_buffer;
        size_t m_size;
        size_t m_position = 0;

    public:
        explicit ByteBuffer(size_t size);

        ByteBuffer(uint8_t *data, size_t size);

        ByteBuffer(const ByteBuffer &other);

        ByteBuffer(ByteBuffer &&other) noexcept;

        ~ByteBuffer();

        uint8_t at(size_t index) const;

        uint8_t *ptr_at(size_t index) const;

        uint8_t &operator[](size_t index) const;

        size_t position() const;

        void set_position(size_t position);

        void move_position(long offset);

        u8 *data() { return m_buffer; };

        template<typename T>
        T read(size_t index) const {
            assert(index < m_size);
            assert(index + sizeof(T) < m_size);

            T data;
            memcpy(&data, m_buffer + index, sizeof(T));
            return data;
        }

        template<typename T>
        T read() {
            auto data = read<T>(m_position);
            m_position += sizeof(T);
            return data;
        }

        template<typename T>
        void write(size_t index, const T &data) const {
            assert(index < m_size);
            assert(index + sizeof(T) <= m_size);

            memcpy(m_buffer + index, &data, sizeof(T));
        }

        template<typename T>
        void write(const T &data) {
            write<T>(m_position, data);
            m_position += sizeof(T);
        }
    };

}

#endif //LIBNEKO_BYTEBUFFER_HPP
