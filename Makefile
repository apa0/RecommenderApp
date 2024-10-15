CXX = g++
OPTIONS = -Wall -std=c++17
PROGRAM = main.out

all: $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM) $(ARGS)

$(PROGRAM): main.cpp Recommend.cpp 
	$(CXX) $(OPTIONS) main.cpp Recommend.cpp -o $(PROGRAM) 

clean:
	rm -f $(PROGRAM)