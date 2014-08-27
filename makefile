enigma: main.o terminal.o rotor.o reflector.o transformer.o plugboard.o
	g++ -g -Wall main.o terminal.o rotor.o reflector.o transformer.o plugboard.o -o enigma

main.o: main.cpp terminal.hpp constants.h
	g++ -g -Wall main.cpp -c

terminal.o: terminal.cpp terminal.hpp transformer.hpp rotor.hpp reflector.hpp plugboard.hpp constants.h errors.h
	g++ -g -Wall terminal.cpp -c

transformer.o: transformer.cpp transformer.hpp errors.h constants.h
	g++ -g -Wall transformer.cpp -c

rotor.o: rotor.cpp rotor.hpp transformer.hpp errors.h constants.h
	g++ -g -Wall rotor.cpp -c

reflector.o: reflector.cpp reflector.hpp transformer.hpp errors.h constants.h
	g++ -g -Wall reflector.cpp -c

plugboard.o: plugboard.cpp plugboard.hpp transformer.hpp errors.h constants.h
	g++ -g -Wall plugboard.cpp -c

clean:
	rm *.o
