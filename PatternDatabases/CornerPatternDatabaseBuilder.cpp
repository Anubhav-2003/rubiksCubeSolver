#include "CornerPatternDatabaseBuilder.h"

using namespace std;

CornerPatternDatabaseBuilder::CornerPatternDatabaseBuilder(string _filePath) {
    filePath = _filePath;
}

CornerPatternDatabaseBuilder::CornerPatternDatabaseBuilder(string _filePath, uint8_t initialValue) {
    filePath = _filePath;
    cornerDatabase = CornerPatternDatabase(initialValue);
}

bool CornerPatternDatabaseBuilder::generateDatabaseWithBFS() {
    RubiksCubeBitboard initialCube;
    queue<RubiksCubeBitboard> cubeQueue;
    cubeQueue.push(initialCube);
    cornerDatabase.setNumMoves(initialCube, 0);

    int currentDepth = 0;

    while (!cubeQueue.empty()) {
        int levelSize = cubeQueue.size();
        currentDepth++;

        if (currentDepth == 9) break;

        for (int i = 0; i < levelSize; i++) {
            RubiksCubeBitboard currentCube = cubeQueue.front();
            cubeQueue.pop();

            for (int moveIndex = 0; moveIndex < 18; moveIndex++) {
                auto move = RubiksCube::MOVE(moveIndex);
                currentCube.move(move);

                if ((int)cornerDatabase.getNumMoves(currentCube) > currentDepth) {
                    cornerDatabase.setNumMoves(currentCube, currentDepth);
                    cubeQueue.push(currentCube);
                }

                currentCube.invert(move);
            }
        }
    }

    cornerDatabase.toFile(filePath);
    return true;
}
