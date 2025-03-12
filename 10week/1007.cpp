#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <random>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <map>
#include <chrono>

std::unordered_set<std::string> generate_random_strings(int count, int length) {
    std::unordered_set<std::string> strings;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis('a', 'z');

    while (strings.size() < count) {
        std::string str(length, '\0');
        for (int i = 0; i < length; ++i) {
            str[i] = dis(gen);
        }
        strings.insert(str);
    }

    return strings;
}

unsigned int RSHash(const char* str, unsigned int length) {
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = hash * a + (*str);
        a = a * b;
    }

    return hash;
}

unsigned int JSHash(const char* str, unsigned int length) {
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}

unsigned int PJWHash(const char* str, unsigned int length) {
    const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = (hash << OneEighth) + (*str);

        if ((test = hash & HighBits) != 0) {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }

    return hash;
}

unsigned int ELFHash(const char* str, unsigned int length) {
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = (hash << 4) + (*str);

        if ((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length) {
    unsigned int seed = 131;
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = (hash * seed) + (*str);
    }

    return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length) {
    unsigned int hash = 0;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

unsigned int DJBHash(const char* str, unsigned int length) {
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

unsigned int DEKHash(const char* str, unsigned int length) {
    unsigned int hash = length;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }

    return hash;
}

unsigned int APHash(const char* str, unsigned int length) {
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i) {
        hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
            (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }

    return hash;
}

int count_collisions(const std::unordered_set<std::string>& strings, unsigned int (*hash_func)(const char*, unsigned int)) {
    std::unordered_map<unsigned int, int> hash_counts;
    int collisions = 0;

    for (const auto& str : strings) {
        unsigned int hash = hash_func(str.c_str(), str.length());
        if (hash_counts.find(hash) != hash_counts.end()) {
            collisions++;
        } else {
            hash_counts[hash] = 1;
        }
    }

    return collisions;
}

int main() {
    const int string_length = 10;
    const int max_strings = 2000000;
    const int step = 100000;
    auto strings = generate_random_strings(max_strings, string_length);

    std::vector<std::pair<std::string, std::vector<int>>> collision_data = {
        {"RSHash", {}},
        {"JSHash", {}},
        {"PJWHash", {}},
        {"ELFHash", {}},
        {"BKDRHash", {}},
        {"SDBMHash", {}},
        {"DJBHash", {}},
        {"DEKHash", {}},
        {"APHash", {}}
    };

    for (int i = step; i <= max_strings; i += step) {
        std::unordered_set<std::string> subset(strings.begin(), std::next(strings.begin(), i));

        for (auto& data : collision_data) {
            if (data.first == "RSHash") data.second.push_back(count_collisions(subset, RSHash));
            else if (data.first == "JSHash") data.second.push_back(count_collisions(subset, JSHash));
            else if (data.first == "PJWHash") data.second.push_back(count_collisions(subset, PJWHash));
            else if (data.first == "ELFHash") data.second.push_back(count_collisions(subset, ELFHash));
            else if (data.first == "BKDRHash") data.second.push_back(count_collisions(subset, BKDRHash));
            else if (data.first == "SDBMHash") data.second.push_back(count_collisions(subset, SDBMHash));
            else if (data.first == "DJBHash") data.second.push_back(count_collisions(subset, DJBHash));
            else if (data.first == "DEKHash") data.second.push_back(count_collisions(subset, DEKHash));
            else if (data.first == "APHash") data.second.push_back(count_collisions(subset, APHash));
        }
    }

    for (const auto& data : collision_data) {
        std::cout << data.first << ": ";
        for (int collisions : data.second) {
            std::cout << collisions << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}