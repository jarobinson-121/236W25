#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "token.h"
#include "scanner.h"
#include "Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"
#include "Interpreter.h"
#include "Predicate.h"
#include "Rule.h"
#include "Node.h"
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    char* filename = argv[1];

    ifstream in;
    in.open(filename);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();

    Scanner s(input);

    vector<Token> tokens = s.scanAllTokens();

    Parser p = Parser(tokens);

    Interpreter interpreter = Interpreter(p.datalogProgram());

    interpreter.run();

    return 0;
}