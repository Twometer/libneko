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
            Entry *m_next = nullptr;
            Entry *m_prev = nullptr;
        };

        struct Bucket {
            Entry *m_head = nullptr;
            Entry *m_tail = nullptr;
            size_t m_items = 0;
            bool m_used = false;

            ~Bucket() {
                for (Entry *entry = m_head; entry != nullptr; entry = entry->m_next) {
                    delete entry;
                }
            }
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
            grow();

            auto bucket_idx = hash(key) % m_buckets.length();
            auto &bucket = m_buckets[bucket_idx];
            auto entry = new Entry({key, value});

            if (bucket.m_tail != nullptr)
                bucket.m_tail->m_next = entry;
            bucket.m_tail = entry;
            if (bucket.m_head == nullptr)
                bucket.m_head = entry;
            bucket.m_items++;
        }

        Optional<V> find(const K &key) {
            auto bucket_idx = hash(key) % m_buckets.length();
            Bucket &bucket = m_buckets[bucket_idx];

            if (!bucket.m_used)
                return Optional<V>();

            for (Entry *entry = bucket.m_head; entry->m_next != nullptr; entry = entry->m_next) {
                if (entry->m_key == key)
                    return entry->m_value;
            }

            return Optional<V>();
        }

        size_t length() {
            size_t result = 0;
            for (const Bucket &buck : m_buckets)
                result += buck.m_items;
            return result;
        }

        float load_factor() {
            return (float) length() / (float) m_buckets.length();
        }

    private:
        void grow() {
            if (load_factor() <= max_load_factor)
                return;

            // Create new buckets
            for (size_t i = 0; i < m_buckets.length(); i++) {
                m_buckets.push(Bucket{});
            }

            // Rehash
            for (const Bucket &bucket : m_buckets) {
                for (Entry *entry = bucket.m_head; entry->m_next != nullptr; entry = entry->m_next) {
                    // Recalculate hash
                    auto new_bucket_idx = hash(entry->m_key) % m_buckets.length();
                    Bucket &new_bucket = m_buckets[new_bucket_idx];

                    // Remove from old bucket
                    entry->m_prev->m_next = entry->m_next;

                    // Insert into new bucket
                    entry->m_prev = new_bucket.m_tail;
                    entry->m_next = nullptr;

                    if (new_bucket.m_tail != nullptr)
                        new_bucket.m_tail->m_next = entry;
                    new_bucket.m_tail = entry;
                    if (new_bucket.m_head == nullptr)
                        new_bucket.m_head = entry;
                }
            }
        }


    };

}

#endif //LIBNEKO_HASHMAP_HPP
