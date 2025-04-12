//
// Created by Jared Robinson on 2/17/25.
//

#pragma once

#include <string>
#include <vector>
#include "Parameter.h"
#include "Predicate.h"

using namespace std;

class Rule {
private:
    Predicate headPred;
    vector<Predicate> predicates;

public:
    Rule(Predicate headPred, vector<Predicate> predicates) : headPred(headPred), predicates(predicates) {}

    Predicate getHeadPredicate() const {
        return headPred;
    }

    vector<Predicate> getPredicates() const {
        return predicates;
    }

    string toString() {
        string ruleString = headPred.toString();

        ruleString += " :- ";

        for (int i = 0; i < predicates.size(); i++) {
            ruleString += predicates[i].toString();

            if(i < predicates.size() - 1) {
                ruleString += ",";
            }
        }
        return ruleString;
    }
};