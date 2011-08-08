/* TODO: Remove this, it's taken from BISON's documentation */
/* Reverse polish notation calculator.  */

%{
  #include <math.h>
  #include <stdio.h>

  int yylex (void);
  void yyerror (char const * err) {
    printf ("%s", err);
  }
%}

%union {
  double val;
}

%defines
%token <val> NUM
%type <val> exp
%type <val> line
%type <val> input

%% /* Grammar rules and actions follow.  */

input: /* empty */
     | input line
     ;

line: '\n'
    | exp '\n'      { printf ("= \t%.10g\n", $1); }
    | 'h' 'i' '\n'  { printf ("Hello!\n"); }
    | error '\n'
    ;

exp: NUM           { $$ = $1;           }

   /* Expressions */
   | exp exp '+'   { $$ = $1 + $2;      }
   | exp exp '-'   { $$ = $1 - $2;      }
   | exp exp '*'   { $$ = $1 * $2;      }
   | exp exp '/'   { $$ = $1 / $2;      }

    /* Exponentiation */
   | exp exp '^'   { $$ = pow ($1, $2); }

    /* Unary minus    */
   | exp 'n'       { $$ = -$1;          }
   ;
%%
