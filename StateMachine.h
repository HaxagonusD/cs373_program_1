#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "State.h"
#include <vector>
using namespace std;
class StateMachine{
vector<State *> start_states;
vector<State *> accept_states;
vector<State *> reject_states;

};
#endif