#include "Transition.h"

Transition::Transition(int n, string s, int z){
    this->symbol = s;
    this->currentName = n;
    this->nextName = z;
}
