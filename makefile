CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

#Executing name
EXE = library_system

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)
