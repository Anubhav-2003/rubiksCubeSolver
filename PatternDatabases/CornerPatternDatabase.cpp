#include "CornerPatternDatabase.h"

CornerPatternDatabase::CornerPatternDatabase()
    : MoveCountDatabase(100179840) {}

CornerPatternDatabase::CornerPatternDatabase(uint8_t initialValue)
    : MoveCountDatabase(100179840, initialValue) {}

uint32_t CornerPatternDatabase::getDatabaseIndex(const RubiksCube &cube) const {
    std::array<uint8_t, 8> cornerPermutation = {
        cube.getCornerIndex(0),
        cube.getCornerIndex(1),
        cube.getCornerIndex(2),
        cube.getCornerIndex(3),
        cube.getCornerIndex(4),
        cube.getCornerIndex(5),
        cube.getCornerIndex(6),
        cube.getCornerIndex(7),
    };

    uint32_t permutationRank = this->cornerPermutationIndexer.rank(cornerPermutation);

    std::array<uint8_t, 7> cornerOrientation = {
        cube.getCornerOrientation(0),
        cube.getCornerOrientation(1),
        cube.getCornerOrientation(2),
        cube.getCornerOrientation(3),
        cube.getCornerOrientation(4),
        cube.getCornerOrientation(5),
        cube.getCornerOrientation(6),
    };

    uint32_t orientationValue =
        cornerOrientation[0] * 729 +
        cornerOrientation[1] * 243 +
        cornerOrientation[2] * 81 +
        cornerOrientation[3] * 27 +
        cornerOrientation[4] * 9 +
        cornerOrientation[5] * 3 +
        cornerOrientation[6];

    return (permutationRank * 2187) + orientationValue;
}
