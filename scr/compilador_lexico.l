%{
#include <stdio.h>
#include <stdlib.h>

class Node;
#include "compilador_sintatico.tab.h"
int yyerror(const char *s);
%}

%%
[ \t\r\n_]  {   /*ignora*/  }
"//".*\n { /*Comentário*/ }

"mostra" { return TOK_MOSTRA ; }

"enquanto" {return TOK_ENQUANTO ; }
"loop"  {return TOK_LOOP;}
"se" {return TOK_SE ;}
"senao" {return TOK_SENAO;}
"NAO" {return TOK_NAO ;}
"E" {return TOK_E ;}
"OU" {return TOK_OU ;}
"==" {return TOK_IGUAL ;}
"!=" {return TOK_DIFERENTE ;}
"+" {return '+' ; }
"-" {return '-' ; }
"*" {return '*' ; }
"/" {return '/' ; }
"(" {return '(' ; }
")" {return ')' ; }
";" {return ';' ; }
"=" {return '=' ; }
"<" {return '<' ; }
">" {return '>' ; }
"{" {return '{' ; }
"}" {return '}' ; }


([V][E][R][D][A][D][E]|[F][A][L][S][O]) {return TOK_BOLEANO;}

[a-zA-Z_][a-zA-Z0-9_]* {return TOK_ID ; }

[0-9]+\.[0-9]* {return TOK_PF ; }

[0-9]+  {return TOK_INTEIRO ; }

\"([^\\\"]|\\.)*\"  {return TOK_PALAVRA ; }

.   {printf("Simbolo não reconhecido! %c\n",yytext[0]);}

%%
int yywrap(){
    return 1;
}

int yyerror(const char *s){
    printf("Error de Sintaxe %d: %s.\n", yylineno,s);
    return 1;
}

int main(int argc, char *argv[]){
if(argc <= 1){
        printf("Sintaxe: %s nome_do_programa\n",argv[0]);
        return 1;
    }

    yyin = fopen(argv[1],"r");
    if(yyin == NULL){
        printf("Não foi possivel abrir o arquivo %s.\n",argv[1]);
        return 1;
    }
    
    yyparse();

    if(yyin)
        fclose(yyin);

    return 0;
}
