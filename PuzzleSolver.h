#ifndef PUZZLEPATHFINDER_PUZZLESOLVER_H
#define PUZZLEPATHFINDER_PUZZLESOLVER_H
#include "Graph.h"
#include "IStateGenerator.h"


class PuzzleSolver : public Graph {
private:
    void generateNodes(IStateGenerator* puzzleState);
    void generateEdges(IStateGenerator* puzzleState);

public:
    void solve(IStateGenerator* puzzleState);

};

#endif //PUZZLEPATHFINDER_PUZZLESOLVER_H