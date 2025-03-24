#include<bits/stdc++.h>
using namespace std;

#include "../Models/RubiksCubeAbstract.h"
#include "DFSSolver.h"

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

template<typename R, typename H>

class IDDFSSolver {
  private:
  int max_depth;
  vector<RubiksCube::MOVE> moves;

  public:
  R rubiksCube;


  IDDFSSolver(R _rubiksCube, int _max_depth = 7) {
    rubiksCube = _rubiksCube;
    max_depth = _max_depth;
  }

  vector<RubiksCube::MOVE> solve() {
    for(int i = 1 ; i < max_depth; i++){
      DFSSolver<R,H> dfsSolver(rubiksCube,i);
      moves=dfsSolver.solve();
      if(dfsSolver.rubiksCube.isSolved()){
        rubiksCube=dfsSolver.rubiksCube;
        break;
      }
    }
    return moves;
  }
};
#endif   