//
// Created by Jared Robinson on 3/4/25.
//
#pragma once

#include <string>
#include <vector>
#include "Scheme.h"
#include "Tuple.h"
#include <set>

using namespace std;

class Relation {

private:

    string name;
    Scheme scheme;
    set<Tuple> tuples;

public:

    Relation(const string &name, const Scheme &scheme)
            : name(name), scheme(scheme) {}

    void addTuple(const Tuple &tuple) {
        tuples.insert(tuple);
    }

    set<Tuple> getTuples() const {
        return tuples;
    }

    Relation selectVal(int index, const string& value) const {
        Relation result(name, scheme);
            for (auto& tuple : tuples) {
                if(value == tuple[index]) {
                    result.addTuple(tuple);
                }
            }
        return result;
    }

    Relation select(int index1, int index2) const {
        Relation result(name, scheme);
        for (auto& tuple : tuples) {
            if(tuple[index1] == tuple[index2]) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(vector<int> indexes) {
        vector<string> tempScheme;
        for (auto& index : indexes) {
            tempScheme.push_back(scheme[index]);
        }
        Relation result(name, tempScheme);
        for (auto& tuple : tuples) {
            vector<string> tempTuple;
            for (auto index : indexes) {
                tempTuple.push_back(tuple[index]);
            }
            result.addTuple(Tuple(tempTuple));
        }
        return result;
    }

    Relation rename(vector<string> names) {
        Scheme newScheme(names);
        Relation result(name, newScheme);
        for (auto& tuple : tuples) {
            result.addTuple(tuple);
        }
        return result;
    }

    static bool joinable(const Scheme& leftScheme, const Scheme& rightScheme,
               const Tuple& leftTuple, const Tuple& rightTuple) {

        for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
            const string& leftName = leftScheme.at(leftIndex);
            const string& leftValue = leftTuple.at(leftIndex);


            for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
                const string& rightName = rightScheme.at(rightIndex);
                const string& rightValue = rightTuple.at(rightIndex);


                if  (leftName == rightName) {
                    if (leftValue != rightValue) {
                        return false;
                    }
                    break;
                }
            }
        }
        return true;
    }

    const Scheme& getScheme() const {
        return scheme;
    }

    Relation join(const Relation& right) {
        const Relation& left = *this;

        Scheme newScheme = joinSchemes(left, right);

        set<Tuple> newTuples = joinTuples(left, right, newScheme);

        Relation result(name, newScheme);

        for (auto& tuple : newTuples) {
            result.addTuple(tuple);
        }

        // cout << result.toString();

        return result;
    }

    Scheme joinSchemes(const Relation& left, const Relation& right) {
        const Scheme& leftScheme = left.getScheme();
        Scheme rightScheme = right.getScheme();
        Scheme newScheme = leftScheme;

        for (const auto & i : rightScheme) {
             if (find(leftScheme.begin(), leftScheme.end(), i) == leftScheme.end()) {
                newScheme.push_back(i);
             }
        }

        return newScheme;
    }

    set<Tuple> joinTuples(const Relation& left, const Relation& right, Scheme& updatedScheme) {
        const Scheme& leftScheme = left.getScheme();
        Scheme rightScheme = right.getScheme();
        set<Tuple> newTupleSet;

        for (const auto & leftTuple : left.tuples) {
            for (const auto & rightTuple : right.tuples) {
                if (joinable(leftScheme, rightScheme,  leftTuple, rightTuple)) {
                    Tuple newTuple = leftTuple;
                    for (size_t j = 0; j < rightScheme.size(); j++) {
                        if (find(leftScheme.begin(), leftScheme.end(), rightScheme[j]) == leftScheme.end()) {
                            newTuple.push_back(rightTuple[j]);
                        }
                    }
                    newTupleSet.insert(newTuple);

                    // cout << newTuple.toString(updatedScheme) << endl;
                }
            }
        }
        return newTupleSet;
    }

    bool unionWith(const Relation& relation) {
        bool added = false;

        // cout << relation.toString() << endl;

        for (const Tuple& t : relation.getTuples()) {
            if (tuples.find(t) == tuples.end()) {
                tuples.insert(t);
                added = true;
                cout << "  " << t.toString(scheme) << endl;
            }
        }

        return added;
    }

    string toString() const {
        stringstream out;
        // add code to print the Tuples, one per line
        for (auto& tuple : tuples) {
            out << tuple.toString(scheme) + "\n";
        }
        return out.str();

    };
};