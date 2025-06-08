#include<bits/stdc++.h>

#include "Models/RubiksCube1DArray.cpp"
#include "Models/RubiksCube3DArray.cpp"
#include "Models/RubiksCubeBitBoard.cpp"

#include "Solvers/BFSSolver.h"
#include "Solvers/DFSSolver.h"
#include "Solvers/IDAStarSolver.h"
#include "Solvers/IDDFSSolver.h"

#include "PatternDatabases/CornerPatternDatabaseBuilder.h"

using namespace std;

int main(){
  RubiksCube3DArray object3DArray;
  RubiksCube1DArray object1DArray;
  RubiksCubeBitBoard objectBitborad;

  object3DArray.printCube();

  if(object3DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(object1DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(objectBitborad.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  objectBitborad.u();
  object3DArray.u();
  object1DArray.u();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.l();
  object3DArray.l();
  object1DArray.l();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.f();
  object3DArray.f();
  object1DArray.f();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.r();
  object3DArray.r();
  object1DArray.r();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.b();
  object3DArray.b();
  object1DArray.b();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.d();
  object3DArray.d();
  object1DArray.d();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  if(object3DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(object1DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(objectBitborad.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  objectBitborad.dPrime();
  object3DArray.dPrime();
  object1DArray.dPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.bPrime();
  object3DArray.bPrime();
  object1DArray.bPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.rPrime();
  object3DArray.rPrime();
  object1DArray.rPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.fPrime();
  object3DArray.fPrime();
  object1DArray.fPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.lPrime();
  object3DArray.lPrime();
  object1DArray.lPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  objectBitborad.uPrime();
  object3DArray.uPrime();
  object1DArray.uPrime();
  objectBitborad.printCube();
  object3DArray.printCube();
  object1DArray.printCube();

  if(object3DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(object1DArray.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  if(objectBitborad.isSolved()) cout<<"Solved\n\n";
  else cout<<"Not Solved\n\n";

  //Creates2Cubes***************************************************************

  RubiksCube3DArray cube1;
  RubiksCube3DArray cube2;

  RubiksCube1DArray cube1;
  RubiksCube1DArray cube2;

  RubiksCubeBitBoard cube1;
  RubiksCubeBitBoard cube2;

  //Equality And Assignment of Cube*********************************************

  if(cube1 == cube2) cout << "Is Equal\n";
  else cout << "Not Equal\n";

  cube1.ShuffleCube(1);

  if(cube1 == cube2) cout << "Is Equal\n";
  else cout << "Not Equal\n";

  cube2 = cube1;
  if(cube1 == cube2) cout << "Is Equal\n";
  else cout << "Not Equal\n";


  // Unordered_map of Cubes*****************************************************
  unordered_map<RubiksCube3DArray,bool,Hash3D>mp1;

  unordered_map<RubiksCube1DArray,bool,Hash>mp1;

  unordered_map<RubiksCubeBitBoard,bool,CubeBitboardHash>mp1;
  mp1[cube1] = true;
  cube2.ShuffleCube(8);
  if(mp1[cube1]) cout << "Cube1 is Present"<<"\n";
  else cout << "Cube1 is Not Present\n";

  if(mp1[cube2]) cout<<"Cube2 is Present\n";
  else cout << "Cube2 is Not Present\n";

  //DFS Testing*****************************************************************

  RubiksCube3DArray cube;
  cube.printCube();

  vector<RubiksCube:: MOVE> shuffle_move=cube.ShuffleCube(6);
  for(auto move:shuffle_move) cout<< cube.getMove(move)<<" ";
  cout<<"\n";
  cube.printCube();

  DFSSolver<RubiksCube3DArray,Hash3D>dfssolver(cube,8);
  vector<RubiksCube::MOVE>solve_moves=dfssolver.solve();

  for(auto move:solve_moves) cout<<cube.getMove(move)<<" ";
  cout<<"\n";
  dfssolver.rubiksCube.printCube();


  //BFS Solver Testing**********************************************************

  RubiksCubeBitBoard cube;
  cube.printCube();

  vector<RubiksCube::MOVE>shuffle_move=cube.ShuffleCube(6);
  for(auto move: shuffle_move) cout<<cube.getMove(move)<<" ";
  cout<<"\n";
  cube.printCube();

  bfs_solver<RubiksCubeBitBoard,CubeBitboardHash>bfssolver(rubkis_cube);
  vector<RubiksCube::MOVE>solve_moves=bfssolver.solve();

  for(auto move:solve_moves) cout << cube.getMove(move)<<" ";
  cout<<"\n";
  bfssolver.rubkisCube.printCube();
  
  //IDDFS Testing***************************************************************

  RubiksCubeBitBoard cube;
  cube.printCube();
  vector<RubiksCube::MOVE>shuffle_move=cube.ShuffleCube(7);
  for(auto move: shuffle_move) cout<<cube.getMove(move)<<" ";
  cout<<"\n";
  cube.printCube();
  IDDFSSolver<RubiksCubeBitBoard,CubeBitboardHash>iddfsSolver(cube,7);
  vector<RubiksCube::MOVE>solve_moves=iddfsSolver.solve();
  for(auto move:solve_moves) cout << cube.getMove(move)<<" ";
  cout<<"\n";
  iddfsSolver.rubiksCube.printCube();

  //IDA* Solver*****************************************************************

  RubiksCubeBitBoard cube;
  cube.printCube();
  vector<RubiksCube::MOVE>shuffle_move=cube.ShuffleCube(5);
  for(auto move: shuffle_move) cout<<cube.getMove(move)<<" ";
  cout<<"\n";
  cube.printCube();

  ida_star_solver<RubiksCubeBitBoard,CubeBitboardHash>idastarSolver(cube);
  vector<RubiksCube::MOVE>solve_moves=idastarSolver.find_solution();
  for(auto move:solve_moves) cout << cube.getMove(move)<<" ";
  cout<<"\n";
  idastarSolver.initial_cube.printCube();

  //CornerPatternDatabases Testing**********************************************
  CornerPatternDatabase cornerDB;
  RubiksCubeBitBoard cube;
  cube.printCube();

  cout<<(int)cornerDB.getMoveCount(cube)<<"\n";

  cornerDB.setMoveCount(cube,5);

  cout<<(int)cornerDB.getMoveCount(cube)<<"\n";
  cube.ShuffleCube(1);
  cube.printCube();
  cout<<(int)cornerDB.getMoveCount(cube)<<"\n";
  cornerDB.setMoveCount(cube,6);
  cout<<(int)cornerDB.getMoveCount(cube)<<"\n";

  //CornerDBMakerTesting********************************************************
  std::string fileName = "C:\\Users\\BIT\\OneDrive\\Desktop\\RubiksCube\\rubiks-cube-solver\\Databases\\cornerDepth5V1.txt";
  //Code to create Corner Database
  CornerPatternDatabaseBuilder dbMaker(fileName, 0x99);
  dbMaker.generateDatabaseWithBFS();

  RubiksCubeBitBoard cube;
  auto shuffle=cube.ShuffleCube(13);
  cube.printCube();
  for(auto moves:shuffle) cout<<cube.getMove(moves)<<" ";
  cout<<"\n";
  ida_star_solver<RubiksCubeBitBoard,CubeBitboardHash>idAstarSolver(cube,fileName);
  auto move=idAstarSolver.find_solution();
  idAstarSolver.initial_cube.printCube();
  for(auto moves: move) cout<<cube.getMove()<<" ";
  cout<<"\n";
  return 0;


  
}