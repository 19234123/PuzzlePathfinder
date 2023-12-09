#ifndef GRAPHPATHFINDING_GRAPH_H
#define GRAPHPATHFINDING_GRAPH_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_set>

using std::string;
using std::vector;
using std::cout;
using std::endl;

class Graph {
private:
    class Node {
    public:
        int id;
        vector<int> state;
        std::map<Node*, int> neighbours {};
        int cumulativeCost = INT_MAX;
        Graph::Node* previous = nullptr;

        Node(int id, const vector<int>& state);
        void addNeighbour(Node* node, int weight);
        bool operator<(const Node& other) const;
        void resetNode();
        string toString();
    };

private:
    vector<Node*> nodeList {};
    void resetGraph();
    Node* getNodeByState(const string& state);

public:
    void addNode(const vector<int>& state);
    void addNode(Node* node);
    static void addEdge(Node* node1, Node* node2);
    static void addEdge(Node* node1, Node* node2, int weight);
    void addEdge(int nodeI1, int nodeI2, int weight);
    void addEdge(int nodeI1, int nodeI2);
    void displayGraph();
    std::map<int, vector<int>> getStates();


    vector<string> breadthFirstSearch(const string& startNodeStateRaw, const string& endNodeStateRaw);
    vector<string> depthFirstSearch();
    vector<string> dijkstraPath(const string& _startNode, const string& _endNode);
};

#endif //GRAPHPATHFINDING_GRAPH_H