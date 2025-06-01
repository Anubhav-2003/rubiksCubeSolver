//
// Created by Lakshya Mittal on 17-02-2022.
//

#ifndef RUBIKS_CUBE_SOLVER_MOVE_COUNT_DATABASE_H
#define RUBIKS_CUBE_SOLVER_MOVE_COUNT_DATABASE_H

#include "../Models/RubiksCubeAbstract.h"
#include "NibbleArray.h"
#include <vector>
#include <string>

class MoveCountDatabase {
protected:
    NibbleArray moveCounts;
    size_t capacity;
    size_t filledEntries;

    MoveCountDatabase() = default;

public:
    explicit MoveCountDatabase(const size_t totalStates);
    MoveCountDatabase(const size_t totalStates, uint8_t initialValue);

    virtual ~MoveCountDatabase() = default;

    virtual uint32_t getDatabaseIndex(const RubiksCube& cube) const = 0;

    virtual bool setMoveCount(const RubiksCube& cube, uint8_t moveCount);
    virtual bool setMoveCount(uint32_t index, uint8_t moveCount);

    virtual uint8_t getMoveCount(const RubiksCube& cube) const;
    virtual uint8_t getMoveCount(uint32_t index) const;

    virtual size_t getCapacity() const;
    virtual size_t getFilledCount() const;
    virtual bool isComplete() const;

    virtual void writeToFile(const std::string& filePath) const;
    virtual bool loadFromFile(const std::string& filePath);

    virtual std::vector<uint8_t> exportAsVector() const;
    virtual void clear();
};

#endif
