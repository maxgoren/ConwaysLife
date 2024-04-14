life:
	g++ --std=c++17 -c life.cpp
	g++ --std=c++17 -c app.cpp
	g++ --std=c++17 -c main.cpp
	g++ *.o -o life -lsfml-window -lsfml-graphics -lsfml-system

debug:
	g++ --std=c++17 -g -c life.cpp
	g++ --std=c++17 -g -c app.cpp
	g++ --std=c++17 -g -c main.cpp
	g++ -g *.o -o life -lsfml-window -lsfml-graphics -lsfml-system