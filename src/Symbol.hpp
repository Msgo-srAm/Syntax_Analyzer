#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>

// 终结符，同实验一中的 Token类型（去除了注释和空白字符）
enum Terminal {
    eof = 0,
    ARRAY = 258,
    ID = 259,
    SEMI = 260,
    LBRACKET = 261,
    NUM = 262,
    RBRACKET = 263,
    IF = 264,
    THEN = 265,
    END = 266,
    ELSE = 267,
    REPEAT = 268,
    UNTIL = 269,
    ASSIGN = 270,
    READ = 271,
    WRITE = 272,
    RELOP = 273,
    PLUS = 274,
    MINUS = 275,
    TIMES = 276,
    OVER = 277,
    LPAREN = 278,
    RPAREN = 279
};

// 非终结符
enum NonTerminal {
    PROGRAM = 26,
    ARRAY_DECLS = 27,
    ARRAY_DECL = 28,
    DIMS = 29,
    STMT_SEQUENCE = 30,
    STATEMENT = 31,
    IF_STMT = 32,
    REPEAT_STMT = 33,
    ASSIGN_STMT = 34,
    READ_STMT = 35,
    WRITE_STMT = 36,
    EXP = 37,
    SIMPLE_EXP = 38,
    TERM = 39,
    FACTOR = 40,
    VAR = 41,
    VAR_DIMS = 42
};

// 符号匹配
bool isTerminal(std::string inputSymbol) {
    return inputSymbol == "eof" || inputSymbol == "ARRAY" || inputSymbol == "ID" || inputSymbol == "SEMI"
           || inputSymbol == "LBRACKET" || inputSymbol == "NUM" || inputSymbol == "RBRACKET" || inputSymbol == "IF"
           || inputSymbol == "THEN" || inputSymbol == "END" || inputSymbol == "ELSE" || inputSymbol == "REPEAT"
           || inputSymbol == "UNTIL" || inputSymbol == "ASSIGN" || inputSymbol == "READ" || inputSymbol == "WRITE"
           || inputSymbol == "RELOP" || inputSymbol == "PLUS" || inputSymbol == "MINUS" || inputSymbol == "TIMES"
           || inputSymbol == "OVER" || inputSymbol == "LPAREN" || inputSymbol == "RPAREN";
}
Terminal whichTerminal(std::string inputSymbol) {
    if (inputSymbol == "eof") return eof;
    else if (inputSymbol == "ARRAY") return ARRAY;
    else if (inputSymbol == "ID") return ID;
    else if (inputSymbol == "SEMI") return SEMI;
    else if (inputSymbol == "LBRACKET") return LBRACKET;
    else if (inputSymbol == "NUM") return NUM;
    else if (inputSymbol == "RBRACKET") return RBRACKET;
    else if (inputSymbol == "IF") return IF;
    else if (inputSymbol == "THEN") return THEN;
    else if (inputSymbol == "END") return END;
    else if (inputSymbol == "ELSE") return ELSE;
    else if (inputSymbol == "REPEAT") return REPEAT;
    else if (inputSymbol == "UNTIL") return UNTIL;
    else if (inputSymbol == "ASSIGN") return ASSIGN;
    else if (inputSymbol == "READ") return READ;
    else if (inputSymbol == "WRITE") return WRITE;
    else if (inputSymbol == "RELOP") return RELOP;
    else if (inputSymbol == "PLUS") return PLUS;
    else if (inputSymbol == "MINUS") return MINUS;
    else if (inputSymbol == "TIMES") return TIMES;
    else if (inputSymbol == "OVER") return OVER;
    else if (inputSymbol == "LPAREN") return LPAREN;
    else if (inputSymbol == "RPAREN") return RPAREN;
    // 默认返回ID，实际使用中应确保输入合法
    return ID;
}
bool isNonTerminal(std::string inputSymbol) {
    return inputSymbol == "PROGRAM" || inputSymbol == "ARRAY_DECLS" || inputSymbol == "ARRAY_DECL"
           || inputSymbol == "DIMS" || inputSymbol == "STMT_SEQUENCE" || inputSymbol == "STATEMENT"
           || inputSymbol == "IF_STMT" || inputSymbol == "REPEAT_STMT" || inputSymbol == "ASSIGN_STMT"
           || inputSymbol == "READ_STMT" || inputSymbol == "WRITE_STMT" || inputSymbol == "EXP"
           || inputSymbol == "SIMPLE_EXP" || inputSymbol == "TERM" || inputSymbol == "FACTOR" || inputSymbol == "VAR"
           || inputSymbol == "VAR_DIMS";
}
NonTerminal whichNonTerminal(std::string inputSymbol) {
    if (inputSymbol == "PROGRAM") return PROGRAM;
    else if (inputSymbol == "ARRAY_DECLS") return ARRAY_DECLS;
    else if (inputSymbol == "ARRAY_DECL") return ARRAY_DECL;
    else if (inputSymbol == "DIMS") return DIMS;
    else if (inputSymbol == "STMT_SEQUENCE") return STMT_SEQUENCE;
    else if (inputSymbol == "STATEMENT") return STATEMENT;
    else if (inputSymbol == "IF_STMT") return IF_STMT;
    else if (inputSymbol == "REPEAT_STMT") return REPEAT_STMT;
    else if (inputSymbol == "ASSIGN_STMT") return ASSIGN_STMT;
    else if (inputSymbol == "READ_STMT") return READ_STMT;
    else if (inputSymbol == "WRITE_STMT") return WRITE_STMT;
    else if (inputSymbol == "EXP") return EXP;
    else if (inputSymbol == "SIMPLE_EXP") return SIMPLE_EXP;
    else if (inputSymbol == "TERM") return TERM;
    else if (inputSymbol == "FACTOR") return FACTOR;
    else if (inputSymbol == "VAR") return VAR;
    else if (inputSymbol == "VAR_DIMS") return VAR_DIMS;
    // 默认返回PROGRAM，实际使用中应确保输入合法
    return PROGRAM;
}
int symbolToIndex(std::string inputSymbol) {
    if (isTerminal(inputSymbol)) {
        return whichTerminal(inputSymbol); // 终结符索引从0开始
    } else if (isNonTerminal(inputSymbol)) {
        return whichNonTerminal(inputSymbol); // 非终结符索引接在终结符后面
    }
    return -1; // 非法符号
}
// 动作结构体
struct ParserAction {
    enum Type { SHIFT, REDUCE, ACCEPT, ERROR } type;
    int value; // SHIFT: 目标状态; REDUCE: 规则编号; ACCEPT/ERROR: 无意义(-1)
};

