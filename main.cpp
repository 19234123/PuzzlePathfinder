#include <iostream>
#include "Graph.h"

bool validMove(const vector<int>& currentState, const vector<int>& nextState) {
    // State
    // Farmer, Fox, Chicken, Grain
    bool validMove = false;

    // Check farmer has moved
    if (currentState[0] != nextState[0]) {
        std::map<int, int> movedEntities;
        int entitiesMoved = 0;
        for (int i=1; i<4; i++) {
            if (currentState[i] != nextState[i]) {
                movedEntities[i] = nextState[i];
                entitiesMoved++;
            }
        }

        // Check if exactly one entity has moved
        // Farmer is not an entity
        if (entitiesMoved == 1) {
            int foxIndex = 1;
            int chickenIndex = 2;
            int grainIndex = 3;

            // Constraints on leaving entity with another entity
            for (const auto& pair: movedEntities) {
                int currentIndex = pair.first;

                if (currentIndex == foxIndex) {
                    if (currentState[chickenIndex] == currentState[grainIndex]) {
                        validMove = false;
                        break;
                    }
                } else if (currentIndex == grainIndex) {
                    if (currentState[foxIndex] == currentState[chickenIndex]) {
                        validMove = false;
                        break;
                    }
                }
                validMove = true;
            }
        // Only farmer moves
        } else if (entitiesMoved == 0) {
            validMove = true;
        }
    }
    // Farmer hasn't moved
    return validMove;
}

bool validState(const vector<int>& state) {
    bool chickenAloneWithFox = (state[1] == state[2]) && (state[0] != state[2]);
    bool chickenAloneWithGrain = (state[2] == state[3]) && (state[0] != state[3]);
    return !chickenAloneWithFox && !chickenAloneWithGrain;
}

vector<vector<int>> generateValidStates() {
    vector<vector<int>> states;
    for (int farmer=0; farmer<2; farmer++) {
        for (int fox=0; fox<2; fox++) {
            for (int chicken=0; chicken<2; chicken++) {
                for (int grain=0; grain<2; grain++) {
                    vector<int> state = {farmer, fox, chicken, grain};
                    if (validState(state)) {
                        states.push_back(state);
                    }
                }
            }
        }
    }
    return states;
}

int main() {
    auto graph = new Graph();

    for (auto const& state: generateValidStates()) {
        graph->addNode(state);
    }

    for (const auto& state1: graph->getStates()) {
        for (const auto& state2: graph->getStates()) {
            if (validMove(state1.second, state2.second)) {
                graph->addEdge(state1.first, state2.first);
            }
        }
    }

    //graph->displayGraph();

    vector<string> results = graph->breadthFirstSearch("{0, 0, 0, 0}", "{1, 1, 1, 1}");
    for (const auto& line: results) {
        cout << line << endl;
    }
    cout << "Total moves: " << results.size()-1;
    return 0;
}