#include <stdio.h>
#include "../include/dfa.h"

int main() {
  State q0 = {0}, q1 = {0};

  q0.name = '0';
  q0.transitions[0] = (Transition){'a', &q1};
  q0.transition_count++;

  q1.name = '1';
  q1.transitions[0] = (Transition){'t', &q0};
  q1.transition_count++;

  DFA dfa = (DFA) {
    &q0,
    &q1
  };

  State *computed = dfa_compute(&dfa, dfa.start, "atata");

  if (check_acceptance(&dfa, computed)) {
    printf("Input was accepted");
  } else {
    printf("Input was not accepted");
  }


  return 0;
}
