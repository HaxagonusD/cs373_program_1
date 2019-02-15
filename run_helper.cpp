#ifndef RUN_HELPER_CPP
#define RUN_HELPER_CPP
#include <iostream>
#include <fstream>
#include <string.h>
#include "Transition.h"
#include "StateMachine.h"
#include "State.h"

using namespace std;


void interpret_the_line(string single_line){

Node * toBeDeleted = get_node_at_index(index);
	Node * next = toBeDeleted->next;
	Node * prev = toBeDeleted->prev;
	prev->next = next;
	next->previous = prev;
	delete toBeDeleted;
	return true;
}

int main(int argc, char *argv[]){
    string nameOfFile = argv[1];
    ifstream someTextFile;
    someTextFile.open(nameOfFile);
    string line;
    while(getline(someTextFile, line)){

        cout << line << endl;
    }

    someTextFile.close();
}
#endif
