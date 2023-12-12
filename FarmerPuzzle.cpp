#include "FarmerPuzzle.h"

void FarmerPuzzle::generateValidStates() {
    for (int farmer = 0; farmer<2; farmer++) {
        for (int fox = 0; fox<2; fox++) {
            for (int chicken = 0; chicken<2; chicken++) {
                for (int grain = 0; grain<2; grain++) {
                    string state = std::to_string(farmer) + std::to_string(fox)
                                 + std::to_string(chicken) + std::to_string(grain);

                    if (validState(state)) {
                        FarmerPuzzle::validStates.push_back(state);
                    }
                }
            }
        }
    }
}

bool FarmerPuzzle::validState(const string& state) {
    bool chickenAloneWithFox = (state[1] == state[2]) && (state[0] != state[2]);
    bool chickenAloneWithGrain = (state[2] == state[3]) && (state[0] != state[3]);
    return !chickenAloneWithFox && !chickenAloneWithGrain;
}

bool FarmerPuzzle::validMove(const vector<int> &currentState, const vector<int> &nextState) {
    // State
    // Farmer, Fox, Chicken, Grain
    bool validMove = false;
    int agentIndex = 0;

    // Check farmer has moved
    if (currentState[agentIndex] != nextState[agentIndex]) {
        std::map<int, int> movedEntities;
        int entitiesMoved = 0;
        for (int i = 1; i<4; ++i) {
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
            for (const auto &pair: movedEntities) {
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

void FarmerPuzzle::outputResult(const vector<string>& results) {
    string riverBanks[2];
    map<int, string> characters {
            {0, "Farmer"},
            {1, "Fox"},
            {2, "Chicken"},
            {3, "Grain"},
    };

    for (int i=0; i<results.size()-1; ++i) {
        string currentState = results[i];
        string nextState = results[i+1];
        riverBanks[0] = "";
        riverBanks[1] = "";

        string entityString;
        int entityValue;
        for (int stateIndex=0; stateIndex<currentState.size(); stateIndex++) {
            entityValue = currentState[stateIndex] - '0';
            if (stateIndex != 0 && currentState[stateIndex] != nextState[stateIndex]) {
                if (entityValue == 0) {
                    entityString = characters[stateIndex] + " across the river";
                } else {
                    entityString = characters[stateIndex] + " back";
                }

            }
            int characterIndex = entityValue;
            riverBanks[characterIndex] += characters[stateIndex] + " ";
        }

        cout << riverBanks[0] << endl;
        cout << "----------------------" << endl;
        cout << endl << endl;
        cout << "----------------------" << endl;
        cout << riverBanks[1] << endl;

        std::cin.ignore();

        if (entityString.empty()) {
            if (currentState[0] == 0) {
                cout << "The farmer crossed the river" << endl;
            } else {
                cout << "The farmer goes back" << endl;
            }

        } else {
            cout << "The farmer takes the " << entityString << endl;
        }
    }
    cout << endl;
    cout << "----------------------" << endl;
    cout << endl << endl;
    cout << "----------------------" << endl;
    cout << "Farmer Fox Chicken Grain" << endl;

    cout << endl << "Finished!" << endl;
    cout << "Total moves: " << results.size()-1;
}