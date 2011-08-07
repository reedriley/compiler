#include <iostream>

#include "fran.h"

extern "C" int yyparse();

int main(int argc, char *argv[]) {
  return yyparse ();
}
