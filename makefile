all: run_helper
	g++ -g -Wall -o run run_helper.o
run_helper: state statemachine transition run_helper.cpp
	g++ -c run_helper.cpp State.cpp Transition.cpp StateMachine.cpp
state: State.cpp State.h transition
	g++ -c State.cpp State.h Transition.h
statemachine:
	g++ -c StateMachine.cpp StateMachine.h
transition: Transition.cpp Transition.h
	g++ -c Transition.cpp Transition.h
run: all
	./run
clean:
	rm -r *.o *.h.gch run
