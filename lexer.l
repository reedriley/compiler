%{
#include <stdlib.h>
#include "parser.tab.hpp"
%}

%option nounput
%option noyywrap

%%

[0-9.]+       yylval.val=strtod(yytext, NULL); return NUM;
\n            return *yytext;
[ \t]         /* ignore */;
.             return *yytext;

%%
