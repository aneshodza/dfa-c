#include "../include/dfa.h"

#include <stdlib.h>
#include <stdio.h>

State *dfa_compute(DFA *dfa, State *current, const char * const word) {
  if (!*word) return current;

  State *new = NULL;
  for (int i = 0; i < current->transition_count; i++) {
    if (current->transitions[i].symbol == *word) {
      if (new != NULL) {
        fprintf(stderr, "Error: DFA is nondeterministic at state q%c\n", current->name);
        exit(EXIT_FAILURE);
      }
      new = current->transitions[i].to;
    }
  }
  if (new != NULL) {
    return dfa_compute(dfa, new, word + 1);
  }

  return NULL;
}

int check_acceptance(DFA *dfa, State *current) {
  return current == dfa->final;
}

void print_graphviz(DFA *dfa) {
  FILE *fptr = fopen("out/dfa.dot", "w");

  fprintf(fptr,
"digraph DFA {\n\
  rankdir=LR;\n\
  node [shape = circle];\n\
  \n\
  q0 [label=\"q0\"];\n\
  q1 [label=\"q1\", shape=doublecircle];\n\
  \n\
  q0 -> q0 [label=\"a\"];\n\
  q0 -> q1 [label=\"b\"];\n\
}");

  system("dot -Tjpg out/dfa.dot -o out/dfa.jpg");
  printf("Check out/dfa.jpg for your image\n");
  
  fclose(fptr);
}
