#ifndef PARSER_HPP
#define PARSER_HPP

/*
 * Parser.hpp_oringin中存放的代码是严格按照状态转移表生成的，
 * switch语句下的每一个case都严格实现了对应状态的转移逻辑，而
 * 本文件中基于case语句下的重复，优化了switch下的冗余代码，减
 * 少了代码量，实际二者功能一致，但Parser.hpp_oringin能够更
 * 好地和parser.output对应
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Symbol.hpp"
#include "State.hpp"

// 获取动作(下一个输入为终结符号时)
ParserAction getParserAction(State currentState, Terminal nextSymbol) {
    switch (currentState) {
    case S0: return {ParserAction::REDUCE, 2};

    case S1:
        if (nextSymbol == eof) return {ParserAction::SHIFT, 3};
        return {ParserAction::ERROR, -1};

    case S2:
        // State 2: 多种shift
        if (nextSymbol == ARRAY) return {ParserAction::SHIFT, 4};
        if (nextSymbol == ID) return {ParserAction::SHIFT, 5};
        if (nextSymbol == IF) return {ParserAction::SHIFT, 6};
        if (nextSymbol == REPEAT) return {ParserAction::SHIFT, 7};
        if (nextSymbol == READ) return {ParserAction::SHIFT, 8};
        if (nextSymbol == WRITE) return {ParserAction::SHIFT, 9};
        return {ParserAction::ERROR, -1};

    case S3: return {ParserAction::ACCEPT, -1};

    case S4:
        if (nextSymbol == ID) return {ParserAction::SHIFT, 19};
        return {ParserAction::ERROR, -1};

    case S5: return {ParserAction::REDUCE, 32};

    // Group A: Expression Starters
    case S6:
    case S9:
    case S22:
    case S32:
    case S35:
    case S38:
    case S39:
    case S40:
    case S41:
    case S42:
    case S43:
        if (nextSymbol == ID) return {ParserAction::SHIFT, 5};
        if (nextSymbol == NUM) return {ParserAction::SHIFT, 21};
        if (nextSymbol == LPAREN) return {ParserAction::SHIFT, 22};
        return {ParserAction::ERROR, -1};

    // Group B: Statement Starters
    case S7:
    case S31:
    case S37:
    case S62:
        if (nextSymbol == ID) return {ParserAction::SHIFT, 5};
        if (nextSymbol == IF) return {ParserAction::SHIFT, 6};
        if (nextSymbol == REPEAT) return {ParserAction::SHIFT, 7};
        if (nextSymbol == READ) return {ParserAction::SHIFT, 8};
        if (nextSymbol == WRITE) return {ParserAction::SHIFT, 9};
        return {ParserAction::ERROR, -1};

    case S8:
        if (nextSymbol == ID) return {ParserAction::SHIFT, 5};
        return {ParserAction::ERROR, -1};

    case S10: return {ParserAction::REDUCE, 3};

    case S11:
        if (nextSymbol == SEMI) return {ParserAction::SHIFT, 31};
        return {ParserAction::REDUCE, 1};

    case S12: return {ParserAction::REDUCE, 8};
    case S13: return {ParserAction::REDUCE, 9};
    case S14: return {ParserAction::REDUCE, 10};
    case S15: return {ParserAction::REDUCE, 11};
    case S16: return {ParserAction::REDUCE, 12};
    case S17: return {ParserAction::REDUCE, 13};

    case S18:
        if (nextSymbol == ASSIGN) return {ParserAction::SHIFT, 32};
        return {ParserAction::ERROR, -1};

    case S19:
        if (nextSymbol == LBRACKET) return {ParserAction::SHIFT, 33};
        return {ParserAction::ERROR, -1};

    case S20:
        if (nextSymbol == LBRACKET) return {ParserAction::SHIFT, 35};
        return {ParserAction::REDUCE, 31};

    case S21: return {ParserAction::REDUCE, 29};

    case S23:
        if (nextSymbol == THEN) return {ParserAction::SHIFT, 37};
        return {ParserAction::ERROR, -1};

    case S24:
        if (nextSymbol == RELOP) return {ParserAction::SHIFT, 38};
        if (nextSymbol == PLUS) return {ParserAction::SHIFT, 39};
        if (nextSymbol == MINUS) return {ParserAction::SHIFT, 40};
        return {ParserAction::REDUCE, 21};

    case S25:
        if (nextSymbol == TIMES) return {ParserAction::SHIFT, 41};
        if (nextSymbol == OVER) return {ParserAction::SHIFT, 42};
        return {ParserAction::REDUCE, 24};

    case S26: return {ParserAction::REDUCE, 27};
    case S27: return {ParserAction::REDUCE, 30};

    case S28:
        if (nextSymbol == SEMI) return {ParserAction::SHIFT, 31};
        if (nextSymbol == UNTIL) return {ParserAction::SHIFT, 43};
        return {ParserAction::ERROR, -1};

    case S29: return {ParserAction::REDUCE, 18};
    case S30: return {ParserAction::REDUCE, 19};

    case S33:
        if (nextSymbol == NUM) return {ParserAction::SHIFT, 46};
        return {ParserAction::ERROR, -1};

    case S34:
        if (nextSymbol == SEMI) return {ParserAction::SHIFT, 47};
        if (nextSymbol == LBRACKET) return {ParserAction::SHIFT, 48};
        return {ParserAction::ERROR, -1};

    case S36:
        if (nextSymbol == RPAREN) return {ParserAction::SHIFT, 50};
        return {ParserAction::ERROR, -1};

    case S44: return {ParserAction::REDUCE, 7};
    case S45: return {ParserAction::REDUCE, 17};

    case S46:
        if (nextSymbol == RBRACKET) return {ParserAction::SHIFT, 58};
        return {ParserAction::ERROR, -1};

    case S47: return {ParserAction::REDUCE, 4};

    case S48:
        if (nextSymbol == NUM) return {ParserAction::SHIFT, 59};
        return {ParserAction::ERROR, -1};

    case S49:
        if (nextSymbol == RBRACKET) return {ParserAction::SHIFT, 60};
        return {ParserAction::ERROR, -1};

    case S50: return {ParserAction::REDUCE, 28};

    case S51:
        if (nextSymbol == SEMI) return {ParserAction::SHIFT, 31};
        if (nextSymbol == END) return {ParserAction::SHIFT, 61};
        if (nextSymbol == ELSE) return {ParserAction::SHIFT, 62};
        return {ParserAction::ERROR, -1};

    case S52:
        if (nextSymbol == PLUS) return {ParserAction::SHIFT, 39};
        if (nextSymbol == MINUS) return {ParserAction::SHIFT, 40};
        return {ParserAction::REDUCE, 20};

    case S53:
        if (nextSymbol == TIMES) return {ParserAction::SHIFT, 41};
        if (nextSymbol == OVER) return {ParserAction::SHIFT, 42};
        return {ParserAction::REDUCE, 22};

    case S54:
        if (nextSymbol == TIMES) return {ParserAction::SHIFT, 41};
        if (nextSymbol == OVER) return {ParserAction::SHIFT, 42};
        return {ParserAction::REDUCE, 23};

    case S55: return {ParserAction::REDUCE, 25};
    case S56: return {ParserAction::REDUCE, 26};
    case S57: return {ParserAction::REDUCE, 16};
    case S58: return {ParserAction::REDUCE, 6};

    case S59:
        if (nextSymbol == RBRACKET) return {ParserAction::SHIFT, 63};
        return {ParserAction::ERROR, -1};

    case S60: return {ParserAction::REDUCE, 33};
    case S61: return {ParserAction::REDUCE, 14};
    case S63: return {ParserAction::REDUCE, 5};

    case S64:
        if (nextSymbol == SEMI) return {ParserAction::SHIFT, 31};
        if (nextSymbol == END) return {ParserAction::SHIFT, 65};
        return {ParserAction::ERROR, -1};

    case S65: return {ParserAction::REDUCE, 15};
    }
    return {ParserAction::ERROR, -1};
}

// 获取跳转(下一个输入为非终结符号时)
State getNextState(State currentState, NonTerminal nextSymbol) {
    switch (currentState) {
    case S0:
        if (nextSymbol == PROGRAM) return S1;
        if (nextSymbol == ARRAY_DECLS) return S2;
        return S_error;

    // Group: Statement Starters
    case S2:
    case S7:
    case S31:
    case S37:
    case S62:
        if (nextSymbol == STMT_SEQUENCE) {
            if (currentState == S2) return S11;
            if (currentState == S7) return S28;
            if (currentState == S37) return S51;
            if (currentState == S62) return S64;
        }
        if (currentState == S2 && nextSymbol == ARRAY_DECL) return S10;

        if (nextSymbol == STATEMENT) return (currentState == S31) ? S44 : S12;

        if (nextSymbol == IF_STMT) return S13;
        if (nextSymbol == REPEAT_STMT) return S14;
        if (nextSymbol == ASSIGN_STMT) return S15;
        if (nextSymbol == READ_STMT) return S16;
        if (nextSymbol == WRITE_STMT) return S17;
        if (nextSymbol == VAR) return S18;
        return S_error;

    case S5:
        if (nextSymbol == VAR_DIMS) return S20;
        return S_error;

    // Group: Expression Starters
    case S6:
    case S9:
    case S22:
    case S32:
    case S35:
    case S43:
        if (nextSymbol == EXP) {
            if (currentState == S6) return S23;
            if (currentState == S9) return S30;
            if (currentState == S22) return S36;
            if (currentState == S32) return S45;
            if (currentState == S35) return S49;
            if (currentState == S43) return S57;
        }
        if (nextSymbol == SIMPLE_EXP) return S24;
        if (nextSymbol == TERM) return S25;
        if (nextSymbol == FACTOR) return S26;
        if (nextSymbol == VAR) return S27;
        return S_error;

    case S8:
        if (nextSymbol == VAR) return S29;
        return S_error;

    case S19:
        if (nextSymbol == DIMS) return S34;
        return S_error;

    case S38:
        if (nextSymbol == SIMPLE_EXP) return S52;
        if (nextSymbol == TERM) return S25;
        if (nextSymbol == FACTOR) return S26;
        if (nextSymbol == VAR) return S27;
        return S_error;

    case S39:
    case S40:
        if (nextSymbol == TERM) return (currentState == S39) ? S53 : S54;
        if (nextSymbol == FACTOR) return S26;
        if (nextSymbol == VAR) return S27;
        return S_error;

    case S41:
    case S42:
        if (nextSymbol == FACTOR) return (currentState == S41) ? S55 : S56;
        if (nextSymbol == VAR) return S27;
        return S_error;

    default: return S_error;
    }
}

// 返回规则的内容
std::string addRules(int index) {
    if (index == 0) return "program' -> program";
    else if (index == 1) return "program -> array_decls stmt_sequence";
    else if (index == 2) return "array_decls -> epsilon";
    else if (index == 3) return "array_decls -> array_decls array_decl";
    else if (index == 4) return "array_decl -> ARRAY ID dims SEMI";
    else if (index == 5) return "dims -> dims LBRACKET NUM RBRACKET";
    else if (index == 6) return "dims -> LBRACKET NUM RBRACKET";
    else if (index == 7) return "stmt_sequence -> stmt_sequence SEMI statement";
    else if (index == 8) return "stmt_sequence -> statement";
    else if (index == 9) return "statement -> if_stmt";
    else if (index == 10) return "statement -> repeat_stmt";
    else if (index == 11) return "statement -> assign_stmt";
    else if (index == 12) return "statement -> read_stmt";
    else if (index == 13) return "statement -> write_stmt";
    else if (index == 14) return "if_stmt -> IF exp THEN stmt_sequence END";
    else if (index == 15) return "if_stmt -> IF exp THEN stmt_sequence ELSE stmt_sequence END";
    else if (index == 16) return "repeat_stmt -> REPEAT stmt_sequence UNTIL exp";
    else if (index == 17) return "assign_stmt -> var ASSIGN exp";
    else if (index == 18) return "read_stmt -> READ var";
    else if (index == 19) return "write_stmt -> WRITE exp";
    else if (index == 20) return "exp -> simple_exp RELOP simple_exp";
    else if (index == 21) return "exp -> simple_exp";
    else if (index == 22) return "simple_exp -> simple_exp PLUS term";
    else if (index == 23) return "simple_exp -> simple_exp MINUS term";
    else if (index == 24) return "simple_exp -> term";
    else if (index == 25) return "term -> term TIMES factor";
    else if (index == 26) return "term -> term OVER factor";
    else if (index == 27) return "term -> factor";
    else if (index == 28) return "factor -> LPAREN exp RPAREN";
    else if (index == 29) return "factor -> NUM";
    else if (index == 30) return "factor -> var";
    else if (index == 31) return "var -> ID var_dims";
    else if (index == 32) return "var_dims -> epsilon";
    else if (index == 33) return "var_dims -> var_dims LBRACKET exp RBRACKET";
    return "";
}

// 语法分析器类
class Parser {
private:
    int currentSymbol;
    std::ifstream inputFile;
    std::vector<std::string> reduceStack;
    std::vector<State> stateStack;

    bool getNextToken() {
        std::string lexeme;
        std::string token;
        if (inputFile.peek() == EOF) { return false; }
        if (inputFile >> token >> lexeme) {
            currentSymbol = symbolToIndex(token);
            return true;
        } else {
            currentSymbol = eof;
            return false;
        }
    }

public:
    Parser(std::string filename) : currentSymbol(0) {
        inputFile.open(filename, std::ios::in);
        reduceStack.clear();
        stateStack.clear();
        stateStack.push_back(S0);
        getNextToken();
    }
    ~Parser() {
        if (inputFile.is_open()) inputFile.close();
    }

    bool parse() {
        while (true) {
            ParserAction action = getParserAction(stateStack.back(), static_cast<Terminal>(currentSymbol));
            if (action.type == ParserAction::SHIFT) {
                stateStack.push_back(static_cast<State>(action.value));
                getNextToken();
            } else if (action.type == ParserAction::REDUCE) {
                ProductionRule rule = rules[action.value];
                for (int i = 0; i < rule.rhsLen; ++i) { stateStack.pop_back(); }
                reduceStack.push_back(addRules(action.value));
                State newState = getNextState(stateStack.back(), rule.lhs);
                stateStack.push_back(newState);
            } else if (action.type == ParserAction::ACCEPT) {
                std::cout << "Parsing completed successfully." << std::endl;
                return true;
            } else {
                std::cout << "Syntax error encountered." << std::endl;
                return false;
            }
        }
    }

    void printReduceStack(std::string outfilename) {
        std::ofstream outfile;
        outfile.open(outfilename, std::ios::out);
        std::cout << "Reduction Steps:" << std::endl;
        for (int i = reduceStack.size() - 1; i >= 0; --i) {
            std::cout << reduceStack[i] << std::endl;
            outfile << reduceStack[i] << std::endl;
        }
        outfile.close();
    }
};

#endif // PARSER_HPP