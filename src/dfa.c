#include "../include/dfa.h"

#include <stdio.h>

State *dfa_compute(DFA *dfa, State *current, const char * const word) {
  if (!*word) return current;

  for (int i = 0; i < current->transition_count; i++) {
    if (current->transitions[i].symbol == *word) {
      return dfa_compute(dfa, current->transitions[i].to, word + 1);
    }
  }

  return NULL;
}

int check_acceptance(DFA *dfa, State *current) {
  return current == dfa->final;
}
