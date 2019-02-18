all: run_helper
	g++ -g -Wall -o run run_helper.o State.o StateMachine.o Transition.o
run_helper: transition state statemachine run_helper.cpp
	g++ -c run_helper.cpp
state: State.cpp State.h
	g++ -c State.cpp
statemachine:
	g++ -c StateMachine.cpp
transition: Transition.cpp Transition.h
	g++ -c Transition.cpp
run: all
	./run sample_1.txt 000
clean:
	rm -r *.o *.h.gch run
