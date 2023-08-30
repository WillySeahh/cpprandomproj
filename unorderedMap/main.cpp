//
// Created by Willy Seah on 28/8/23.
//

#include <iostream>
#include <list>
#include <vector>

using namespace std;

template<typename KeyType, typename ValueType>
class MyUnorderedMap {
private:
    using KeyValuePair = std::pair<KeyType, ValueType>;
    using Bucket = std::list<KeyValuePair>;
    using Buckets = std::vector<Bucket>;

    //when there is collision is a linkedlist in each bucket


    static const int defaultBucketCount = 10;

    Buckets buckets;

    int hash( KeyType key)  {
        return std::hash<KeyType>()(key) % buckets.size();
    }

public:
    MyUnorderedMap(int bucketCount = defaultBucketCount) : buckets(bucketCount) {

    }

    void insert(const KeyType& key, const ValueType& value) {
        int bucketIndex = hash(key);
        buckets[bucketIndex].emplace_back(key, value);
    }

    ValueType& operator[](const KeyType& key) {
        int bucketIndex = hash(key);
        for(auto& keyValuePair : buckets[bucketIndex]) {
            if (keyValuePair.first == key) {
                return keyValuePair.second;
            }
        }

        ValueType newValue;
        buckets[bucketIndex].emplace_back(key, newValue);
        return buckets[bucketIndex].back().second;
    }

    bool contains(const KeyType& key)  {
        int bucketIndex = hash(key);
        for(auto& keyValuePair : buckets[bucketIndex]) {
            if (keyValuePair.first == key) {
                return true;
            }
        }
        return false;
    }



};


int main() {
    MyUnorderedMap<std::string, int> map;
    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);

    std::cout << map["one"] << std::endl; // Outputs: 1

    if (map.contains("two")) {
        std::cout << "Map contains 'two'" << std::endl;
    }

    return 0;

}
