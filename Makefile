all:
	g++ -Wall -o run *.cpp utils/*.cpp -lglut -lGLU -lGL -lm
