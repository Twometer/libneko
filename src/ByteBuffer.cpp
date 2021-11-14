//
// Created by Twometer on 14 Nov 2021.
//

#include "ByteBuffer.hpp"

nk::ByteBuffer::ByteBuffer(size_t size) {
    m_buffer = new uint8_t[size];
    m_size = size;
}

nk::ByteBuffer::ByteBuffer(uint8_t *data, size_t size) {
    m_buffer = new uint8_t[size];
    memcpy(m_buffer, data, size);
    m_size = size;
}

nk::ByteBuffer::ByteBuffer(const nk::ByteBuffer &other) {
    m_buffer = new uint8_t[other.m_size];
    memcpy(m_buffer, other.m_buffer, other.m_size);
    m_size = other.m_size;
    m_position = other.m_position;
}

nk::ByteBuffer::ByteBuffer(nk::ByteBuffer &&other) noexcept {
    m_buffer = other.m_buffer;
    m_size = other.m_size;
    m_position = other.m_position;

    other.m_buffer = nullptr;
}

nk::ByteBuffer::~ByteBuffer() {
    delete[] m_buffer;
}

uint8_t nk::ByteBuffer::at(size_t index) const {
    return m_buffer[index];
}

uint8_t *nk::ByteBuffer::ptr_at(size_t index) const {
    return &m_buffer[index];
}

uint8_t &nk::ByteBuffer::operator[](size_t index) const {
    assert(m_position < m_size);
    return m_buffer[index];
}

size_t nk::ByteBuffer::position() const {
    return m_position;
}

void nk::ByteBuffer::set_position(size_t position) {
    assert(m_position < m_size);
    m_position = position;
}

void nk::ByteBuffer::move_position(long offset) {
    assert(m_position + offset < m_size);
    assert(m_position + offset >= 0);
    m_position += offset;
}
