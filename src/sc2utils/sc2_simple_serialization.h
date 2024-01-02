// Simple functions for serializing structures.

#pragma once

#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

namespace sc2 {

template <class Stream>
bool IsReading(const Stream& /*stream*/) {
    return typeid(Stream) == typeid(std::ifstream);
}

// Strings.
static inline void SerializeT(std::ifstream& s, std::string& t) {
    std::getline(s, t);
}

static inline void SerializeT(std::ofstream& s, const std::string& t) {
    s << t << std::endl;
}

// Bools.
static inline void SerializeT(std::ifstream& s, bool& t) {
    std::string linein;
    if (!std::getline(s, linein)) {
        return;
    }

    t = std::stoi(linein) == 1;
}

void inline SerializeT(std::ofstream& s, bool t) {
    if (t) {
        s << "1" << std::endl;
    } else {
        s << "0" << std::endl;
    }
}

// All other types, assumed to be 32-bit.
template <typename T>
void SerializeT(std::ifstream& s, T& t) {
    std::string linein;
    if (!std::getline(s, linein)) {
        return;
    }

    t = static_cast<T>(std::stoi(linein));
}

template <typename T>
void SerializeT(std::ofstream& s, T t) {
    s << std::to_string(static_cast<uint32_t>(t)) << std::endl;
}

static inline void SerializeT(std::ofstream& data_file, const std::set<uint32_t>& s) {
    data_file << std::to_string(s.size()) << std::endl;
    for (auto it : s) {
        data_file << std::to_string(it) << std::endl;
    }
}

static inline void SerializeT(std::ifstream& data_file, std::set<uint32_t>& s) {
    uint32_t set_size = 0;
    SerializeT<uint32_t>(data_file, set_size);
    for (uint32_t i = 0; i < set_size; ++i) {
        uint32_t value = 0;
        SerializeT<uint32_t>(data_file, value);
        s.insert(value);
    }
}

}  // namespace sc2
