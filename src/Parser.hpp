/**
 * @file Parser.hpp
 * @brief 语法分析器头文件
 *
 * 该文件基于ACTION和GOTO表实现了两个转移函数。
 * 其中,getParserAction函数处理终结符号输入的状态转移，
 * getNextState函数处理非终结符号输入的状态转移。
 * 此外,addRules函数返回对应规则的字符串表示。
 * 还定义了Parser类,实现了语法分析的整体流程。
 *
 * @note
 * 这里的两个转移函数的switch语句经过优化,合并了许多处理相同的case,
 * 减少了冗余代码,也因此不太好与`compiler/parser.output`对照,
 * 也保留了原始版本,存放在`src/Parser.hpp_origin`中,
 * 以便对照查看,二者实际功能是完全等价的.
 *
 * @author srAm-dev
 * @version 0.1
 * @date 2025-12-11
 * @copyright Copyright (c) 2025 srAm-dev
 * SPDX-License-Identifier: WTFPL
 * Licensed under the WTFPL.
 */
#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Symbol.hpp"
#include "State.hpp"

/**
 * @brief 获取解析器动作
 *
 * 该函数根据当前状态和下一个输入符号(终结符号)返回相应的解析器动作。
 * 动作类型包括SHIFT(移入), REDUCE(规约), ACCEPT(接受)和ERROR(错误)。
 * 对应了语法分析器设计中的ACTION表。
 *
 * @param currentState 当前状态
 * @param nextSymbol 下一个输入符号(终结符号)
 * @return ParserAction 返回对应的解析器动作
 */
ParserAction getParserAction(State currentState, Terminal nextSymbol) {
    switch (currentState) {
    case S0: return {ParserAction::REDUCE, 2};

    case S1:
        if (nextSymbol == eof) return {ParserAction::SHIFT, 3};
        return {ParserAction::ERROR, -1};

    case S2:
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

/**
 * @brief 获取下一个状态
 *
 * 该函数根据当前状态和下一个输入符号(非终结符号)返回相应的下一个状态。
 * 对应了语法分析器设计中的GOTO表。
 *
 * @param currentState 当前状态
 * @param nextSymbol 下一个输入符号(非终结符号)
 * @return State 返回对应的下一个状态
 */
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

/**
 * @brief 返回对应规则的字符串表示
 *
 * 该函数根据规则索引返回对应的产生式规则的字符串表示。
 * 当程序选择进行某条规约时,可以调用此函数获取该规则的文本形式,
 * 以便输出到控制台和命令行中。
 *
 * @param index 规则索引
 * @return std::string 返回对应的产生式规则字符串
 */
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

/**
 * @class Parser
 * @brief 语法分析器类
 *
 * 该类实现了基于LALR分析方法的语法分析器。
 * 它使用状态栈和规约栈来跟踪分析过程,
 * 并通过ACTION和GOTO表进行状态转移。
 */
class Parser {
private:
    int currentSymbol;                    ///< 当前输入符号索引,可在Symbol.hpp中找到对应
    std::ifstream inputFile;              ///< 输入文件流
    std::vector<std::string> reduceStack; ///< 规约栈,存储规约规则的字符串表示
    std::vector<State> stateStack;        ///< 状态栈,存储当前状态序列

    /**
     * @brief 获取下一个符号
     *
     * 该函数从输入文件中读取下一个符号,
     * 并将其转换为对应的符号索引存储在currentSymbol中。
     *
     * @return true 如果成功读取下一个符号
     * @return false 如果到达文件末尾或读取失败
     */
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
    /**
     * @brief 构造函数
     *
     * 初始化语法分析器,打开输入文件,清空规约栈和状态栈,提前获取第一个符号.
     *
     * @param filename 输入文件路径
     */
    Parser(std::string filename) : currentSymbol(0) {
        inputFile.open(filename, std::ios::in);
        reduceStack.clear();
        stateStack.clear();
        stateStack.push_back(S0);
        getNextToken();
    }

    /**
     * @brief 析构函数
     *
     * 关闭输入文件流.
     */
    ~Parser() {
        if (inputFile.is_open()) inputFile.close();
    }

    /**
     * @brief 语法分析主流程
     *
     * 该函数实现了LALR语法分析的主循环,
     * 根据当前状态和输入符号获取解析器动作,
     * 并执行相应的移入、规约或接受操作。
     *
     * @return true 如果成功完成语法分析
     * @return false 如果遇到语法错误
     */
    bool parse() {
        while (true) {
            ParserAction action = getParserAction(stateStack.back(), static_cast<Terminal>(currentSymbol));
            if (action.type == ParserAction::SHIFT) { // 移入操作,推入新状态
                stateStack.push_back(static_cast<State>(action.value));
                getNextToken();
            } else if (action.type == ParserAction::REDUCE) {
                ProductionRule rule = rules[action.value];                       // 从Symbol.hpp中的rules数组获取规则
                for (int i = 0; i < rule.rhsLen; ++i) { stateStack.pop_back(); } // 从状态栈中弹出对应数量的状态
                reduceStack.push_back(addRules(action.value));                   // 记录规约步骤
                State newState = getNextState(stateStack.back(), rule.lhs);      // 获取新状态
                stateStack.push_back(newState);                                  // 将新状态压入状态栈
            } else if (action.type == ParserAction::ACCEPT) {                    // 接受状态
                std::cout << "Parsing completed successfully." << std::endl;
                return true;
            } else { // 错误状态
                std::cout << "Syntax error encountered." << std::endl;
                return false;
            }
        }
    }

    /**
     * @brief 输出规约步骤
     *
     * 该函数将规约栈中的规约步骤输出到控制台和指定的输出文件中。
     *
     * @param outfilename 输出文件路径
     */
    void printReduceStack(std::string outfilename) {
        std::ofstream outfile;
        outfile.open(outfilename, std::ios::out);
        std::cout << "Reduction Steps:" << std::endl;
        for (int i = reduceStack.size() - 1; i >= 0; --i) {
            std::cout << reduceStack[i] << std::endl; // 输出到控制台
            outfile << reduceStack[i] << std::endl;   // 输出到文件
        }
        outfile.close();
    }
};

#endif // PARSER_HPP