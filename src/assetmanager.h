#pragma once

#include <map>
#include <utility>


template<typename K, typename V>
class AssetManager
{
public:
    AssetManager() {}

    std::map<K, V> map;

    void add(const K& key, V value)
    {
        map.insert(std::make_pair(key, value));
    }

    void remove(const K& key)
    {
        auto result = map.find(key);
        if (result != map.end()) {
            map.erase(key);
        }
    }

    V get(const K& key)
    {
        auto result = map.find(key);
        if (result == map.end()) {
            V null_ptr = nullptr;
            return null_ptr;
        }
        return result->second;
    }

    int get_count() const
    {
        return map.size();
    }
};