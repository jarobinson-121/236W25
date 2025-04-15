//
// Created by Jared Robinson on 2/17/25.
//

#pragma once

#include <string>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    string name;
    vector<Parameter> parameters;

public:
    Predicate(string name, vector<Parameter> parameters) : name(name), parameters(parameters) {}

    Predicate(string name) : name(name) {}

    string getName() {
        return name;
    }

    vector<Parameter> getParameters() {
        return parameters;
    }

    string toString() const {
        string predicateString;

        predicateString = name;

        predicateString += "(";

        for (int i = 0; i < parameters.size(); i++) {
            predicateString += parameters[i].toString();

            if(i < parameters.size() - 1) {
                predicateString += ",";
            }
            else {
                predicateString += ")";
            }
        }
        if (parameters.empty()) {
            predicateString += ")";
        }

        return predicateString;
    }
};
