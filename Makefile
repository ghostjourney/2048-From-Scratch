CXX = g++
FLAGS = -std=c++20 -g -Wall


Linux:
	$(CXX) $(FLAGS) -c linux/*.cpp
	$(CXX) $(FLAGS) -lGL -lX11 -o linux_program *.o
clean:
	rm *.o