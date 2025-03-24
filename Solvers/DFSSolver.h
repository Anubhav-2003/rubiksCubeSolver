#include<bits/stdc++.h>
using namespace std;

#include "../Models/RubiksCubeAbstract.h"


#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H

template<typename R, typename H>

class DFSSolver{
  private:
  vector<RubiksCube::MOVE>moves;
  int max_depth;


  bool dfs(int depth){
    if(rubiksCube . isSolved()){
      return true;
    }
    if(depth > max_depth) return false;
    for(int i = 0; i < 18 ; i++){
      rubiksCube.move( RubiksCube::MOVE(i));
      moves.push_back( RubiksCube::MOVE(i));
      if(dfs (depth + 1 ) ) return true;
      moves.pop_back();
      rubiksCube.invert( RubiksCube::MOVE (i) );
    }
    return false;
  }



  public:
  R rubiksCube;
  DFSSolver (R _rubiksCube , int _max_depth=8){
    this->rubiksCube =_rubiksCube;
    this->max_depth= _max_depth;
  }
  vector<RubiksCube::MOVE>solve(){
    dfs(1);
    return moves;
  }

};

#endif