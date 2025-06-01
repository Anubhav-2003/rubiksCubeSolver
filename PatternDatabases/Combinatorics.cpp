
#include "Combinatorics.h"

uint32_t computeFactorial(uint32_t number)
{
    return number <= 1 ? 1 : number * computeFactorial(number - 1);
}

uint32_t calculatePermutations(uint32_t totalItems, uint32_t selectedItems)
{
    return computeFactorial(totalItems) / computeFactorial(totalItems - selectedItems);
}

// Calculates combinations (nCk): n! / ((n - k)! * k!)
uint32_t calculateCombinations(uint32_t totalItems, uint32_t selectedItems)
{
    return (totalItems < selectedItems)
           ? 0
           : computeFactorial(totalItems) / (computeFactorial(totalItems - selectedItems) * computeFactorial(selectedItems));
}
