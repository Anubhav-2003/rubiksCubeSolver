#ifndef RUBIKS_CUBE_SOLVER_CORNER_PATTERN_DATABASE_BUILDER_H
#define RUBIKS_CUBE_SOLVER_CORNER_PATTERN_DATABASE_BUILDER_H

#include "CornerPatternDatabase.h"
#include "../Models/RubiksCubeBitBoard.cpp"

#include <string>
#include <queue>

class CornerPatternDatabaseBuilder {
private:
    std::string filePath;
    CornerPatternDatabase cornerDatabase;

public:
    CornerPatternDatabaseBuilder(std::string _filePath);
    CornerPatternDatabaseBuilder(std::string _filePath, uint8_t initialValue);

    bool generateDatabaseWithBFS();
};

#endif
