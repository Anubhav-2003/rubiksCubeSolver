
#include "MoveCountDatabase.h"

using namespace std;

MoveCountDatabase::MoveCountDatabase(const size_t totalStates)
    : moveCounts(totalStates, 0xFF), capacity(totalStates), filledEntries(0) {}

MoveCountDatabase::MoveCountDatabase(const size_t totalStates, uint8_t initialValue)
    : moveCounts(totalStates, initialValue), capacity(totalStates), filledEntries(0) {}

bool MoveCountDatabase::setMoveCount(const uint32_t index, const uint8_t moveCount) {
    uint8_t currentValue = this->getMoveCount(index);

    if (currentValue == 0xF) {
        ++this->filledEntries;
    }

    if (currentValue > moveCount) {
        this->moveCounts.set(index, moveCount);
        return true;
    }

    return false;
}

bool MoveCountDatabase::setMoveCount(const RubiksCube& cube, const uint8_t moveCount) {
    return this->setMoveCount(this->getDatabaseIndex(cube), moveCount);
}

uint8_t MoveCountDatabase::getMoveCount(const uint32_t index) const {
    return this->moveCounts.get(index);
}

uint8_t MoveCountDatabase::getMoveCount(const RubiksCube& cube) const {
    return this->getMoveCount(this->getDatabaseIndex(cube));
}

size_t MoveCountDatabase::getCapacity() const {
    return this->capacity;
}

size_t MoveCountDatabase::getFilledCount() const {
    return this->filledEntries;
}

bool MoveCountDatabase::isComplete() const {
    return this->filledEntries == this->capacity;
}

void MoveCountDatabase::writeToFile(const string& filePath) const {
    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);

    if (!writer.is_open())
        throw runtime_error("Failed to open the file for writing");

    writer.write(
        reinterpret_cast<const char*>(this->moveCounts.data()),
        this->moveCounts.storageSize()
    );

    writer.close();
}

bool MoveCountDatabase::loadFromFile(const string& filePath) {
    ifstream reader(filePath, ios::in | ios::ate);

    if (!reader.is_open())
        return false;

    size_t fileSize = reader.tellg();
    if (fileSize != this->moveCounts.storageSize()) {
        reader.close();
        throw runtime_error("Corrupt database file: size mismatch");
    }

    reader.seekg(0, ios::beg);
    reader.read(
        reinterpret_cast<char*>(this->moveCounts.data()),
        this->moveCounts.storageSize()
    );
    reader.close();

    this->filledEntries = this->capacity;
    return true;
}

vector<uint8_t> MoveCountDatabase::exportAsVector() const {
    vector<uint8_t> dataVector;
    this->moveCounts.inflate(dataVector);
    return dataVector;
}

void MoveCountDatabase::clear() {
    if (this->filledEntries != 0) {
        this->moveCounts.reset(0xFF);
        this->filledEntries = 0;
    }
}
