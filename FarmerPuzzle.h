#ifndef PUZZLEPATHFINDER_FARMERPUZZLE_H
#define PUZZLEPATHFINDER_FARMERPUZZLE_H
#include "IStateGenerator.h"

class FarmerPuzzle : public IStateGenerator {
private:
    void generateValidStates() override;
    static bool validState(const string& state);
    vector<string> validStates {};
    string startState = "0000";
    string endState = "1111";

public:
    bool validMove(const vector<int>& currentState, const vector<int>& nextState) override;
    void outputResult(const vector<string>& results) override;

    FarmerPuzzle() {
        FarmerPuzzle::generateValidStates();
    }

    [[nodiscard]] vector<string> getValidStates() const override {return this->validStates;}
    [[nodiscard]] string getStartState() const override {return this->startState;}
    [[nodiscard]] string getEndState() const override {return this->endState;}

};


#endif //PUZZLEPATHFINDER_FARMERPUZZLE_H