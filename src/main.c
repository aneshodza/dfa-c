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
  //
  // State *collected_states[MAX_STATES];
  // int state_count = 0;
  //
  // collect_states(dfa.start, collected_states, &state_count);
  // printf("State count: %d\n", state_count);
  // printf("Found following states:\n");
  // for (int i = 0; i < state_count; i++) {
  //   printf("  - q%c\n", collected_states[i]->name);
  // }
  //
  print_graphviz(&dfa);

  State *computed = dfa_compute(&dfa, dfa.start, "atata");

  if (check_acceptance(&dfa, computed)) {
    printf("Input was accepted");
  } else {
    printf("Input was not accepted");
  }


  return 0;
}
