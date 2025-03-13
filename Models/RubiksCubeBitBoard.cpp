#include "RubiksCubeAbstract.h"

class RubiksCubeBitBoard: public RubiksCube {

private:
    uint64_t solvedFaceState[6]{};

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t one_eight = (1 << 8) - 1;
    uint64_t one_twenty_four = (1 << 24) - 1;

    void rotateFace(int index) {
        uint64_t side = state[index];
        side = side >> (8 * 6);
        state[index] = (state[index] << 16) | (side);
    }

     void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3) {
        uint64_t clr1 = (state[s2] & (one_eight << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr2 = (state[s2] & (one_eight << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr3 = (state[s2] & (one_eight << (8 * s2_3))) >> (8 * s2_3);

        state[s1] = (state[s1] & ~(one_eight << (8 * s1_1))) | (clr1 << (8 * s1_1));
        state[s1] = (state[s1] & ~(one_eight << (8 * s1_2))) | (clr2 << (8 * s1_2));
        state[s1] = (state[s1] & ~(one_eight << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

    int getFiveBitCorner(string corner) {
        int r = 0;
        string actual_str;
        for (auto ch: corner) {
            if (ch != 'W' && ch != 'Y') continue;
            actual_str.push_back(ch);
            if (ch == 'Y') {
                r |= (1 << 2);
            }
        }

        for (auto ch: corner) {
            if (ch != 'R' && cch != 'O') continue;
            if (ch == 'O') {
                r |= (1 << 1);
            }
        }

        for (auto ch: corner) {
            if (c != 'B' && c != 'G') continue;
            if (c == 'G') {
                r |= (1 << 0);
            }
        }

        if (corner[1] == actual_str[0]) {
            r |= (1 << 3);
        } else if (corner[2] == actual_str[0]) {
            r |= (1 << 4);
        }
        return r;
    }

public:
    uint64_t state[6]{};

    RubiksCubeBitset() {
        for (int face = 0; face < 6; face++) {
            uint64_t mask = 1 << face;
            state[face] = 0;
            for (int tile = 0; tile < 8; tile++) {
                state[face] |= mask << (8 * tile);
            }
            solvedFaceState[face] = state[face];
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int pos = arr[row][col];
        if (pos == 8) return (COLOR)((int) face);

        uint64_t side = state[(int) face];
        uint64_t color = (side >> (8 * pos)) & one_8;

        int bit_pos = 0;
        while (color != 0) {
            color = color >> 1;
            bit_pos++;
        }
        return (COLOR)(bit_pos - 1);
    }

    bool isSolved() const override {
        for (int face = 0; face < 6; face++) {
            if (solvedFaceState[face] != state[face]) return false;
        }
        return true;
    }

    RubiksCube &u() override {
        this->rotateFace(0);
        uint64_t temp = state[2] & one_24;
        state[2] = (state[2] & ~one_24) | (state[3] & one_24);
        state[3] = (state[3] & ~one_24) | (state[4] & one_24);
        state[4] = (state[4] & ~one_24) | (state[1] & one_24);
        state[1] = (state[1] & ~one_24) | temp;

        return *this;
    }

    RubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    };

    RubiksCube &u2() override {
        this->u();
        this->u();

        return *this;
    };

     RubiksCube &l() override {
        this->rotateFace(1);
        uint64_t clr1 = (state[2] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (state[2] & (one_8 << (8 * 6))) >> (8 * 6);
        uint64_t clr3 = (state[2] & (one_8 << (8 * 7))) >> (8 * 7);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        state[5] = (state[5] & ~(one_8 << (8 * 0))) | (clr1 << (8 * 0));
        state[5] = (state[5] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
        state[5] = (state[5] & ~(one_8 << (8 * 7))) | (clr3 << (8 * 7));

        return *this;

    };

    RubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    };

    RubiksCube &l2() override {
        this->l();
        this->l();

        return *this;
    };


    RubiksCube &f() override {
        this->rotateFace(2);

        uint64_t clr1 = (state[0] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (state[0] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (state[0] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

        state[3] = (state[3] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        state[3] = (state[3] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        state[3] = (state[3] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    };

    RubiksCube &f2() override {
        this->f();
        this->f();

        return *this;
    };


    RubiksCube &r() override {
        this->rotateFace(3);
        uint64_t clr1 = (state[0] & (one_8 << (8 * 2))) >> (8 * 2);
        uint64_t clr2 = (state[0] & (one_8 << (8 * 3))) >> (8 * 3);
        uint64_t clr3 = (state[0] & (one_8 << (8 * 4))) >> (8 * 4);

        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

        state[4] = (state[4] & ~(one_8 << (8 * 7))) | (clr1 << (8 * 7));
        state[4] = (state[4] & ~(one_8 << (8 * 6))) | (clr2 << (8 * 6));
        state[4] = (state[4] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &r2() override {
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &b() override {
        this->rotateFace(4);

        uint64_t clr1 = (state[0] & (one_8 << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (state[0] & (one_8 << (8 * 1))) >> (8 * 1);
        uint64_t clr3 = (state[0] & (one_8 << (8 * 2))) >> (8 * 2);

        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

        state[1] = (state[1] & ~(one_8 << (8 * 6))) | (clr1 << (8 * 6));
        state[1] = (state[1] & ~(one_8 << (8 * 7))) | (clr2 << (8 * 7));
        state[1] = (state[1] & ~(one_8 << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &b2() override {
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &d() override {
        this->rotateFace(5);

        uint64_t clr1 = (state[2] & (one_8 << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (state[2] & (one_8 << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (state[2] & (one_8 << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        state[3] = (state[3] & ~(one_8 << (8 * 4))) | (clr1 << (8 * 4));
        state[3] = (state[3] & ~(one_8 << (8 * 5))) | (clr2 << (8 * 5));
        state[3] = (state[3] & ~(one_8 << (8 * 6))) | (clr3 << (8 * 6));

        return *this;
    };

    RubiksCube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    };

    RubiksCube &d2() override {
        this->d();
        this->d();

        return *this;
    }

    
}