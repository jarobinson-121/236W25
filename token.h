# pragma once

# include <string>
# include <sstream>

using namespace std;

enum TokenType {
    COMMA, 
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    WHITESPACE,
    UNDEFINED,
    END
};

class Token {
    private:
        TokenType type;
        string value;
        int line;
    public:
        Token(TokenType type, string value) :
        type(type),
        value(value) {}

        Token(TokenType type, string value, int line) :
        type(type),
        value(value),
        line(line) {}

        string toString() const {
            stringstream out; 
            out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << line << ")";
            return out.str();
        }

    TokenType getType() const {
        return type;
    }

    string getVal() const {
        return value;
    }

    void setLine(int lineUpdate) {
        line = lineUpdate;
    }

    static Token Colon(string value) { 
        return Token(COLON, value); 
    }

    static Token Colon_Dash(string value) {
        return Token(COLON_DASH, value);
    }

    static Token Comma(string value) { 
        return Token(COMMA, value); 
    }

    static Token LeftParen(string value) { 
        return Token(LEFT_PAREN, value); 
    }

    static Token RightParen(string value) { 
        return Token(RIGHT_PAREN, value); 
    }

    static Token Period(string value) {
        return Token(PERIOD, value);
    }

    static Token Q_Mark(string value) {
        return Token(Q_MARK, value);
    }

    static Token Add(string value) {
        return Token(ADD, value);
    }

    static Token Multiply(string value) {
        return Token(MULTIPLY, value);
    }

    static Token Schemes(string value) {
        return Token(SCHEMES, value);
    }

    static Token Facts(string value) {
        return Token(FACTS, value);
    }

    static Token Rules(string value) {
        return Token(RULES, value);
    }

    static Token Queries(string value) {
        return Token(QUERIES, value);
    }

    static Token Id(string value) {
        return Token(ID, value);
    }

    static Token String(string value) {
        return Token(STRING, value);
    }

    static Token Comment(string value) {
        return Token(COMMENT, value);
    }

    static Token Whitespace(string value) { 
        return Token(WHITESPACE, value); 
    }

    static Token Undefined(string value) { 
        return Token(UNDEFINED, value); 
    }

    static Token Eof(string value) { 
        return Token(END, value);
    }

    string typeName(TokenType type) const {
        switch(type) {
            case COMMA: return "COMMA";
            case PERIOD: return "PERIOD";
            case Q_MARK: return "Q_MARK";
            case LEFT_PAREN: return "LEFT_PAREN";
            case RIGHT_PAREN: return "RIGHT_PAREN";
            case COLON: return "COLON";
            case COLON_DASH: return "COLON_DASH";
            case MULTIPLY: return "MULTIPLY";
            case ADD: return "ADD";
            case SCHEMES: return "SCHEMES";
            case FACTS: return "FACTS";
            case RULES: return "RULES";
            case QUERIES: return "QUERIES";
            case ID: return "ID";
            case STRING: return "STRING";
            case COMMENT: return "COMMENT";
            case WHITESPACE: return "WHITESPACE";
            case UNDEFINED: return "UNDEFINED";
            case END: return "END";
        }
    } 
};