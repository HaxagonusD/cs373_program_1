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

void add_trantions(StateMachine * statemachine){
    for(int i = 0; i < statemachine->transitions.size(); i++){
        for(int j = 0; j < statemachine->all_states.size(); j++){
            if(statemachine->transitions.at(i)->currentName == statemachine->all_states.at(j)->name){
                statemachine->all_states.at(j)->transitions.push_back(statemachine->transitions.at(i));
            }
            else{
                bool duplicates = false;
                for(int k = 0; k < statemachine->all_states.size(); k++){
                     if(statemachine->transitions.at(i)->currentName == statemachine->all_states.at(k)->name){
                        duplicates = true;
                    }
                }
                if(!duplicates){
                    statemachine->reject_states.push_back(new State(statemachine->transitions.at(i)->currentName));
                    statemachine->all_states.push_back(statemachine->reject_states.back());
                    // statemachine->reject_states.back()->transitions.push_back(statemachine->transitions.at(i));
                }
            }
        }
    }
}


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
            size_t where = line.find("accept");
            if(where == string::npos){
                constructedMachine.reject_states.push_back(new State(permanent));
            }


			constructedMachine.start_states.push_back(new State(permanent));
            constructedMachine.all_states.push_back(constructedMachine.start_states.back());

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

            constructedMachine.accept_states.push_back(new State(permanent)); //this might create memory leaks
            constructedMachine.all_states.push_back(constructedMachine.accept_states.back());
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
            //the next line might create memory leaks
            constructedMachine.transitions.push_back(new Transition(stoi(lineHolder[0]), lineHolder[1], stoi(lineHolder[2])));

		}
    }

//TODO: add all the transitions to their respective states
    add_trantions(& constructedMachine);
    // for(int i = 0; i < constructedMachine.transitions.size(); i++){
    //     cout << constructedMachine.transitions.at(i)->currentName << " ";
    //     cout << constructedMachine.transitions.at(i)->symbol << " ";
    //     cout << constructedMachine.transitions.at(i)->nextName << endl;
    // }
    // for(int i = 0; i < constructedMachine.all_states.at(0)->transitions.size(); i++){
    //     cout << constructedMachine.all_states.at(0)->transitions.at(i)->currentName << " ";
    //     cout << constructedMachine.all_states.at(0)->transitions.at(i)->symbol << " ";
    //     cout << constructedMachine.all_states.at(0)->transitions.at(i)->nextName << endl;
    // }
    // for(int i = 0; i < constructedMachine.all_states.size(); i++){
    //     cout << constructedMachine.all_states.at(i)->name << ": transtions:" << endl;
    //     for(int j = 0; j < constructedMachine.all_states.at(i)->transitions.size(); j++){
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->currentName << " ";
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->symbol << " ";
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->nextName << endl;
    //     }
    //
    // }
//There probably are some memory leaks before this point in the program but I can't get valgrind to run

    string inputString = argv[2];
    int inputStringSize = inputString.length();
    constructedMachine.progression.push_back(constructedMachine.start_states);
    vector<State *> temp;
    for(int i = 0; i < inputStringSize; i++){ // character input string
        for(int j = 0; j < constructedMachine.progression.size(); j++){ // Vector of state pointers in progression
            for(int k = 0; k < constructedMachine.progression.at(j).size(); k++){ //state pointer in vector of state pointer
                for(int l = 0; l <constructedMachine.progression.at(j).at(k)->transitions.size(); l++){ // transition in state
                    if(constructedMachine.progression.at(j).at(k)->transitions.at(l)->symbol.compare(string(1, inputString[k])) == 0){
                        for(int m = 0; m < constructedMachine.all_states.size(); m++){
                            if(constructedMachine.progression.at(j).at(k)->transitions.at(l)->nextName == constructedMachine.all_states.at(m)->name){
                                temp.push_back(constructedMachine.all_states.at(m));
                            }
                        }
                    }
                }
            }
        }
        constructedMachine.progression.push_back(temp);
        temp.clear();
    }
    for(int i = 0; i < constructedMachine.progression.back().size(); i++){
        bool itsIn = false;

        for(int j = 0; j < constructedMachine.output.size(); j++){
            /* TODO:
                if ther state in the last vector progreassion is not in the output
                put it in the output
            */

            if(constructedMachine.progression.back().at(i)->name == constructedMachine.output.at(j)->name){
                itsIn =true;
            }

        }
        if(!itsIn){
            constructedMachine.output.push_back(constructedMachine.progression.back().at(i));
        }
        // cout << constructedMachine.progression.back().at(i)->name << endl;
    }
    // for(int i =0; i < constructedMachine.output.size(); i++){
    //     cout << constructedMachine.output.at(i)->name;
    // }
    bool accept = false;
    for(int i =0; i < constructedMachine.output.size(); i++){
        for(int j = 0; j < constructedMachine.accept_states.size(); j++){
            if(constructedMachine.output.at(i)->name == constructedMachine.accept_states.at(j)->name){
                accept = true;
            }
        }
    }

    // cout << constructedMachine.reject_states.size() << endl;



    if(accept){
        cout << "accept ";
        for(int i = 0; i < constructedMachine.output.size(); i++){
            for(int j = 0; j < constructedMachine.accept_states.size(); j++){
                if(constructedMachine.output.at(i)->name == constructedMachine.accept_states.at(j)->name){
                    cout << constructedMachine.accept_states.at(j)->name << " ";
                }
            }
        }
        cout << endl;
    }
    else {
        cout << " reject ";

        for(int i = 0; i < constructedMachine.output.size(); i++){

            for(int j = 0; j < constructedMachine.reject_states.size(); j++){
                if(constructedMachine.output.at(i)->name == constructedMachine.reject_states.at(j)->name){
                    cout << constructedMachine.reject_states.at(j)->name << " ";
                }
            }
        }
        cout << endl;
    }

    // for(int i = 0; i < constructedMachine.accept_states.size(); i++){
    //     cout << constructedMachine.accept_states.at(i)->name << endl;
    // }



    // for(int i = 0; i < constructedMachine.transitions.size(); i++){
    //     cout << constructedMachine.transitions.at(i)->currentName << " ";
    //     cout << constructedMachine.transitions.at(i)->symbol << " ";
    //     cout << constructedMachine.transitions.at(i)->nextName << endl;
    // }


    // for(int i = 0; i < constructedMachine.all_states.size(); i++){
    //     cout << constructedMachine.all_states.at(i)->name << ": transitions: "<< endl;
    //     for(int j =0; j < constructedMachine.all_states.at(i)->transitions.size(); j++){
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->currentName << " ";
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->symbol << " ";
    //         cout << constructedMachine.all_states.at(i)->transitions.at(j)->nextName << endl;
    //     }
    // }

    // for(int i =0; i < constructedMachine.output.size(); i++){
    //     cout << constructedMachine.output.at(i)->name << " ";
    // } cout << endl;



    // for(int i =0; i < constructedMachine.progression.back().size(); i++){
    //     cout << constructedMachine.progression.back().at(i)->name << " ";
    // } cout << endl;

 /*TODO:
    fix the problem
    where the 6th is not being outputed to the progression vector in statemachine class

 */
    someTextFile.close();
}
#endif
