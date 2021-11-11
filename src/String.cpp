//
// Created by Twometer on 11 Nov 2021.
//

#include "String.hpp"

#include <assert.h>
#include <string.h>

nk::String::String() : String(nullptr, 0) {
}

nk::String::String(char chr) : String(&chr, 1) {
}

nk::String::String(const char *c_str) : String(c_str, strlen(c_str)) {
}

nk::String::String(const char *c_str, size_t length) : m_length(length) {
    m_buffer = new char[length + 1];
    m_buffer[length] = 0;

    if (c_str != nullptr && length > 0) {
        memcpy(m_buffer, c_str, length);
    }
}

nk::String::String(const nk::String &other) : String(other.m_buffer, other.m_length) {
}

nk::String::String(const nk::String &&other) noexcept {
    m_buffer = other.m_buffer;
    m_length = other.m_length;
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
    return false;
}

bool nk::String::ends_with(const nk::String &other) const {
    return false;
}

int nk::String::index_of(const nk::String &other) const {
    return 0;
}

bool nk::String::contains(const nk::String &other) const {
    return false;
}

nk::String nk::String::append(const nk::String &other) const {
    return nk::String();
}

nk::String nk::String::substring(size_t offset) const {
    return nk::String();
}

nk::String nk::String::remove(size_t offset) const {
    return nk::String();
}

nk::String nk::String::replace(const nk::String &replace, const nk::String &with) const {
    return nk::String();
}

nk::Vector<nk::String> nk::String::split(const nk::String &separator) const {
    return nk::Vector<nk::String>();
}

nk::String nk::String::trim() {
    return nk::String();
}

char nk::String::front() const {
    return m_buffer[0];
}

char nk::String::back() const {
    return m_buffer[length() - 1];
}

const char *nk::String::begin() const {
    return &m_buffer[0];
}

const char *nk::String::end() const {
    return &m_buffer[length() - 1];
}

bool nk::String::operator==(const nk::String &other) const {
    if (length() != other.length())
        return false;

    for (size_t i = 0; i < length(); i++)
        if (m_buffer[i] != other.m_buffer[i])
            return false;

    return true;
}

nk::String nk::String::operator+(const nk::String &other) const {
    return this->append(other);
}

nk::String nk::String::operator+=(const nk::String &other) const {
    return nk::String();
}

char nk::String::operator[](size_t index) const {
    assert(index < length());
    return m_buffer[index];
}
