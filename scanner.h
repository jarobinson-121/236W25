# pragma once
# include <string>
# include <cctype>
# include <vector>
# include <memory>
# include "token.h"
# include "fsm.h"

using namespace std;

class Scanner {
    private:
        Colon colonFSM;
        Colon_Dash colonDashFSM;
        Comma commaFSM;
        Period periodFSM;
        LeftParen leftParenFSM;
        RightParen rightParenFSM;
        Multiply multiplyFSM;
        Add addFSM;
        Q_Mark qMarkFSM;
        Schemes schemesFSM;
        Facts factsFSM;
        Rules rulesFSM;
        Queries queriesFSM;
        IDFSM idFSM;
        String stringFSM;
        Comment commentFSM;
        WhiteSpace whtSpcFSM;
        Undefined undefinedFSM;
        Eof eofFSM;
        string input;
        int line;

    public:
        vector<Token> allTokens;

        Scanner(string const input) : input(input), line(1) {};

        
        vector<Token> scanAllTokens() {
            while (!input.empty()) {
                Token bestFit = Token::Undefined(string(1, input[0]));
                int maxCharsRead = 0;
                int newLines = 0;

                pair<int, Token> currToken = make_pair(0, Token::Undefined(""));

                while (!input.empty() && (input[0] == ' ' || input[0] == '\t')) {
                    input = input.substr(1);
                }

                vector<pair<int, Token> > possibleTokens;

                possibleTokens.push_back(colonFSM.match(input));
                possibleTokens.push_back(colonDashFSM.match(input));
                possibleTokens.push_back(commaFSM.match(input));
                possibleTokens.push_back(periodFSM.match(input));
                possibleTokens.push_back(leftParenFSM.match(input));
                possibleTokens.push_back(rightParenFSM.match(input));
                possibleTokens.push_back(multiplyFSM.match(input));
                possibleTokens.push_back(addFSM.match(input));
                possibleTokens.push_back(qMarkFSM.match(input));
                possibleTokens.push_back(schemesFSM.match(input));
                possibleTokens.push_back(factsFSM.match(input));
                possibleTokens.push_back(rulesFSM.match(input));
                possibleTokens.push_back(queriesFSM.match(input));
                possibleTokens.push_back(idFSM.match(input));
                possibleTokens.push_back(stringFSM.match(input, newLines));
                possibleTokens.push_back(commentFSM.match(input));
                possibleTokens.push_back(whtSpcFSM.match(input));
                possibleTokens.push_back(eofFSM.match(input));
                possibleTokens.push_back(undefinedFSM.match(input));

                bool isNotUndef = false;
                bool matchKeyword = false;

                for (const auto& tokenPair : possibleTokens) {
                    int numChars = tokenPair.first;
                    Token currToken = tokenPair.second;

                    if (numChars > maxCharsRead) {
                        maxCharsRead = numChars;
                        bestFit = currToken;
                        isNotUndef = (currToken.getType() != UNDEFINED);
                        matchKeyword = (currToken.getType() == SCHEMES || currToken.getType() == FACTS ||
                                        currToken.getType() == RULES || currToken.getType() == QUERIES);
                    } else if (numChars == maxCharsRead) {
                        if(currToken.getType() != UNDEFINED) {
                            bestFit = currToken;
                            isNotUndef = true;
                        }
                    }
                }

                if (!isNotUndef) {
                    for (const auto& tokenPair : possibleTokens) {
                        if (tokenPair.first == maxCharsRead && tokenPair.second.getType() != UNDEFINED) {
                            bestFit = tokenPair.second;
                            break;
                        }
                    }
                }

                if (matchKeyword && bestFit.getType() == ID) {
                    for (const auto& tokenPair : possibleTokens) {
                        if (tokenPair.first == maxCharsRead && (tokenPair.second.getType() == SCHEMES || tokenPair.second.getType() == FACTS || tokenPair.second.getType() == RULES || tokenPair.second.getType() == QUERIES)) {
                            bestFit = tokenPair.second;
                            break;
                        }
                    }
                }

                bestFit.setLine(line);
                if(bestFit.getType() == UNDEFINED) {
                    line += newLines;
                }

                if(bestFit.getType() == WHITESPACE) {
                    ++line;
                }


                input = input.substr(maxCharsRead);

                if(bestFit.getType() != WHITESPACE && bestFit.getType() != COMMENT) {
                    allTokens.push_back(bestFit);
                }
            }

            Token End = Token::Eof("");
            End.setLine(line);
            allTokens.push_back(End);

            return allTokens;
        }
  
};