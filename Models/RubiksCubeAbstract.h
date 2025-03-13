#ifndef RUBIKS_CUBE_ABSTRACT_H
#define RUBIKS_CUBE_ABSTRACT_H

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

        enum class MOVE {
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

        static string getMove(MOVE move);

        void printCube() const;

        vector<MOVE> ShuffleCube(int iterations);

        RubiksCube &move(MOVE move);

        RubiksCube &invert(MOVE move);

        virtual RubiksCube &f() = 0;

        virtual RubiksCube &l() = 0;

        virtual RubiksCube &lPrime() = 0;

        virtual RubiksCube &l2() = 0;

        virtual RubiksCube &bPrime() = 0;

        virtual RubiksCube &b2() = 0;

        virtual RubiksCube &r() = 0;

        virtual RubiksCube &d() = 0;

        virtual RubiksCube &uPrime() = 0;

        virtual RubiksCube &u2() = 0;

        virtual RubiksCube &rPrime() = 0;

        virtual RubiksCube &r2() = 0;

        virtual RubiksCube &b() = 0;

        virtual RubiksCube &dPrime() = 0;

        virtual RubiksCube &d2() = 0;

        virtual RubiksCube &fPrime() = 0;

        virtual RubiksCube &f2() = 0;

        virtual RubiksCube &u() = 0;

        string getCornerColorCode(int ind) const;

        int getCornerIndex(int ind) const;

        int getCornerOrientation(int ind) const;    
}

#endif