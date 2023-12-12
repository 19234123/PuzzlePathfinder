#include "PuzzleSolver.h"

void PuzzleSolver::solve(IStateGenerator* puzzleState) {
    generateNodes(puzzleState);
    generateEdges(puzzleState);

    string startState = puzzleState->getStartState();
    string endState = puzzleState->getEndState();
    vector<string> resultPath = dijkstraPath(startState, endState);
    puzzleState->outputResult(resultPath);
}

void PuzzleSolver::generateNodes(IStateGenerator* puzzleState) {
    for (const auto& state: puzzleState->getValidStates()) {
        addNode(state);
    }
}

void PuzzleSolver::generateEdges(IStateGenerator* puzzleState) {
    for (auto& currentNode: nodeList) {
        for (int nextNodeIndex=1; nextNodeIndex<nodeList.size(); ++nextNodeIndex) {
            Node* nextNode = nodeList[nextNodeIndex];

            if (puzzleState->validMove(currentNode->state, nextNode->state)) {
                addEdge(currentNode, nextNode);
            }
        }
    }
}