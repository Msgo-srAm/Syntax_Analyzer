%{
#include <stdio.h>
void yyerror(const char *s);
int yylex();
%}

/* 定义所有终结符 (Tokens) */
%token ARRAY ID SEMI LBRACKET NUM RBRACKET
%token IF THEN END ELSE REPEAT UNTIL
%token ASSIGN READ WRITE
%token RELOP PLUS MINUS TIMES OVER LPAREN RPAREN

/* 定义起始符号 */
%start program

%%

/* (0) program' -> program (Bison自动处理) */

/* (1) program -> array_decls stmt_sequence */
program:
    array_decls stmt_sequence
    ;

/* (2) array_decls -> array_decls array_decl */
/* (3) array_decls -> ε */
array_decls:
    /* empty */
    | array_decls array_decl
    ;

/* (4) array_decl -> ARRAY ID dims SEMI */
array_decl:
    ARRAY ID dims SEMI
    ;

/* (5) dims -> dims LBRACKET NUM RBRACKET */
/* (6) dims -> LBRACKET NUM RBRACKET */
dims:
    dims LBRACKET NUM RBRACKET
    | LBRACKET NUM RBRACKET
    ;

/* (7) stmt_sequence -> stmt_sequence SEMI statement */
/* (8) stmt_sequence -> statement */
stmt_sequence:
    stmt_sequence SEMI statement
    | statement
    ;

/* (9)-(13) statement 各种产生式 */
statement:
    if_stmt
    | repeat_stmt
    | assign_stmt
    | read_stmt
    | write_stmt
    ;

/* (14) if_stmt -> IF exp THEN stmt_sequence END */
/* (15) if_stmt -> IF exp THEN stmt_sequence ELSE stmt_sequence END */
if_stmt:
    IF exp THEN stmt_sequence END
    | IF exp THEN stmt_sequence ELSE stmt_sequence END
    ;

/* (16) repeat_stmt -> REPEAT stmt_sequence UNTIL exp */
repeat_stmt:
    REPEAT stmt_sequence UNTIL exp
    ;

/* (17) assign_stmt -> var ASSIGN exp */
assign_stmt:
    var ASSIGN exp
    ;

/* (18) read_stmt -> READ var */
read_stmt:
    READ var
    ;

/* (19) write_stmt -> WRITE exp */
write_stmt:
    WRITE exp
    ;

/* (20) exp -> simple_exp RELOP simple_exp */
/* (21) exp -> simple_exp */
exp:
    simple_exp RELOP simple_exp
    | simple_exp
    ;

/* (22)-(24) simple_exp */
simple_exp:
    simple_exp PLUS term
    | simple_exp MINUS term
    | term
    ;

/* (25)-(27) term */
term:
    term TIMES factor
    | term OVER factor
    | factor
    ;

/* (28)-(30) factor */
factor:
    LPAREN exp RPAREN
    | NUM
    | var
    ;

/* (31) var -> ID var_dims */
var:
    ID var_dims
    ;

/* (32) var_dims -> var_dims LBRACKET exp RBRACKET */
/* (33) var_dims -> ε */
var_dims:
    /* empty */
    | var_dims LBRACKET exp RBRACKET
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}