#ifndef DFA_H
#define DFA_H

#define MAX_TRANSITIONS 8
#define MAX_STATES 64

typedef struct State State;

typedef struct {
  char symbol;
  State *to;
} Transition;

struct State {
  char name;
  Transition transitions[MAX_TRANSITIONS];
  int transition_count;
};

typedef struct {
  State *start;
  State *final;
} DFA;

State *dfa_compute(DFA *dfa, State *current, const char * const word);
int check_acceptance(DFA *dfa, State *current);
void collect_states(State *state, State **seen, int *seen_count);
void print_graphviz(DFA *dfa);

#endif
