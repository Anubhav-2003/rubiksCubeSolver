#include "RubiksCubeAbstarct.h"
class RubiksCube1DArray : public RubiksCube {
  private:
      static inline int getFlattenedIndex(int faceIndex, int rowIndex, int colIndex) {
          return (faceIndex * 9) + (rowIndex * 3) + colIndex;
      }
      void rotate(int faceIndex){
        char temp_vec[9]={};
        for(int i=0;i<3;i++){
          for(int j=0;j<3;j++){
            temp_vec[i*3+j]=cube[getFlattenedIndex(faceIndex,i,j)];
          }
        }
        

      }
    }

  