#ifndef STATE_H
#define STATE_H
#include "Transition.h"

class State{
public:
State(int);
int name;
Transition * transitions[];
};
#endif
