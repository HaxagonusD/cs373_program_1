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
			// finds the number in the start linesand convert it into an int
			stringstream ss;
			ss << line;
			string temp = "";
			int stateName = 0;
            int permanent = 0;
			while(!ss.eof()){
				ss >> temp;
				if(stringstream(temp) >> stateName){
                    permanent = stateName;
                }

			}
			//add the state to the STATEMACHINE



			constructedMachine.start_states.push_back(new State(permanent));

            permanent = 0;


		}
		//do the same for the accept states
		where = line.find("accept");
		if(where != string::npos){
			stringstream ss;
			ss << line;
			string temp = "";
			int stateName = 0;
            int permanent = 0;
			while(!ss.eof()){
				ss >> temp; // read word by word
				if(stringstream(temp) >> stateName){
                    permanent = stateName;
                } //put the word into the int variable if it fits
				temp = "";
			}
			//add the state to the STATEMACHINE

            constructedMachine.accept_states.push_back(new State(permanent));
            permanent = 0;

		}

		where = line.find("transition");
		if(where != string::npos){

			stringstream ss;
			string temp = "";

            line.replace(0, 11, ""); //removes the transtion word
            ss << line;
            string lineHolder[3];
            int index = 0;
            while(!ss.eof()){
                ss >> temp;
                lineHolder[index] = temp;
                index++;
            }
            index = 0;
            constructedMachine.transitions.push_back(Transition(stoi(lineHolder[0]), lineHolder[1], stoi(lineHolder[2])));

		}
    }


//There probably are some memory leaks before this point in the program but I can't get valgrind to run
/*TODO
        Create a vector made up  vectors for every input in the input string - Because it's a vector I dont have to know the size of the list
        Add the starting vector to the list
        for every symbol in the list
            Aloow all the states in the list to process the input string
            creating a state and adding it to the next list
*/


    someTextFile.close();
}
#endif
