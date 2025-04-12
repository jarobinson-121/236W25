//
// Created by Jared Robinson on 2/4/25.
//

# pragma once

# include <vector>
# include <string>
# include <iostream>
# include <algorithm>
# include "token.h"
# include "Parameter.h"
# include "Predicate.h"
# include "Rule.h"
# include "DatalogProgram.h"

using namespace std;

class Parser {
private:
    vector<Token> tokens;
    string name;
    vector<Parameter> parameters;
    vector<string> domain;
    Predicate head;
    vector<Predicate> rulePredicates;
    DatalogProgram prog = DatalogProgram();

public:

    Parser(const vector<Token>& tokens) : tokens(tokens), name(""), head(Predicate(name, parameters)) {}

    DatalogProgram datalogProgram() {

        // TODO: for each section of datalog, add something to function to add it to datalog
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        checkForSchemes();

        match(FACTS);
        match(COLON);
        fact();
        factList();
        // TODO: addDomain to datalogProgram call
        addDomainItems();


        match(RULES);
        match(COLON);
        ruleList();

        match(QUERIES);
        match(COLON);
        query();
        queryList();
        checkForQueries();

        match(END);

        return prog;

    }

    TokenType tokenType() {
        return tokens.at(0).getType();
    }

    void advanceToken() {
        tokens.erase(tokens.begin());
    }

    void throwError() {
       throw tokens[0];

    }

    void match(TokenType t) {
    // TODO: add something here to figure out if something is an ID or a domain member
        try {
            if(tokenType() == t) {
                if(name == "" && t == ID) {
                    name = tokens[0].getVal();
                }
                else if(name != "" && (t == STRING || t == ID)) {
                    parameters.push_back(Parameter(tokens[0].getVal()));
                }
                advanceToken();
            }
            else {
                throwError();
            }
        }
        catch(Token badToken) {
            cout << "Failure!" << endl;
            cout << "  " << badToken.toString() << endl;
            exit(0);
        }
    }


    void idList() {
        if(tokenType() == COMMA) {
            match(COMMA);
            match(ID);
            idList();
        }
    }

    void stringList() {
        if(tokenType() == COMMA) {
            match(COMMA);
            match(STRING);
            stringList();
        }
    }

    void scheme() {
        if(tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);

            prog.addScheme(Predicate(name, parameters));
            clear();
        }
    }

    void schemeList() {
        if(tokenType() == ID) {
            scheme();
            schemeList();
        }
    }

    void checkForSchemes() {
        try{
            if(prog.getSchemes().size() == 0) {
                throw tokens[0];
            }
        }
        catch(Token badToken) {
            cout << "Failure!" << endl;
            cout << "  " << badToken.toString() << endl;
            exit(0);
        }
    }

    void fact() {
        if(tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(STRING);
            stringList();
            match(RIGHT_PAREN);
            match(PERIOD);

            // TODO: loop through parameters and check if it is already in the domain, if not, add it to domain
            for(int i = 0; i < parameters.size(); i++) {
                int j = 0;
                bool inDomain = false;
                while(j < domain.size()) {
                    if(parameters[i].toString() == domain[j]) {
                        inDomain = true;
                        break;
                    }
                    else {
                        j++;
                    }
                }
                if(!inDomain) {
                    domain.push_back(parameters[i].toString());
                }
            }

            sort(domain.begin(), domain.end());

            prog.addFact(Predicate(name, parameters));
            clear();
        }
    }

    void factList() {
        if(tokenType() == ID) {
            fact();
            factList();
        }
    }

    void rule() {
        if(tokenType() == ID) {
            headPredicate();
            match(COLON_DASH);
            predicate();
            rulePredicates.push_back(Predicate(name,parameters));
            clear();
            predicateList();
            match(PERIOD);

            prog.addRule(Rule(head, rulePredicates));

            clear();

            head = Predicate("", parameters);
            while(!rulePredicates.empty()) {
                rulePredicates.pop_back();
            }
        }
    }

    void ruleList() {
        if(tokenType() == ID) {
            rule();
            ruleList();
        }
    }

    void query() {
        if(tokenType() == ID) {
            predicate();
            match(Q_MARK);

            prog.addQuery(Predicate(name, parameters));
            clear();
        }
    }

    void queryList() {
        if(tokenType() == ID) {
            query();
            queryList();
        }
    }

    void checkForQueries() {
        try{
            if(prog.getQueries().size() == 0) {
                throw tokens[0];
            }
        }
        catch(Token badToken) {
            cout << "Failure!" << endl;
            cout << "  " << badToken.toString() << endl;
            exit(0);
        }
    }

    void headPredicate() {
        if(tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);

            head = Predicate(name, parameters);
            clear();
        }
    }

    void predicate() {
        if(tokenType() == ID) {
            match(ID);
            match(LEFT_PAREN);
            parameter();
            parameterList();
            match(RIGHT_PAREN);
        }
    }

    void predicateList() {
        if(tokenType() == COMMA) {
            match(COMMA);
            predicate();
            rulePredicates.push_back(Predicate(name,parameters));
            clear();
            predicateList();
        }
    }

    void parameter() {
        if(tokenType() == STRING) {
            match(STRING);
        }
        else if(tokenType() == ID) {
            match(ID);
        }
    }

    void parameterList() {
        if(tokenType() == COMMA) {
            match(COMMA);
            parameter();
            parameterList();
        }
    }

    void addDomainItems() {
        for(int i = 0; i < domain.size(); i++) {
            prog.addDomainItem(Parameter(domain[i]));
        }
    }

    void clear() {
        name = "";
        while(!parameters.empty()) {
            parameters.pop_back();
        }
    }

};