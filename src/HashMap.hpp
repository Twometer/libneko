//
// Created by Twometer on 13 Nov 2021.
//

#ifndef LIBNEKO_HASHMAP_HPP
#define LIBNEKO_HASHMAP_HPP

#include "Optional.hpp"
#include "Vector.hpp"
#include "Hash.hpp"

namespace nk {

    template<typename K, typename V>
    class HashMap {
    private:
        static constexpr float max_load_factor = 0.75f;
        static constexpr size_t default_capacity = 8;

        struct Entry {
            K m_key;
            V m_value;
        };

        struct Bucket {
            nk::Vector<Entry> m_entries{};
            bool m_used = false;
        };

        nk::Vector<Bucket> m_buckets{};

    public:
        HashMap() : HashMap(default_capacity) {
        }

        explicit HashMap(size_t capacity) {
            for (size_t i = 0; i < capacity; i++) {
                m_buckets.push(Bucket{});
            }
        }

        void insert(const K &key, const V &value) {
            auto bucket_idx = hash(key) % m_buckets.length();
            auto &bucket = m_buckets[bucket_idx];
            bucket.m_used = true;
            bucket.m_entries.push(Entry{key, value});
        }

        Optional<V> find(const K &key) {
            auto bucket_idx = hash(key) % m_buckets.length();
            Bucket &bucket = m_buckets[bucket_idx];

            if (!bucket.m_used)
                return Optional<V>();

            for (const Entry &entry : bucket.m_entries)
                if (entry.m_key == key)
                    return entry.m_value;

            return Optional<V>();
        }

        size_t length() {
            size_t result = 0;
            for (const Bucket &buck : m_buckets)
                result += buck.m_entries.length();
            return result;
        }

    private:
        void rehash() {

        }


    };

}

#endif //LIBNEKO_HASHMAP_HPP
