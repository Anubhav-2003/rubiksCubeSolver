#include "RubiksCubeAbstract.h"

class RubiksCubeBitBoard: public RubiksCube {

private:
    uint64_t solved_config[6]{};

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
            solvedFaceConfig[face] = state[face];
        }
    }

    COLOR getColor(FACE face, unsigned row, unsigned col) const override {
        int pos = arr[row][col];
        if (pos == 8) return (COLOR)((int) face);

        uint64_t side = bitboard[(int) face];
        uint64_t color = (side >> (8 * pos)) & one_8;

        int bit_pos = 0;
        while (color != 0) {
            color = color >> 1;
            bit_pos++;
        }
        return (COLOR)(bit_pos - 1);
    }

    

}