#include "bits/stdc++.h"

using namespace std;

class RubiksCube {
    public:
        enum class FACE {
            UP, LEFT, RIGHT, FRONT, DOWN, BACK 
        };

        enum class COLOR {
            WHITE, RED, GREEN, YELLOW, BLUE, ORANGE
        };

        enum class MOVES {
            R, RPRIME, R2,
            L, LPRIME, L2,
            U, PRIME, U2,
            D, DPRIME, D2,
            F, FPRIME, F2,
            B, BPRIME, B2
        };

        virtual COLOR getColor(FACE face, int row, int col) const = 0;

        static char getColorCode(COLOR color);

        virtual bool isSolved() const = 0;

        static string getMove(MOVE index);

        void printCube() const;

        vector<MOVE> ShuffleCube(int iterations);
}