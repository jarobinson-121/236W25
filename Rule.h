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
    Predicate headPredicate;
    vector<Predicate> predicates;

public:
    Rule(Predicate headPred, vector<Predicate> predicates) : headPredicate(headPred), predicates(predicates) {}

    Rule(Predicate headPred) : headPredicate(headPred) {}

    Predicate getHeadPredicate() const {
        return headPredicate;
    }

    vector<Predicate> getPredicates() const {
        return predicates;
    }

    void addBodyPredicate(Predicate predicate) {
        predicates.push_back(predicate);
    }

    string toString() {
        string ruleString = headPredicate.toString();

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