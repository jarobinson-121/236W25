//
// Created by Jared Robinson on 4/11/25.
//

#pragma once

#include <set>
#include <iostream>
#include <sstream>

using namespace std;

class Node {

private:

    set<int> adjacentNodeIDs;

public:

    void addEdge(int adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }

    set<int> getAdjacentNodeIDs() {
        return adjacentNodeIDs;
    }

    string toString() {
      stringstream ss;
        for (auto it = adjacentNodeIDs.begin(); it != adjacentNodeIDs.end(); ++it) {
            ss << "R" << *it;
            if (next(it) != adjacentNodeIDs.end()) {
                ss << ",";
            }
        }
        return ss.str();
    }

};