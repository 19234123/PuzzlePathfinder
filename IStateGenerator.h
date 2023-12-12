#ifndef PUZZLEPATHFINDER_ISTATEGENERATOR_H
#define PUZZLEPATHFINDER_ISTATEGENERATOR_H
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::vector;
using std::map;
using std::string;
using std::cout;
using std::endl;

class IStateGenerator {
protected:
    virtual void generateValidStates() = 0;
    vector<string> validStates;
    string startState;
    string endState;

public:
    virtual bool validMove(const vector<int>& currentState, const vector<int>& nextState) = 0;
    virtual void outputResult(const vector<string>& results) = 0;
    virtual ~IStateGenerator() = default;

    [[nodiscard]] virtual vector<string> getValidStates() const = 0;
    [[nodiscard]] virtual string getStartState() const = 0;
    [[nodiscard]] virtual string getEndState() const = 0;
};
#endif //PUZZLEPATHFINDER_ISTATEGENERATOR_H