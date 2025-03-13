#include "RubiksCubeAbstract.h"

class RubiksCube3DArray : public RubiksCube{
  private:
  void rotate(int idx){
    char temp_vec[3][3]={};
    for(int i=0 ;i < 3; i++){
      for(int j = 0;j < 3; j ++){
        temp_vec[i][j]=cube[idx][i][j];
      }
    }
    for (int i = 0; i < 3; i++) cube[idx][0][i] = temp_vec[2 - i][0];
    for (int i = 0; i < 3; i++) cube[idx][i][2] = temp_vec[0][i];
    for (int i = 0; i < 3; i++) cube[idx][2][2 - i] = temp_vec[i][2];
    for (int i = 0; i < 3; i++) cube[idx][2 - i][0] = temp_vec[2][2 - i];
  }
  public:
    char cube[6][3][3]{};
    RubiksCube3DArray() {
      for (int i = 0; i < 6; i++) {
          for (int j = 0; j < 3; j++) {
              for (int k = 0; k < 3; k++)
                  cube[i][j][k] = getColorCode(COLOR(i));
          }
      }
  }
  COLOR getColor(FACE face ,int row, int col) const override{
    char ch=cube[int(face)][row][col];
    switch (ch) {
      case 'B':
          return COLOR::BLUE;
      case 'R':
          return COLOR::RED;
      case 'G':
          return COLOR::GREEN;
      case 'O':
          return COLOR::ORANGE;
      case 'Y':
          return COLOR::YELLOW;
      default:
          return COLOR::WHITE;
    }
  }
  bool isSolved() const override {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (this->cube[i][j][k] == getColorCode(COLOR(i))) continue;
                return false;
            }
        }
    }
    return true;
  }
  RubiksCube &u() override {
    this->rotate(0);

    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[4][0][2 - i];
    for (int i = 0; i < 3; i++) cube[4][0][2 - i] = cube[1][0][2 - i];
    for (int i = 0; i < 3; i++) cube[1][0][2 - i] = cube[2][0][2 - i];
    for (int i = 0; i < 3; i++) cube[2][0][2 - i] = cube[3][0][2 - i];
    for (int i = 0; i < 3; i++) cube[3][0][2 - i] = temp_vec[i];
    return *this;
  }
    RubiksCube &uPrime() override {
      this->u();
      this->u();
      this->u();
      return *this;
  }
  RubiksCube &u2() override {
      this->u();
      this->u();
      return *this;
  }
  RubiksCube &l() override {
    this->rotate(1);
    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[0][i][0];
    for (int i = 0; i < 3; i++) cube[0][i][0] = cube[4][2 - i][2];
    for (int i = 0; i < 3; i++) cube[4][2 - i][2] = cube[5][i][0];
    for (int i = 0; i < 3; i++) cube[5][i][0] = cube[2][i][0];
    for (int i = 0; i < 3; i++) cube[2][i][0] = temp_vec[i];
    return *this;
  }
  RubiksCube &lPrime() override {
      this->l();
      this->l();
      this->l();
      return *this;
  }
  RubiksCube &l2() override {
      this->l();
      this->l();
      return *this;
  }
  RubiksCube &f() override {
    this->rotate(2);

    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[0][2][i];
    for (int i = 0; i < 3; i++) cube[0][2][i] = cube[1][2 - i][2];
    for (int i = 0; i < 3; i++) cube[1][2 - i][2] = cube[5][0][2 - i];
    for (int i = 0; i < 3; i++) cube[5][0][2 - i] = cube[3][i][0];
    for (int i = 0; i < 3; i++) cube[3][i][0] = temp_vec[i];
    return *this;
  }
  RubiksCube &fPrime() override {
      this->f();
      this->f();
      this->f();
      return *this;
  }
  RubiksCube &f2() override {
      this->f();
      this->f();
      return *this;
  }
  RubiksCube &r() override {
    this->rotate(3);

    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[0][2 - i][2];
    for (int i = 0; i < 3; i++) cube[0][2 - i][2] = cube[2][2 - i][2];
    for (int i = 0; i < 3; i++) cube[2][2 - i][2] = cube[5][2 - i][2];
    for (int i = 0; i < 3; i++) cube[5][2 - i][2] = cube[4][i][0];
    for (int i = 0; i < 3; i++) cube[4][i][0] = temp_vec[i];
    return *this;
  }
  RubiksCube &rPrime() override {
    this->r();
    this->r();
    this->r();
    return *this;
  }
  RubiksCube &r2() override {
      this->r();
      this->r();
      return *this;
  }
  RubiksCube &b() override {
    this->rotate(4);

    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[0][0][2 - i];
    for (int i = 0; i < 3; i++) cube[0][0][2 - i] = cube[3][2 - i][2];
    for (int i = 0; i < 3; i++) cube[3][2 - i][2] = cube[5][2][i];
    for (int i = 0; i < 3; i++) cube[5][2][i] = cube[1][i][0];
    for (int i = 0; i < 3; i++) cube[1][i][0] = temp_vec[i];
    return *this;
  }

  RubiksCube &bPrime() override {
      this->b();
      this->b();
      this->b();
      return *this;
  }
  RubiksCube &b2() override {
      this->b();
      this->b();
      return *this;
  }
  RubiksCube &d() override {
    this->rotate(5);

    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[2][2][i];
    for (int i = 0; i < 3; i++) cube[2][2][i] = cube[1][2][i];
    for (int i = 0; i < 3; i++) cube[1][2][i] = cube[4][2][i];
    for (int i = 0; i < 3; i++) cube[4][2][i] = cube[3][2][i];
    for (int i = 0; i < 3; i++) cube[3][2][i] = temp_vec[i];
    return *this;
  }
  RubiksCube &dPrime() override {
      this->d();
      this->d();
      this->d();
      return *this;
  }
  RubiksCube &d2() override {
      this->d();
      this->d();
      return *this;
  }
    bool operator==(const RubiksCube3DArray &r1) const {
      for (int i = 0; i < 6; i++) {
          for (int j = 0; j < 3; j++) {
              for (int k = 0; k < 3; k++) {
                  if (r1.cube[i][j][k] != cube[i][j][k]) return false;
              }
          }
      }
      return true;
  }
  RubiksCube3DArray &operator=(const RubiksCube3DArray &r1) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cube[i][j][k] = r1.cube[i][j][k];
            }
        }
    }
    return *this;
  }
};
  struct Hash3D {
    size_t operator()(const RubiksCube3DArray &r1) const {
        string str = "";
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    str += r1.cube[i][j][k];
                }
            }
        }
        return hash<string>()(str);
    }

  };