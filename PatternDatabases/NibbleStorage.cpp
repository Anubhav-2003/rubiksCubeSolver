#include "NibbleStorage.h"

using namespace std;

NibbleStorage::NibbleStorage(const size_t elementCount, const uint8_t initialNibbleValue)
    : count(elementCount), byteArray((elementCount + 1) / 2, initialNibbleValue) {
}

uint8_t NibbleStorage::get(const size_t index) const {
    assert(index < count);
    size_t byteIndex = index / 2;
    uint8_t byte = byteArray.at(byteIndex);

    if (index % 2) {
        return byte & 0x0F;
    }

    return byte >> 4;
}

void NibbleStorage::set(const size_t index, const uint8_t nibbleValue) {
    assert(index < count);
    size_t byteIndex = index / 2;
    uint8_t currentByte = byteArray.at(byteIndex);

    if (index % 2) {
        byteArray.at(byteIndex) = (currentByte & 0xF0) | (nibbleValue & 0x0F);
    } else {
        byteArray.at(byteIndex) = (currentByte & 0x0F) | ((nibbleValue & 0x0F) << 4);
    }
}

uint8_t* NibbleStorage::data() {
    return byteArray.data();
}

const uint8_t* NibbleStorage::data() const {
    return byteArray.data();
}

size_t NibbleStorage::storageSize() const {
    return byteArray.size();
}

void NibbleStorage::inflate(vector<uint8_t>& output) const {
    output.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        output.push_back(get(i));
    }
}

void NibbleStorage::reset(const uint8_t nibbleValue) {
    fill(byteArray.begin(), byteArray.end(), nibbleValue);
}
