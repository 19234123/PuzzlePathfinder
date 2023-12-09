#include "Graph.h"

/**
 * Node
 */
Graph::Node::Node(int id, const vector<int>& state) {
    this->id = id;
    this->state = state;
}

void Graph::Node::addNeighbour(Graph::Node* node, int weight) {
    auto it = neighbours.find(node);
    if (it == neighbours.end()) {
        neighbours[node] = weight;
    }
}

bool Graph::Node::operator<(const Graph::Node &other) const {
    return state < other.state;
}

void Graph::Node::resetNode() {
    this->previous = nullptr;
    this->cumulativeCost = INT_MAX;
}

string Graph::Node::toString() {
    string stateString = "State: {";
    for (int i=0; i<state.size(); i++) {
        stateString += std::to_string(state[i]);
        if (i != state.size()-1) {
         stateString += ", ";
        }
    }
    stateString += "}";
    return stateString;
}


/**
 * Graph
 */
void Graph::resetGraph() {
    for (auto& node: nodeList){
        node->resetNode();
    }
}

std::map<int, vector<int>> Graph::getStates() {
    std::map<int, vector<int>> states;
    for (const auto& node: nodeList) {
        states[node->id] = node->state;
    }
    return states;
}

void Graph::displayGraph() {
    for (const auto& node: nodeList) {
        cout << node->toString() << endl;
        cout << "Neighbours: ";
        for (const auto& pair: node->neighbours) {
            cout << pair.first->toString() + ", ";
        }
        cout << endl << endl;
    }
    cout << endl;
}


/**
 * addNode()
 * addEdge()
 */

void Graph::addNode(const vector<int>& state) {
    int id = (int)nodeList.size();
    addNode(new Node(id, state));
}

void Graph::addNode(Graph::Node* node) {
    nodeList.push_back(node);
}

void Graph::addEdge(Node* node1, Node* node2, int weight) {
    node1->addNeighbour(node2, weight);
    node2->addNeighbour(node1, weight);
}

void Graph::addEdge(Graph::Node *node1, Graph::Node *node2) {
    node1->addNeighbour(node2, 1);
    node2->addNeighbour(node1, 1);
}

void Graph::addEdge(int nodeI1, int nodeI2, int weight) {
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for (auto& node: nodeList) {
        int currentNodeId = node->id;
        if (currentNodeId == nodeI1) {
            node1 = node;
        } else if (currentNodeId == nodeI2) {
            node2 = node;
        }
    }

    if (node1 != nullptr && node2 != nullptr) {
        addEdge(node1, node2, weight);
    }
}

void Graph::addEdge(int nodeI1, int nodeI2) {
    addEdge(nodeI1, nodeI2, 1);

}


/**
 * Pathfinding algorithms
 */
vector<string> Graph::breadthFirstSearch(const string& startNodeStateRaw, const string& endNodeStateRaw) {
    vector<string> results;
    std::queue<Node*> queue;
    queue.push(nodeList[0]);
    string startNodeState = "State: " + startNodeStateRaw;
    string endNodeState = "State: " + endNodeStateRaw;

    std::unordered_set<string> visited;
    std::map<string, string> parents;

    queue.push(getNodeByState(startNodeState));
    visited.insert(startNodeState);

    while (!queue.empty()) {
        Node* currentNode = queue.front();
        queue.pop();

        string currentNodeState = currentNode->toString();

        if (currentNodeState == endNodeState) {
            // Reconstruct the path
            string current = endNodeState;
            while (current != startNodeState) {
                results.insert(results.begin(), current);
                current = parents[current];
            }
            results.insert(results.begin(), startNodeState);
            return results;
        }

        for (const auto& neighbor : currentNode->neighbours) {
            Node* nextNode = neighbor.first;
            string nextNodeState = nextNode->toString();

            if (visited.find(nextNodeState) == visited.end()) {
                visited.insert(nextNodeState);
                parents[nextNodeState] = currentNodeState;
                queue.push(nextNode);
            }
        }
    }
    return results;
}


Graph::Node* Graph::getNodeByState(const string &state) {
    for (const auto& node: nodeList) {
        if (state == node->toString()) {
            return node;
        }
    }
    return nullptr;
}



/*
vector<string> Graph::dijkstraPath(const string &_startNode, const string &_endNode) {
   resetGraph();
   vector<string> results;

   vector<Node*> closed;
   vector<Node*> open = nodeList;
   Node* startNode = getNodeByName(_startNode);
   Node* endNode = getNodeByState(_endNode);
   Node* currentNode = nullptr;

   startNode->cumulativeCost = 0;
   int currentPathValue = 0;

   auto it = std::find(closed.begin(), closed.end(), endNode);
   while (it == closed.end()) {
       int minPathValue = INT_MAX;
       for (const auto& node: open) {
           currentPathValue = node->cumulativeCost;
           if (currentPathValue < minPathValue) {
               currentNode = node;
               minPathValue = currentPathValue;
           }
       }

       open.erase(std::find(open.begin(), open.end(), currentNode));
       closed.push_back(currentNode);

       int combinedPathValue;
       if (currentNode != endNode){
           for (const auto& neighbourPair: currentNode->neighbours) {
               Node* neighbourNode = neighbourPair.first;
               if (std::find(open.begin(), open.end(), neighbourNode) != open.end()) {
                   int edgeWeight = neighbourPair.second;
                   combinedPathValue = currentNode->cumulativeCost + edgeWeight;
                   if (combinedPathValue < neighbourNode->cumulativeCost) {
                       neighbourNode->cumulativeCost = combinedPathValue;
                       neighbourNode->previous = currentNode;
                   }
               }
           }
       }
       it = std::find(closed.begin(), closed.end(), endNode);
   }

   currentNode = endNode;
   while (currentNode != nullptr) {
       results.push_back(currentNode->name);
       currentNode = currentNode->previous;
   }

   std::reverse(results.begin(), results.end());
   return results;
}



vector<string> Graph::depthFirstSearch() {
   vector<string> results;
   std::stack<Node*> stack;
   stack.push(nodeList[0]);

   while (!stack.empty()) {
       Node* currentNode = stack.top();
       stack.pop();

       string currentNodeName = currentNode->name;
       auto it = std::find(results.begin(), results.end(), currentNodeName);
       if (it == results.end()) {
           results.push_back(currentNodeName);
           for (const auto& neighbour: currentNode->neighbours) {
               stack.push(neighbour.first);
           }
       }
   }
   return results;
}*/