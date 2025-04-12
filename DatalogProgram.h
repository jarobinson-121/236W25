//
// Created by Jared Robinson on 2/17/25.
//

#pragma once

#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"

using namespace std;

class DatalogProgram {
    // TODO: add helper classes for each of the vectors
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    vector<Parameter> domain;

public:
    DatalogProgram() : schemes(), facts(), rules(), queries(), domain() {}

    const vector<Parameter> &getDomain() const {
        return domain;
    }

    void setDomain(const vector<Parameter> &domain) {
        DatalogProgram::domain = domain;
    }

    const vector<Predicate> &getQueries() const {
        return queries;
    }

    void setQueries(const vector<Predicate> &queries) {
        DatalogProgram::queries = queries;
    }

    const vector<Rule> &getRules() const {
        return rules;
    }

    void setRules(const vector<Rule> &rules) {
        DatalogProgram::rules = rules;
    }

    const vector<Predicate> &getFacts() const {
        return facts;
    }

    void setFacts(const vector<Predicate> &facts) {
        DatalogProgram::facts = facts;
    }

    const vector<Predicate> &getSchemes() const {
        return schemes;
    }

    void setSchemes(const vector<Predicate> &schemes) {
        DatalogProgram::schemes = schemes;
    }

    void addScheme(Predicate scheme) {
        schemes.push_back(scheme);
    }

    void addFact(Predicate fact) {
        facts.push_back(fact);
    }

    void addRule(Rule rule) {
        rules.push_back(rule);
    }

    void addQuery(Predicate query) {
        queries.push_back(query);
    }

    void addDomainItem(Parameter item) {
        domain.push_back(item);
    }

    string toString() {
        string dataProg;

        dataProg = "Success!\nSchemes(" + to_string(schemes.size()) + "):\n";
        for(int i = 0; i < schemes.size(); i++) {
            dataProg += "  " + schemes[i].toString() + "\n";
        }

        dataProg += "Facts(" + to_string(facts.size()) + "):\n";
        for(int i = 0; i < facts.size(); i++) {
            dataProg += "  " + facts[i].toString() + ".\n";
        }

        dataProg += "Rules(" + to_string(rules.size()) + "):\n";
        for(int i = 0; i < rules.size(); i++) {
            dataProg += "  " + rules[i].toString() + ".\n";
        }

        dataProg += "Queries(" + to_string(queries.size()) + "):\n";
        for(int i = 0; i < queries.size(); i++) {
            dataProg += "  " + queries[i].toString() + "?\n";
        }

        dataProg += "Domain(" + to_string(domain.size()) + "):\n";
        for(int i = 0; i < domain.size(); i++) {
            dataProg += "  " + domain[i].toString() + "\n";
        }

        return dataProg;
    }
};
