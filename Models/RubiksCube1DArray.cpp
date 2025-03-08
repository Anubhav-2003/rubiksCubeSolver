#include "RubiksCubeAbstarct.h"
class RubiksCube1dArray : public RubiksCube {
  private:
      static inline int getFlattenedIndex(int faceIndex, int rowIndex, int colIndex) {
          return (faceIndex * 9) + (rowIndex * 3) + colIndex;
      }
    }
  