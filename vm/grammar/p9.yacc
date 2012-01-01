%token T_ASSIGN
%token T_ASSIGN_NUMERIC_ADD T_ASSIGN_NUMERIC_SUB T_ASSIGN_NUMERIC_MUL T_ASSIGN_NUMERIC_DIV T_ASSIGN_NUMERIC_MOD
%token T_ASSIGN_BINARY_NOT T_ASSIGN_BINARY_AND T_ASSIGN_BINARY_OR T_ASSIGN_BINARY_XOR T_ASSIGN_BINARY_LSHIFT T_ASSIGN_BINARY_RSHIFT
%token T_NUMERIC_ADD T_NUMERIC_SUB T_NUMERIC_MUL T_NUMERIC_DIV T_NUMERIC_MOD
%token T_BINARY_NOT T_BINARY_AND T_BINARY_OR T_BINARY_XOR T_BINARY_LSHIFT T_BINARY_RSHIFT
%token T_LOGICAL_NOT T_LOGICAL_AND T_LOGICAL_OR
%token T_RELATIONAL_EQUAL T_RELATIONAL_DIFFERENT T_RELATIONAL_LESSER T_RELATIONAL_GREATER T_RELATIONAL_LESSER_OR_EQUAL T_RELATIONAL_GREATER_OR_EQUAL
%token T_INCREMENT T_DECREMENT

%token T_LBRACE T_RBRACE
%token T_LPARENTHESIS T_RPARENTHESIS
%token T_LBRACKET T_RBRACKET

%token T_DOT T_COMMA T_SEMICOLON T_COLON

%token T_THIS
%token T_NEW
%token T_FUNCTION T_CLASS
%token T_PUBLIC T_PRIVATE
%token T_IMPORT T_FROM T_AS
%token T_RETURN
%token T_MIXED

%token T_IDENTIFIER
%token T_NUMBER
%token T_STRING

%token T_UNEXPECTED

%{
#include <stdio.h>
void yyerror( char const * err ) { printf( "Error : %s\n", err ); }
int yywrap( void ) { return 1; }
int main( void ) { yyparse( ); return 0; }
int yydebug = 0;
%}

%start Program

%%

Program                  : StatementList ;

StatementList            : Statement StatementList
                         | /* no more statement */
                         ;

Statement                : Block
                         | ImportStatement
                         | VariableStatement
                         | ExpressionStatement
                         | EmptyStatement
                         ;

Block                    : T_LBRACE StatementList T_RBRACE;

ImportStatement          : ImportFrom T_IMPORT T_IDENTIFIER ImportAs T_SEMICOLON;
                         ;

ImportFrom               : T_FROM ImportPath
                         | /* no from clause */
                         ;

ImportAs                 : T_AS T_IDENTIFIER
                         | /* no as clause */
                         ;

ImportPath               : T_IDENTIFIER ImportPathNext
                         ;

ImportPathNext           : T_DOT ImportPath
                         | /* end of path */
                         ;

VariableStatement        : Type T_IDENTIFIER T_SEMICOLON
                         | Type T_IDENTIFIER T_ASSIGN Expression T_SEMICOLON
                         ;

ExpressionStatement      : Expression T_SEMICOLON
                         ;

EmptyStatement           : T_SEMICOLON
                         ;

Expression               : ExpressionLevel13
                         ;

ExpressionLevel13        : ExpressionLevel12
                         | ExpressionLevel12 T_ASSIGN ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_NUMERIC_ADD ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_NUMERIC_SUB ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_NUMERIC_MUL ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_NUMERIC_DIV ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_NUMERIC_MOD ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_BINARY_AND ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_BINARY_OR ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_BINARY_XOR ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_BINARY_LSHIFT ExpressionLevel13
                         | ExpressionLevel12 T_ASSIGN_BINARY_RSHIFT ExpressionLevel13
                         ;

ExpressionLevel12        : ExpressionLevel11
                         | ExpressionLevel11 T_LOGICAL_OR ExpressionLevel12
                         ;

ExpressionLevel11        : ExpressionLevel10
                         | ExpressionLevel10 T_LOGICAL_AND ExpressionLevel11
                         ;

