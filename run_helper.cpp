#ifndef RUN_HELPER_CPP
#define RUN_HELPER_CPP
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include "Transition.h"
#include "StateMachine.h"
#include "State.h"

using namespace std;

//
// void interpret_the_line(string single_line){
//
// Node * toBeDeleted = get_node_at_index(index);
// 	Node * next = toBeDeleted->next;
// 	Node * prev = toBeDeleted->prev;
// 	prev->next = next;
// 	next->previous = prev;
// 	delete toBeDeleted;
// 	return true;
// }

int main(int argc, char *argv[]){
	//gets the name of the file from the commandline
    string nameOfFile = argv[1];
	//opens the file as a read stream
    ifstream someTextFile;
    someTextFile.open(nameOfFile);
	//the string line is where the each line fo the file is going to be stored
    string line = "";
	//this is the statemachine that represents the statemachine in the file
	StateMachine constructedMachine;
	//go through every line in the file and store it in the string line
    while(getline(someTextFile, line)){
		//determine if this line is a start state
		size_t where = line.find("start");
		//if it is, make a new state and add it to the statemachine as a star state
		if (where != string::npos){
			//finds the number in the start linesand convert it into an int
			stringstream ss;
			ss << line;
			string temp = "";
			int stateName = 0;
			while(!ss.eof()){
				ss >> temp;
				stringstream(temp) >> stateName;
				temp = "";
			}
			//add the state to the STATEMACHINE
			State someState = State(stateName);
			constructedMachine.start_states.push_back(&someState);
		}
		where = line.find("accept");
		if(where != string::npos){
			stringstream ss;
			ss << line;
			string temp = "";
			int stateName = 0;
			while(!ss.eof()){
				ss >> temp;
				stringstream(temp) >> stateName;
				temp = "";
			}
			//add the state to the STATEMACHINE
			State someState = State(stateName);
			constructedMachine.accept_states.push_back(&someState);
		}
    }


    someTextFile.close();
}
#endif
