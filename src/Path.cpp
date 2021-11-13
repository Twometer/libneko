//
// Created by Twometer on 13 Nov 2021.
//

#include "Path.hpp"
#include "StringBuffer.hpp"

nk::Path::Path(const nk::String &value) {
    auto parts = value.split('/');
    for (auto part : parts) {
        auto trimmed = part.trim();
        if (trimmed.is_empty() || trimmed == ".") {
            continue;
        }
        if (!m_parts.is_empty() && trimmed == "..") {
            m_parts.pop();
            continue;
        }
        m_parts.push(trimmed);
    }

    m_absolute = !value.is_empty() && value[0] == '/';
}

const nk::Vector<nk::String> &nk::Path::parts() const {
    return m_parts;
}

nk::String nk::Path::name() const {
    if (m_parts.is_empty()) {
        return "";
    }
    return m_parts.back();
}

nk::String nk::Path::to_string() const {
    nk::StringBuffer buf;
    if (m_absolute) {
        buf.append("/");
    }

    for (const auto &part : m_parts) {
        buf.append(part).append("/");
    }

    return buf.to_string();
}

bool nk::Path::is_root() const {
    return m_parts.is_empty() && m_absolute;
}

bool nk::Path::is_absolute() const {
    return m_absolute;
}

nk::Path nk::Path::operator+(const nk::Path &other) const {
    return nk::Path(join(this->to_string(), other.to_string()));
}

nk::String nk::Path::join(const nk::String &a, const nk::String &b) {
    if (!a.ends_with("/") && !b.starts_with("/"))
        return a + "/" + b;
    else if (a.ends_with("/") && b.starts_with("/"))
        return a.substring(1) + b;
    else
        return a + b;
}
