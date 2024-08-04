CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = Bard.o List.o

bard: $(OBJECTS)
	    $(CXX) -g $(CXXFLAGS) -o $@ Bard.o List.o

Bard.o: Bard.cpp List.cpp List.h
		$(CXX) -g $(CXXFLAGS) -c Bard.cpp

List.o: List.cpp List.h
		$(CXX) -g $(CXXFLAGS) -c List.cpp

clean:
	rm *.o
	rm bard
