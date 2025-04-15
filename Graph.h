//
// Created by Jared Robinson on 4/11/25.
//

#pragma once

#include "Node.h"
#include <map>

using namespace std;

class Graph {

private:

    map<int,Node> nodes;

public:

    Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }

    void addEdge(int fromNodeID, int toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }

    const Node& getNode(int nodeID) const {
        return nodes.at(nodeID);
    }

    const int getSize() const {
        return nodes.size();
    }

    void DFS(int nodeID, vector<bool>& visited, stack<int>& finishOrder) {
        visited[nodeID] = true;
        Node currentNode = nodes[nodeID];
        for (int nextNode : currentNode.getAdjacentNodeIDs()) {
            if (!visited[nextNode]) {
                DFS(nextNode, visited, finishOrder);
            }
        }
        finishOrder.push(nodeID);
    }

    void compDFS(int nodeID, vector<bool>& visited, set<int>& component) {
        visited[nodeID] = true;
        component.insert(nodeID);
        Node currentNode = nodes[nodeID];
        for (int nextNode : currentNode.getAdjacentNodeIDs()) {
            if (!visited[nextNode]) {
                compDFS(nextNode, visited, component);
            }
        }
    }

    bool infiniteProblem(int nodeID) {
        set<int> adjacentNodeIDs = nodes[nodeID].getAdjacentNodeIDs();
        if (find(adjacentNodeIDs.begin(), adjacentNodeIDs.end(), nodeID) != adjacentNodeIDs.end()) {
            return true;
        }
        else {
            return false;
        }
    }

    stack<int> getFinishOrder() {
        vector<bool> visited(nodes.size(), false);
        stack<int> finishOrder;

        for (int nodeID = 0; nodeID < nodes.size(); nodeID++) {
            if (!visited[nodeID]) {
                DFS(nodeID, visited, finishOrder);
            }
        }
        return finishOrder;
    }

    string toString() {
      stringstream ss;

        for (auto& pair: nodes) {
            int nodeID = pair.first;
            Node node = pair.second;
            ss << "R" << nodeID << ":" << node.toString() << endl;
        }
        return ss.str();
    }
};