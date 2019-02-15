#ifndef STATE_H
#define STATE_H
#include "Transition.h"
#include <vector>
using namespace std;
class State{
public:
    State(int);
    int name;
    vector<Transition *> transitions;
};
#endif
