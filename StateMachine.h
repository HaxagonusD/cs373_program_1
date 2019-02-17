#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.h"
#include <vector>
using namespace std;
class StateMachine{
public:
    vector<State *> start_states;
    vector<State *> accept_states;
    vector<State *> reject_states;
    vector<State *> all_states;
    vector<State *> output;
    vector<Transition *> transitions;
    vector<vector<State *>> progression;

};
#endif
