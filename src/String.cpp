//
// Created by Twometer on 11 Nov 2021.
//

#include "String.hpp"

#include <assert.h>
#include <string.h>

void nk::String::init_from(const char *c_str, size_t length) {
    delete[] m_buffer;
    m_length = length;
    m_buffer = new char[length + 1];
    m_buffer[length] = 0;

    if (c_str != nullptr && length > 0) {
        memcpy(m_buffer, c_str, length);
    }
}

nk::String::String() : String(nullptr, 0) {
}

nk::String::String(char chr) : String(&chr, 1) {
}

nk::String::String(const char *c_str) : String(c_str, strlen(c_str)) {
}

nk::String::String(const char *c_str, size_t length) {
    this->init_from(c_str, length);
}

nk::String::String(const nk::String &other) : String(other.m_buffer, other.m_length) {
}

nk::String::String(nk::String &&other) noexcept {
    m_buffer = other.m_buffer;
    m_length = other.m_length;

    other.m_buffer = nullptr;
    other.m_length = 0;
}

nk::String::~String() {
    delete[] m_buffer;
}

const char *nk::String::c_str() const {
    return m_buffer;
}

size_t nk::String::length() const {
    return m_length;
}

bool nk::String::is_empty() const {
    return m_length == 0;
}

bool nk::String::starts_with(const nk::String &other) const {
    if (other.m_length > m_length)
        return false;

    for (size_t i = 0; i < other.length(); i++)
        if (other.m_buffer[i] != m_buffer[i])
            return false;

    return true;
}

bool nk::String::ends_with(const nk::String &other) const {
    if (other.m_length > m_length)
        return false;

    for (size_t i = 0, j = m_length - other.length(); i < other.length(); i++, j++)
        if (other.m_buffer[i] != m_buffer[j])
            return false;

    return true;
}

int nk::String::index_of(const nk::String &other) const {
    if (other.m_length > m_length)
        return -1;

    for (size_t i = 0; i < m_length; i++) {
        bool matched = true;
        for (size_t j = 0; j < other.m_length; j++) {
            if (other.m_buffer[j] != m_buffer[i + j]) {
                matched = false;
                break;
            }
        }

        if (matched)
            return (int) i;
    }

    return -1;
}

bool nk::String::contains(const nk::String &other) const {
    return this->index_of(other) != -1;
}

nk::String nk::String::append(const nk::String &other) const {
    auto new_str = nk::String();
    delete[] new_str.m_buffer;

    new_str.m_length = this->m_length + other.m_length;
    new_str.m_buffer = new char[new_str.m_length + 1];

    memcpy(new_str.m_buffer, m_buffer, m_length);
    memcpy(new_str.m_buffer + m_length, other.m_buffer, other.m_length);
    new_str.m_buffer[new_str.m_length] = 0;

    return new_str;
}

nk::String nk::String::substring(size_t start_idx) const {
    assert(start_idx < m_length);
    return nk::String(m_buffer + start_idx);
}

nk::String nk::String::substring(size_t start_idx, size_t end_idx) const {
    assert(start_idx < m_length);
    assert(end_idx < m_length);
    assert(end_idx > start_idx);
    return nk::String(m_buffer + start_idx, end_idx - start_idx);
}

nk::String nk::String::remove(size_t end_idx) const {
    assert(end_idx < m_length);
    return this->substring(0, end_idx);
}

nk::String nk::String::replace(const nk::String &replace, const nk::String &with) const {
    // TODO
    return nk::String();
}

nk::Vector<nk::String> nk::String::split(const nk::String &separator) const {
    // TODO
    return nk::Vector<nk::String>();
}

nk::String nk::String::trim() {
    size_t i = 0;
    while (i < m_length && m_buffer[i] == ' ')
        i++;

    size_t j = m_length - 1;
    while (j >= 0 && m_buffer[j] == ' ')
        j--;

    return this->substring(i, j + 1);
}

char nk::String::front() const {
    return m_buffer[0];
}

char nk::String::back() const {
    return m_buffer[m_length - 1];
}

const char *nk::String::begin() const {
    return &m_buffer[0];
}

const char *nk::String::end() const {
    return &m_buffer[m_length];
}

bool nk::String::operator==(const nk::String &other) const {
    if (m_length != other.m_length)
        return false;

    for (size_t i = 0; i < m_length; i++)
        if (m_buffer[i] != other.m_buffer[i])
            return false;

    return true;
}

nk::String nk::String::operator+(const nk::String &other) const {
    return this->append(other);
}

nk::String &nk::String::operator+=(const nk::String &other) {
    return *this = *this + other;
}

nk::String &nk::String::operator=(const nk::String &other) {
    if (&other == this)
        return *this;

    this->init_from(other.m_buffer, other.m_length);

    return *this;
}

nk::String &nk::String::operator=(nk::String &&other) noexcept {
    if (&other == this)
        return *this;

    delete[] m_buffer;

    m_buffer = other.m_buffer;
    m_length = other.m_length;

    other.m_buffer = nullptr;
    other.m_length = 0;

    return *this;
}

char nk::String::operator[](size_t index) const {
    assert(index < length());
    return m_buffer[index];
}