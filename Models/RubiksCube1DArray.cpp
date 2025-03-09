#include "RubiksCubeAbstarct.h"

class RubiksCube1DArray : public RubiksCube{
  private:
  static inline int flat(int idx, int row, int col){
    return (idx * 9) + (row * 3) + col;
  }
  void rotate(int idx){
    char temp_vec [9] = {};
    for(int i = 0; i < 3; i++){
      for(int j= 0 ; j < 3 ; j++){
        temp_vec[i * 3 + j] = cube [flat(idx , i , j )];
      }
    }
    for(int i = 0 ; i < 3 ; i++) {cube[flat (idx, 0 , i )] = temp_vec[flat( 0 , 2-i , 0 )];}
    for(int i = 0 ; i < 3 ; i++) {cube[flat(idx , i , 2 )]= temp_vec[flat ( 0 , 0 , i )];}
    for(int i= 0 ; i < 3 ; i++) {cube[flat(idx , 2 , 2-i )]= temp_vec[flat( 0 , i , 2 )];}
    for(int i= 0 ;i < 3 ; i++) {cube[flat(idx , 2-i ,0 )] = temp_vec[flat( 0 ,2 ,2-i )];}
  }
  public:
  char cube[54]{};
  RubiksCube1DArray() {
     for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
           for (int k = 0; k < 3; k++) {
              cube[i * 9 + j * 3 + k] = getColorCode(COLOR(i));
           }
        }
     }
  }

  COLOR getColor(FACE face, int row, int col) const override {
    char ch = cube[flat((int)face, (int)row, (int)col)];
    switch (ch) {
        case 'B': return COLOR::BLUE;
        case 'R': return COLOR::RED;
        case 'G': return COLOR::GREEN;
        case 'Y': return COLOR::YELLOW;
        case 'O': return COLOR::ORANGE;
        default: return COLOR::WHITE;
    }
  }

 bool isSolved() const override {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (this->cube[flat(i, j, k)] == getColorCode(COLOR(i))) {
                    continue;
                }
                return false;
            }
        }
    }
    return true;
  }

   RubiksCube &u() override {
    this->rotate(0);
    char temp_vec[3] = {};
    for (int i = 0; i < 3; i++) {
        temp_vec[i] = cube[flat(4, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(4, 0, 2 - i)] = cube[flat(1, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(1, 0, 2 - i)] = cube[flat(2, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(2, 0, 2 - i)] = cube[flat(3, 0, 2 - i)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(3, 0, 2 - i)] = temp_vec[i];
    }
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
    for (int i = 0; i < 3; i++) {
        temp_vec[i] = cube[flat(0, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(0, i, 0)] = cube[flat(4, 2 - i, 2)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(4, 2 - i, 2)] = cube[flat(5, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(5, i, 0)] = cube[flat(2, i, 0)];
    }
    for (int i = 0; i < 3; i++) {
        cube[flat(2, i, 0)] = temp_vec[i];
    }
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
      for (int i = 0; i < 3; i++) {
          temp_vec[i] = cube[flat(0, 2, i)];
      }
      for (int i = 0; i < 3; i++) {
          cube[flat(0, 2, i)] = cube[flat(1, 2 - i, 2)];
      }
      for (int i = 0; i < 3; i++) {
          cube[flat(1, 2 - i, 2)] = cube[flat(5, 0, 2 - i)];
      }
      for (int i = 0; i < 3; i++) {
          cube[flat(5, 0, 2 - i)] = cube[flat(3, i, 0)];
      }
      for (int i = 0; i < 3; i++) {
          cube[flat(3, i, 0)] = temp_vec[i];
      }
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
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[flat(0, 2 - i, 2)];
    for (int i = 0; i < 3; i++) cube[flat(0, 2 - i, 2)] = cube[flat(2, 2 - i, 2)];
    for (int i = 0; i < 3; i++) cube[flat(2, 2 - i, 2)] = cube[flat(5, 2 - i, 2)];
    for (int i = 0; i < 3; i++) cube[flat(5, 2 - i, 2)] = cube[flat(4, i, 0)];
    for (int i = 0; i < 3; i++) cube[flat(4, i, 0)] = temp_vec[i];
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
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[flat(0, 0, 2 - i)];
    for (int i = 0; i < 3; i++) cube[flat(0, 0, 2 - i)] = cube[flat(3, 2 - i, 2)];
    for (int i = 0; i < 3; i++) cube[flat(3, 2 - i, 2)] = cube[flat(5, 2, i)];
    for (int i = 0; i < 3; i++) cube[flat(5, 2, i)] = cube[flat(1, i, 0)];
    for (int i = 0; i < 3; i++) cube[flat(1, i, 0)] = temp_vec[i];

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
    for (int i = 0; i < 3; i++) temp_vec[i] = cube[flat(2, 2, i)];
    for (int i = 0; i < 3; i++) cube[flat(2, 2, i)] = cube[flat(1, 2, i)];
    for (int i = 0; i < 3; i++) cube[flat(1, 2, i)] = cube[flat(4, 2, i)];
    for (int i = 0; i < 3; i++) cube[flat(4, 2, i)] = cube[flat(3, 2, i)];
    for (int i = 0; i < 3; i++) cube[flat(3, 2, i)] = temp_vec[i];

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
bool operator==(const RubiksCube1DArray &r1) const {
  for (int i = 0; i < 54; i++) {
      if (cube[i] != r1.cube[i]) return false;
  }
  return true;
}

RubiksCube1DArray &operator=(const RubiksCube1DArray &r1) {
  for (int i = 0; i < 54; i++) {
      cube[i] = r1.cube[i];
  }
  return *this;
}
};
struct Hash{
  size_t operator()(const RubiksCube1DArray &r1) const{
    string s="";
    for(int i=0;i<54;i++) s+=r1.cube[i];
    return hash<string>()(s);
  }
};

  