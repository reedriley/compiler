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
%type <val> rexp
%type <val> iexp_1
%type <val> iexp_2
%type <val> iexp_3
%type <val> iexp_4

%% /* Grammar rules and actions follow.  */

input: /* empty */
     | input line
     ;

line: '\n'
    | 'r' rexp '\n'      { printf ("= \t%.10g\n", $2); }
    | 'i' iexp_1 '\n'    { printf ("= \t%.10g\n", $2); }
    | 'h' 'i' '\n'  { printf ("Hello!\n"); }
    | error '\n'
    ;

rexp: NUM           { $$ = $1;           }

   /* Expressions */
   | rexp rexp '+'   { $$ = $1 + $2;      }
   | rexp rexp '-'   { $$ = $1 - $2;      }
   | rexp rexp '*'   { $$ = $1 * $2;      }
   | rexp rexp '/'   { $$ = $1 / $2;      }

    /* Exponentiation */
   | rexp rexp '^'   { $$ = pow ($1, $2); }

    /* Unary minus    */
   | rexp 'n'       { $$ = -$1;          }
   ;

iexp_1: iexp_2            { $$ = $1;           }
      | iexp_2 '+' iexp_2 { $$ = $1 + $3;      }
      | iexp_2 '-' iexp_2 { $$ = $1 - $3;      }
      ;

iexp_2: iexp_3            { $$ = $1            }
      | iexp_3 '*' iexp_3 { $$ = $1 * $3;      }
      | iexp_3 '/' iexp_3 { $$ = $1 / $3;      }
      ;

iexp_3: iexp_4            { $$ = $1            }
      | iexp_4 '^' iexp_4 { $$ = pow ($1, $3); }
      | '-' iexp_4        { $$ = -$2;          }
      ;

iexp_4: NUM               { $$ = $1;           }
      | '(' iexp_1 ')'    { $$ = $2;           }
   ;
%%
