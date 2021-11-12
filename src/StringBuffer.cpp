//
// Created by Twometer on 12 Nov 2021.
//

#include "StringBuffer.hpp"

#include <string.h>

size_t nk::StringBuffer::length() const {
    return m_buffer.length();
}

bool nk::StringBuffer::is_empty() const {
    return m_buffer.length() == 0;
}

nk::String nk::StringBuffer::to_string() const {
    return nk::to_string(m_buffer);
}

nk::StringBuffer &nk::StringBuffer::append(char chr) {
    m_buffer.push(chr);
    return *this;
}

nk::StringBuffer &nk::StringBuffer::append(const char *c_str) {
    auto len = strlen(c_str);
    for (size_t i = 0; i < len; i++) {
        m_buffer.push(c_str[i]);
    }
    return *this;
}

nk::StringBuffer &nk::StringBuffer::append(const nk::String &string) {
    for (char c : string) {
        m_buffer.push(c);
    }
    return *this;
}

nk::StringBuffer &nk::StringBuffer::append_newline() {
    this->append('\n');
    return *this;
}

