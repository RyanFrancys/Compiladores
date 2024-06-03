%{
    int yyerror(const char *s);
    int yylex(void);
%}

%define parse.error verbose

%token TOK_ID
%token TOK_PF
%token TOK_INTEIRO
%token TOK_PALAVRA
%token TOK_BOLEANO

%token TOK_MOSTRA
%token TOK_ENQUANTO
%token TOK_SE
%token TOK_SENAO
%token TOK_CASO
%token TOK_LOOP


%token TOK_E
%token TOK_OU
%token TOK_NAO
%token TOK_IGUAL
%token TOK_DIFERENTE

%start program

%%

program : globals;

globals: global globals{}
        |global {}

global: TOK_ID '=' expr ';' {}
        |TOK_MOSTRA factor ';' {}
        |TOK_SE  cmprt  '{' globals '}' {}
        |TOK_SE  cmprt  '{' globals '}' TOK_SENAO '{' globals '}'  {}
        |TOK_ENQUANTO  cmprt '{' globals '}' {}
        |TOK_LOOP '{' globals'}'

cmprt:  '(' cmprt TOK_E cmprt ')' {}
        |'(' cmprt TOK_OU  cmprt ')' {}
        |'(' cmprt '<' cmprt ')' {}
        |'(' cmprt TOK_DIFERENTE cmprt ')' {}
        |'(' cmprt '>' cmprt ')'{}
        |'(' cmprt TOK_IGUAL cmprt ')' {}
        |factor {}

expr:   expr '+' term   {}
        |expr '-' term  {}
        |term   {}

term:   term '*' factor{}
        |term '/' factor{}
        |factor{}

factor: '(' expr ')'    {}
        |TOK_PALAVRA    {}
        |TOK_INTEIRO    {}
        |TOK_BOLEANO    {}
        |TOK_ID {}
        |TOK_PF {}
        |unary   {}

unary:  '-' factor      {}
        |'+' factor     {}

%%
