#ifndef RUBIKS_CUBE_SOLVER_NIBBLESTORAGE_H
#define RUBIKS_CUBE_SOLVER_NIBBLESTORAGE_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <cassert>

class NibbleStorage {
    size_t count;
    std::vector<uint8_t> byteArray;

public:
    NibbleStorage(const size_t elementCount, const uint8_t initialNibbleValue = 0xFF);

    uint8_t get(const size_t index) const;

    void set(const size_t index, const uint8_t nibbleValue);

    uint8_t* data();

    const uint8_t* data() const;

    size_t storageSize() const;

    void inflate(std::vector<uint8_t>& output) const;

    void reset(const uint8_t nibbleValue = 0xFF);
};

#endif
