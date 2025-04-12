#pragma once

#include "token.h"
#include <utility>
#include <cctype>
#include <string>

using namespace std;

class Colon {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == ':') {
            return make_pair(1, Token::Colon(":"));
        }
        else{
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Colon_Dash {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == ':' && input[1] == '-') {
            return make_pair(2, Token::Colon_Dash(":-"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Comma {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == ',') {
            return make_pair(1, Token::Comma(","));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class LeftParen {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == '(') {
            return make_pair(1, Token::LeftParen("("));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class RightParen {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == ')') {
            return make_pair(1, Token::RightParen(")"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Period {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == '.') {
            return make_pair(1, Token::Period("."));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};


class Q_Mark {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == '?') {
            return make_pair(1, Token::Q_Mark("?"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Add {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == '+') {
            return make_pair(1, Token::Add("+"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Multiply {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == '*') {
            return make_pair(1, Token::Multiply("*"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class WhiteSpace {
public:
    pair<int, Token> match(const string& input)  {
        if(input[0] == '\n') {
            return make_pair(1, Token::Whitespace("\n"));
        }
        return make_pair(0, Token::Undefined(input));
    }
};

class Eof {
public:
    pair<int, Token> match(const string& input)  {
        if(input.empty()) {
            return make_pair(0, Token::Eof(""));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Schemes {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == 'S' && input[1] == 'c' && input[2] == 'h' && input[3] == 'e' && input[4] == 'm' && input[5] == 'e' && input[6] == 's') {
            return make_pair(7, Token::Schemes("Schemes"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Facts  {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == 'F' && input[1] == 'a' && input[2] == 'c' && input[3] == 't' && input[4] == 's') {
            return make_pair(5, Token::Facts("Facts"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Rules {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == 'R' && input[1] == 'u' && input[2] == 'l' && input[3] == 'e' && input[4] == 's') {
            return make_pair(5, Token::Rules("Rules"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class Queries {
public:
    pair<int, Token> match(const string& input)  {
        if(!input.empty() && input[0] == 'Q' && input[1] == 'u' && input[2] == 'e' && input[3] == 'r' && input[4] == 'i' && input[5] == 'e' && input[6] == 's') {
            return make_pair(7, Token::Queries("Queries"));
        }
        else {
            return make_pair(0, Token::Undefined(input));
        }
    }
};

class String {
public:
    pair<int, Token> match(const string& input, int &newLines)  {
        newLines = 0;
        if (!input.empty() && input[0] == '\'') {
            int count = 1;
            while (count < input.size() && input[count] != '\'') {
                count++;
                if(input[count] == '\n') {
                    newLines++;
                }
            }
            if(count < input.size()) {
                return make_pair(count + 1, Token::String(input.substr(0, count + 1)));
            }
            else {
                return make_pair(count, Token::Undefined(input.substr(0,count)));
            }
        }
        return make_pair(0, Token::Undefined(input));
    }
};

class Comment {
public:
    pair<int, Token> match(const string& input)  {
        if (!input.empty() && input[0] == '#') {
            int count = 1;
            while (count < input.size() && input[count] != '\n') {
                count++;
            }
            return make_pair(count, Token::Comment(input.substr(0, count)));
        }
        return make_pair(0, Token::Undefined(input));
    }
};

class IDFSM {
public:
    pair<int, Token> match(const string& input)  {
        if (!input.empty() && isalpha(input[0])) {
            int count = 1;
            while (count < input.size() && isalnum(input[count])) {
                count++;
            }
            return make_pair(count, Token::Id(input.substr(0, count)));
        }
        return make_pair(0, Token::Undefined(input));
    }
};

class Undefined {
public:
    pair<int, Token> match(const string& input)  {
        if (!input.empty()) {
            if (isspace(input[0])) {
                return make_pair(0, Token::Undefined(""));
            }
            if(isdigit(input[0])) {
                return make_pair(1, Token::Undefined(string(1, input[0])));
            }
            int count = 1;
            if(input[0] == '\'') {
                while (count < input.size() && input[count] != '\'') {
                    if(input[count] == '\n') {
                        return make_pair(1, Token::Whitespace("\n"));
                    } else if (count + 1 >= input.size()) {
                        return make_pair(count, Token::Undefined((input.substr(0,count))));
                    } else {
                        count++;
                    }
                }
            }
//            int count = 1;
//            while (count < input.size() && isalnum(input[count])) {
//                count++;
//            }
//            return make_pair(count, Token::Id(input.substr(0, count)));
            return make_pair(1, Token::Undefined(string(1, input[0])));

        }
        return make_pair(0, Token::Undefined(input));
    }
};