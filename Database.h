//
// Created by Jared Robinson on 3/25/25.
//

#pragma once

#include <map>
#include "Scheme.h"
#include "Relation.h"

using namespace std;

class Database {
    private:
        map<string, Relation> relations;

    public:
        Database() {}

    void addRelation(string name, Relation relation) {
        relations.insert(pair<string, Relation>(name, relation));
    }

    Relation& getRelation(string name) {
        return relations.at(name);
    }
};