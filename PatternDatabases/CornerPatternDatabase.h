#ifndef RUBIKS_CUBE_SOLVER_CORNER_PATTERN_DATABASE_H
#define RUBIKS_CUBE_SOLVER_CORNER_PATTERN_DATABASE_H

#include "../Models/RubiksCubeAbstract.h"
#include "MoveCountDatabase.h"
#include "PermutationIndexer.h"

class CornerPatternDatabase : public PatternDatabase {
private:
    using Face = RubiksCube::FACE;

    PermutationIndexer<8> cornerPermutationIndexer;

public:
    CornerPatternDatabase();
    CornerPatternDatabase(uint8_t initialValue);

    uint32_t getDatabaseIndex(const RubiksCube& cube) const;
};

#endif
