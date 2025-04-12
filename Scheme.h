//
// Created by Jared Robinson on 3/4/25.
//

#pragma once

#include <string>
#include <vector>

using namespace std;

class Scheme : public vector<string> {

public:

    Scheme(vector<string> names) : vector<string>(names) { }

};