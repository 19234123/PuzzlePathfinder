#include <iostream>
#include "PuzzleSolver.h"
#include "FarmerPuzzle.h"

int main() {
    auto* puzzleSolver = new PuzzleSolver();
    IStateGenerator* puzzle = new FarmerPuzzle();

    puzzleSolver->solve(puzzle);

    return 0;
}