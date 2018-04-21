Ass_3:main.o Game.o Map.o Robot.o
	g++ main.o Game.o Map.o Robot.o -o Ass_3
Robot.o:Robot.cpp Robot.h
	g++ -c Robot.cpp
Map.o:Map.cpp Map.h
	g++ -c Map.cpp
Game.o:Game.cpp Game.h Robot.h Map.h
	g++ -c Game.cpp
main.o:main.cpp Game.h Robot.h Map.h
	g++ -c main.cpp
clean:
	rm -g *.o