ExpressionLevel10        : ExpressionLevel09
                         | ExpressionLevel09 T_BINARY_OR ExpressionLevel10
                         ;

ExpressionLevel09        : ExpressionLevel08
                         | ExpressionLevel08 T_BINARY_XOR ExpressionLevel09
                         ;

ExpressionLevel08        : ExpressionLevel07
                         | ExpressionLevel07 T_BINARY_AND ExpressionLevel08
                         ;

ExpressionLevel07        : ExpressionLevel06
                         | ExpressionLevel06 T_RELATIONAL_EQUAL ExpressionLevel07
                         | ExpressionLevel06 T_RELATIONAL_DIFFERENT ExpressionLevel07
                         ;

ExpressionLevel06        : ExpressionLevel05
                         | ExpressionLevel05 T_RELATIONAL_LESSER ExpressionLevel06
                         | ExpressionLevel05 T_RELATIONAL_GREATER ExpressionLevel06
                         | ExpressionLevel05 T_RELATIONAL_LESSER_OR_EQUAL ExpressionLevel06
                         | ExpressionLevel05 T_RELATIONAL_GREATER_OR_EQUAL ExpressionLevel06
                         ;

ExpressionLevel05        : ExpressionLevel04
                         | ExpressionLevel04 T_BINARY_LSHIFT ExpressionLevel05
                         | ExpressionLevel04 T_BINARY_RSHIFT ExpressionLevel05
                         ;

ExpressionLevel04        : ExpressionLevel03
                         | ExpressionLevel03 T_NUMERIC_ADD ExpressionLevel04
                         | ExpressionLevel03 T_NUMERIC_SUB ExpressionLevel04
                         ;

ExpressionLevel03        : ExpressionLevel02
                         | ExpressionLevel02 T_NUMERIC_MUL ExpressionLevel03
                         | ExpressionLevel02 T_NUMERIC_DIV ExpressionLevel03
                         | ExpressionLevel02 T_NUMERIC_MOD ExpressionLevel03
                         ;

ExpressionLevel02        : ExpressionLevel01
                         | T_INCREMENT ExpressionLevel01
                         | T_DECREMENT ExpressionLevel01
                         | T_NUMERIC_ADD ExpressionLevel01
                         | T_NUMERIC_SUB ExpressionLevel01
                         | T_BINARY_NOT ExpressionLevel01
                         | T_LOGICAL_NOT ExpressionLevel01
                         ;

ExpressionLevel01        : ExpressionLevel00
                         | ExpressionLevel00 T_INCREMENT
                         | ExpressionLevel00 T_DECREMENT
                         ;

ExpressionLevel00        : MemberExpression
                         | CallExpression
                         | NewExpression
                         ;

CallExpression           : MemberExpression CallArguments
                         ;

NewExpression            : T_NEW MemberExpression CallArguments
                         ;

MemberExpression         : PrimaryExpression
                         | MemberExpression T_DOT T_IDENTIFIER
                         | MemberExpression T_LBRACKET Expression T_RBRACKET
                         ;

PrimaryExpression        : T_THIS
                         | T_IDENTIFIER
                         | Literal
                         | T_LPARENTHESIS Expression T_RPARENTHESIS
                         ;

Literal                  : NumberLiteral
                         | StringLiteral
                         | ArrayLiteral
                         | ObjectLiteral
//                       | FunctionLiteral
//                       | ClassLiteral
                         ;

NumberLiteral            : T_NUMBER
                         ;

StringLiteral            : T_STRING
                         ;

ArrayLiteral             : T_LBRACKET T_RBRACKET
                         | T_LBRACKET ValueList T_RBRACKET
                         ;

ObjectLiteral            : T_LBRACE T_RBRACE
                         | T_LBRACE PairList T_RBRACE
                         ;

CallArguments            : T_LPARENTHESIS T_RPARENTHESIS
                         | T_LPARENTHESIS ValueList T_RPARENTHESIS
                         ;

ValueList                : Expression
                         | ValueList T_COMMA Expression
                         ;

PairList                 : T_IDENTIFIER T_COLON Expression
                         | PairList T_COMMA T_IDENTIFIER T_COLON Expression
                         ;

Type                     : T_MIXED
                         | T_IDENTIFIER
                         ;
