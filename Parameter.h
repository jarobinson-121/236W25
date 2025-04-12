//
// Created by Jared Robinson on 2/17/25.
//

#pragma once

#include <string>

using namespace std;

class Parameter {
private:
    string value;

public:
    Parameter(string value) : value(value) {}

    string toString() const {
        return value;
    }
};
