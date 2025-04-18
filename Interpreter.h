//
// Created by Jared Robinson on 3/25/25.
//

#pragma once

#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Graph.h"
#include <iostream>


using namespace std;

class Interpreter {
    private:
        DatalogProgram program;
        Database database;

    public:
        Interpreter(DatalogProgram program) : program(program) {}

        void print() { cout << program.toString() << endl; }

    void schemes() {
        for (auto scheme : program.getSchemes()) {
            vector<Parameter> parameters = scheme.getParameters();
            vector<string> relation;
            string name = scheme.getName();
            for (auto parameter : parameters) {
                relation.push_back(parameter.toString());
            }

            Scheme relScheme(relation);

            // cout << name << endl;

            database.addRelation(name, Relation(name, relScheme));
        }
     }

    void facts() {
         for (auto fact : program.getFacts()) {
             // cout << fact.getName() << endl;
             Relation &relation = database.getRelation(fact.getName());
             vector<string> tupleStrings;
             for (auto parameter : fact.getParameters()) {
                 // cout << parameter.toString() << endl;
                 tupleStrings.push_back(parameter.toString());
             }
             // database.getRelation(fact.getName()).addTuple(Tuple(tupleStrings));
             relation.addTuple(Tuple(tupleStrings));
         }
     }

    void queries() {
            cout << "Query Evaluation" << endl;

            for (const Predicate& query : program.getQueries()) {
                cout << query.toString() << "? ";

                Relation relation = evalPredicate(query);

                if (relation.getTuples().empty()) {
                    cout << "No" << endl;
                } else {
                    cout << "Yes(" << relation.getTuples().size() << ")" << endl;
                    if (!relation.getScheme().empty()) {
                        for (const Tuple& tuple : relation.getTuples()) {
                            cout << "  " << tuple.toString(relation.getScheme()) << endl;
                        }
                    }
                }
            }
        }

    void rules() {

        cout << "Dependency Graph" << endl;

        pair<Graph, Graph> graphs = makeGraph(program.getRules());
        Graph graph = graphs.first;
        Graph reverseGraph = graphs.second;

        cout << graph.toString() << endl;

        stack<int> finishOrder = reverseGraph.getFinishOrder();

        vector<bool> visited(graph.getSize(), false);

            vector<set<int>> sccs;

            while (!finishOrder.empty()) {
                int node = finishOrder.top();
                finishOrder.pop();

                if (!visited[node]) {
                    set<int> component;
                    graph.compDFS(node, visited, component);
                    sccs.push_back(component);
                }
            }

        // reverse(sccs.begin(), sccs.end());

        cout << "Rule Evaluation" << endl;
            // cout << sccs.size() << endl;

        for (auto scc : sccs) {
            bool addedTuples = false;
            int passes = 0;
            cout << "SCC: ";
            bool first = true;
            for (auto id : scc) {
                if (!first) {
                    cout << ",";
                }
                cout << "R" << id;
                first = false;
            }
            cout << endl;

            do {
                addedTuples = false;
                passes++;

                vector<Rule> rules = program.getRules();

                for (auto id : scc) {
                    Rule rule = rules[id];

                    cout << rule.toString() << "." << endl;

                    vector<Relation> bodyRelations;
                    vector<Predicate> bodyPredicates = rule.getPredicates();
                    for (unsigned j = 0; j < bodyPredicates.size(); j++) {
                        Relation r = evalPredicate(bodyPredicates[j]);
                        // cout << r.toString();
                        bodyRelations.push_back(r);
                    }

                    Relation joinedRelation = bodyRelations[0];
                    // cout << joinedRelation.toString() << endl;
                    for (unsigned j = 1; j < bodyRelations.size(); j++) {
                        joinedRelation = joinedRelation.join(bodyRelations[j]);
                        // cout << joinedRelation.toString();
                    }

                    Predicate head = rule.getHeadPredicate();

                    vector<int> indexes;
                    Scheme joinedScheme = joinedRelation.getScheme();
                    vector<Parameter> headParams = head.getParameters();
                    for (unsigned j = 0; j < headParams.size(); j++) {
                        string name = headParams[j].toString();
                        for (unsigned k = 0; k < joinedScheme.size(); k++) {
                            if (joinedScheme[k] == name) {
                                indexes.push_back(k);
                                break;
                            }
                        }
                    }

                    Relation projected = joinedRelation.project(indexes);
                    vector<string> newNames;
                    for (unsigned j = 0; j < headParams.size(); j++) {
                        newNames.push_back(headParams[j].toString());
                    }
                    projected = projected.rename(newNames);

                    string headName = head.getName();
                    Relation& target = database.getRelation(headName);

                    bool added = target.unionWith(projected);

                    if (added) {
                        addedTuples = true;
                    }
                }
            } while (addedTuples && (scc.size() > 1 || graph.infiniteProblem(*scc.begin())));
            cout << passes << " passes: ";
            first = true;
            for (auto id : scc) {
                if (!first) {
                    cout << ",";
                }
                cout << "R" << id;
                first = false;
            }
            cout << endl;
        }
    cout << endl;
}


    Relation evalPredicate(Predicate predicate) {
        Relation relation = database.getRelation(predicate.getName());

        vector<Parameter> parameters = predicate.getParameters();
        vector<int> projectIndexes;
        vector<string> reNames;
        map<string, int> seenVariables;

        for (int i = 0; i < parameters.size(); i++) {
            string val = parameters[i].toString();

            if (val[0] == '\'') {
                relation = relation.selectVal(i, val);
            }
            else {
                if (seenVariables.count(val)) {
                    relation = relation.select(i, seenVariables[val]);
                }
                else {
                    seenVariables[val] = i;
                    projectIndexes.push_back(i);
                    reNames.push_back(val);
                }
            }
        }

        relation = relation.project(projectIndexes);
        relation = relation.rename(reNames);

        return relation;
    }

    static pair<Graph, Graph> makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size());
        Graph reverseGraph(rules.size());
        int fromIndex = 0;
        int toIndex = 0;

        for (auto r : rules) {
            // cout << "from rule R" << fromIndex << ": " << rule.toString() << endl;
            for (auto predicate : r.getPredicates()) {
                // cout << "from body predicate: " << predicate.toString() << endl;
                toIndex = 0;
                for (auto other : rules) {
                    // cout << "to rule R" << toIndex << ": " << rule.toString() << endl;
                    if (predicate.getName() == other.getHeadPredicate().getName()) {

                        // cout << "graph: " <<fromIndex << ", " << toIndex << endl;
                        graph.addEdge(fromIndex, toIndex);

                        // cout << "graph: " <<fromIndex << ", " << toIndex <<  endl;
                        reverseGraph.addEdge(toIndex, fromIndex);
                        // cout << "dependency found: " << "(R" << fromIndex << ",R" << toIndex << ")" << endl;
                    }
                    toIndex++;
                }
            }
            fromIndex++;
        }
        return pair<Graph, Graph>(graph, reverseGraph);
    }

    void run() {
        schemes();
        facts();
        rules();
        queries();
     }
};
