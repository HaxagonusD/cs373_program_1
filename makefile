all: run_helper
	g++ -g -Wall -o quezada_p1 quezada_p1.o State.o StateMachine.o Transition.o
quezada_p1: run_helper
	g++ -g -Wall -o quezada_p1 quezada_p1.o State.o StateMachine.o Transition.o
run_helper: transition state statemachine quezada_p1.cpp
	g++ -c quezada_p1.cpp
state: State.cpp State.h
	g++ -c State.cpp
statemachine:
	g++ -c StateMachine.cpp
transition: Transition.cpp Transition.h
	g++ -c Transition.cpp
run: quezada_p1
	./run
clean:
	rm -r *.o *.h.gch run
