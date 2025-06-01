#ifndef RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H
#define RUBIKS_CUBE_SOLVER_PERMUTATIONINDEXER_H

#include <array>
#include <bitset>
#include <cstdint>
#include <cmath>

template <size_t N, size_t K = N>
class PermutationIndexer {
    std::array<uint32_t, (1 << N) - 1> onesCountTable;

    std::array<uint32_t, K> positionWeights;

public:

    PermutationIndexer() {
        for (uint32_t i = 0; i < (1 << N) - 1; ++i) {
            std::bitset<N> bits(i);
            this->onesCountTable[i] = bits.count();
        }

        for (uint32_t i = 0; i < K; ++i) {
            this->positionWeights[i] = pick(N - 1 - i, K - 1 - i);
        }
    }

    uint32_t rank(const std::array<uint8_t, K>& permutation) const {
        std::array<uint32_t, K> lehmerCode;
        std::bitset<N> usedDigits;

        lehmerCode[0] = permutation[0];
        usedDigits[N - 1 - permutation[0]] = 1;

        for (uint32_t i = 1; i < K; ++i) {
            usedDigits[N - 1 - permutation[i]] = 1;

            uint32_t shiftedBits = usedDigits.to_ulong() >> (N - permutation[i]);
            uint32_t smallerUsedBefore = this->onesCountTable[shiftedBits];

            lehmerCode[i] = permutation[i] - smallerUsedBefore;
        }

        uint32_t rankIndex = 0;
        for (uint32_t i = 0; i < K; ++i) {
            rankIndex += lehmerCode[i] * this->positionWeights[i];
        }

        return rankIndex;
    }

private:

    static uint32_t pick(uint32_t n, uint32_t k) {
        uint32_t result = 1;
        for (uint32_t i = 0; i < k; ++i)
            result *= (n - i);
        return result;
    }
};

#endif