// 规则结构体 (用于 Reduce)
struct ProductionRule {
    NonTerminal lhs; // 左部非终结符
    int rhsLen;      // 右部长度 (要弹出的数量)
};

// 规则表
const ProductionRule rules[34] = {
    {PROGRAM, 1},       // Rule 0:  $accept (占位)
    {PROGRAM, 2},       // Rule 1:  program: array_decls stmt_sequence
    {ARRAY_DECLS, 0},   // Rule 2:  array_decls: ε
    {ARRAY_DECLS, 2},   // Rule 3:  array_decls: array_decls array_decl
    {ARRAY_DECL, 4},    // Rule 4:  array_decl: ARRAY ID dims SEMI
    {DIMS, 4},          // Rule 5:  dims: dims LBRACKET NUM RBRACKET
    {DIMS, 3},          // Rule 6:  dims: LBRACKET NUM RBRACKET
    {STMT_SEQUENCE, 3}, // Rule 7:  stmt_sequence: stmt_sequence SEMI statement
    {STMT_SEQUENCE, 1}, // Rule 8:  stmt_sequence: statement
    {STATEMENT, 1},     // Rule 9:  statement: if_stmt
    {STATEMENT, 1},     // Rule 10: statement: repeat_stmt
    {STATEMENT, 1},     // Rule 11: statement: assign_stmt
    {STATEMENT, 1},     // Rule 12: statement: read_stmt
    {STATEMENT, 1},     // Rule 13: statement: write_stmt
    {IF_STMT, 5},       // Rule 14: if_stmt: IF exp THEN stmt_sequence END
    {IF_STMT, 7},       // Rule 15: if_stmt: IF exp THEN stmt_sequence ELSE stmt_sequence END
    {REPEAT_STMT, 4},   // Rule 16: repeat_stmt: REPEAT stmt_sequence UNTIL exp
    {ASSIGN_STMT, 3},   // Rule 17: assign_stmt: var ASSIGN exp
    {READ_STMT, 2},     // Rule 18: read_stmt: READ var
    {WRITE_STMT, 2},    // Rule 19: write_stmt: WRITE exp
    {EXP, 3},           // Rule 20: exp: simple_exp RELOP simple_exp
    {EXP, 1},           // Rule 21: exp: simple_exp
    {SIMPLE_EXP, 3},    // Rule 22: simple_exp: simple_exp PLUS term
    {SIMPLE_EXP, 3},    // Rule 23: simple_exp: simple_exp MINUS term
    {SIMPLE_EXP, 1},    // Rule 24: simple_exp: term
    {TERM, 3},          // Rule 25: term: term TIMES factor
    {TERM, 3},          // Rule 26: term: term OVER factor
    {TERM, 1},          // Rule 27: term: factor
    {FACTOR, 3},        // Rule 28: factor: LPAREN exp RPAREN
    {FACTOR, 1},        // Rule 29: factor: NUM
    {FACTOR, 1},        // Rule 30: factor: var
    {VAR, 2},           // Rule 31: var: ID var_dims
    {VAR_DIMS, 0},      // Rule 32: var_dims: ε
    {VAR_DIMS, 4}       // Rule 33: var_dims: var_dims LBRACKET exp RBRACKET
};
#endif // SYMBOL_HPP
