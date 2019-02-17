#ifndef TRANSITION_H
#define TRANSITION_H
#include <iostream>
#include <string>
using namespace std;
class Transition{
public:
    Transition(int, string, int);
    string symbol;
    int currentName;
    int nextName;
};
#endif
