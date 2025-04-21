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

void collect_states(State *current, State **seen, int *seen_count) {
  for (int i = 0; i < *seen_count; i++) {

    // Check if the current state has already been noted down
    if (seen[i] == current) {
      return;
    }
  } 

  seen[*seen_count] = current;
  (*seen_count)++;

  for (int i = 0; i < current->transition_count; i++) {
    collect_states(current->transitions[i].to, seen, seen_count);
  }
}

void print_graphviz(DFA *dfa) {
  FILE *fptr = fopen("out/dfa.dot", "w");

  State *collected_states[MAX_STATES];
  int state_count = 0;

  collect_states(dfa->start, collected_states, &state_count);

  fprintf(fptr, 
"digraph DFA {\n\
  rankdir=LR;\n\
  node [shape = circle];\n\
  \n");

  for (int i = 0; i < state_count; i++) {
    fprintf(fptr, "  q%c [label=\"q%c\"",
            collected_states[i]->name,
            collected_states[i]->name);

    if (collected_states[i] == dfa->final) {
      fprintf(fptr, ", shape=doublecircle");
    }
    fprintf(fptr, "];\n");

    for (int j = 0; j < collected_states[i]->transition_count; j++) {
      fprintf(fptr, "  q%c -> q%c [label=\"%c\"];\n",
              collected_states[i]->name,
              collected_states[i]->transitions[j].to->name,
              collected_states[i]->transitions[j].symbol);
    }
  }

  fprintf(fptr, "}");
  fclose(fptr);

  system("dot -Tjpg out/dfa.dot -o out/dfa.jpg");
  printf("Check out/dfa.jpg for your image\n");
}
