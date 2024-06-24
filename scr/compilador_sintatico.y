%{
#include "nodes.h"

extern bool force_print_tree;
int yyerror(const char *s);
int yylex(void);
%}

%define parse.error verbose

%union { 
    char *str;
    int itg;
    double flt;
    Node *node;
}

%token TOK_ID TOK_PF TOK_INTEIRO TOK_PALAVRA TOK_VERDADEIRO TOK_FALSO

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

%type<str> TOK_ID
%type<itg> TOK_INTEIRO
%type<flt> TOK_PF
%type<str> TOK_PALAVRA

%type<node> globals global cmprt expr term factor unary

%start program 

%%

program : globals       {Node *program = new Program();
                        program->append($globals);
                        
                        //Analise semantica




                        
                        if(error_count>0){
                                cout    << "\nForam encontrados "
                                        << error_count
                                        << " erros no  No código\n"
                                        << endl;  
                        }
                        if(force_print_tree||error_count==0){
                                printf_tree(program);
                        }

                        }

globals: globals[gg] global {$gg->append($global);
                        $$ = $gg;}
        |global { Node *n = new Node();
                n->append($global);
                $$ = n; }

global: TOK_ID '=' expr ';'     { $$ = new Variavel($TOK_ID,$expr);     }
        |TOK_MOSTRA factor ';' { $$ = new Mostra($factor);      }
        |TOK_SE  cmprt  '{' globals '}' { $$ = new Se($cmprt,$globals); }
        |TOK_SE  cmprt  '{' globals[g1] '}' TOK_SENAO '{' globals[g2] '}'       { $$ = new SeSenao($cmprt,$g1,$g2);     }
        |TOK_ENQUANTO  cmprt '{' globals '}'    { $$ = new Enquanto($cmprt,$globals);   }
        |TOK_LOOP '{' globals'}'        { $$ = new Loop($globals);      }
        |error ';'      { $$ = new Node();      }
        |error  { $$ = new Node();      }


cmprt:  '(' cmprt[c1] TOK_E cmprt[c2] ')'       { $$ = new OpBinaria($c1,'&',$c2);      }
        |'(' cmprt[c1] TOK_OU  cmprt[c2] ')'    { $$ = new OpBinaria($c1,'|',$c2);      }
        |'(' cmprt[c1] '<' cmprt[c2] ')'        { $$ = new OpBinaria($c1,'<',$c2);      }
        |'(' cmprt[c1] TOK_DIFERENTE cmprt[c2] ')'      { $$ = new OpBinaria($c1,'!',$c2);      }
        |'(' cmprt[c1] '>' cmprt[c2] ')'        { $$ = new OpBinaria($c1,'>',$c2);      }
        |'(' cmprt[c1] TOK_IGUAL cmprt[c2] ')'  { $$ = new OpBinaria($c1,'=',$c2);      }
        |factor { $$ = $factor; }

expr:   expr[e] '+' term   {$$ = new OpBinaria($e,'+',$term);   }
        |expr[e] '-' term  {$$ = new OpBinaria($e,'-',$term);   }
        |term   { $$ = $term;   }

term:   term[t] '*' factor {  $$ = new OpBinaria($t,'*',$factor);}
        |term[t] '/' factor        { $$ = new OpBinaria($t,'/',$factor);        }
        |factor { $$ = $factor; }

factor: '(' expr ')'    { $$ = $expr;   }
        |TOK_PALAVRA    { $$ = new Palavra($TOK_PALAVRA);       }
        |TOK_INTEIRO    { $$ = new Inteiro($TOK_INTEIRO);       }
        |TOK_ID { $$ = new Id($TOK_ID);    }
        |TOK_PF { $$ = new Pf($TOK_PF); }
        |unary  { $$ = $unary; }
        |TOK_FALSO      { $$ = new Boleano(true);       }
        |TOK_VERDADEIRO { $$= new Boleano(false);        }

unary:  '-' factor      { $$ = new Unario('-',$factor);   }
        |'+' factor     { $$ = new Unario('+',$factor);   }

%%
