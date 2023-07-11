all: compile link 

# Change path with your SFML directory 
compile:
	g++ -ISFML/include -c main.cpp game.cpp wall.cpp

# Change path with your SFML directory 
link:
	g++ main.o game.o wall.o -o main -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system