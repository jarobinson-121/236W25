//
// Created by Jared Robinson on 3/4/25.
//

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Scheme.h"

using namespace std;

class Tuple : public vector<string> {

public:

    Tuple(vector<string> values) : vector<string>(values) { }

    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        for(int i = 0; i < scheme.size(); i++) {
            if(i != scheme.size() - 1) {
                out << scheme[i] + "=" + tuple[i] + ", ";
            }
            else {
                out << scheme[i] + "=" + tuple[i];
            }
        }
//        out << scheme.size();
//        out << scheme.at(0);
//        out << tuple.size();
//        out << tuple.at(0);
        return out.str();
    }

};
