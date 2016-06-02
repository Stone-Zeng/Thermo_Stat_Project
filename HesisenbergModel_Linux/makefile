SOURCES = HeisenbergModel_Main.cpp SingleSimulation.cpp MyLattice.cpp Physics.cpp MyVector.cpp MyTiming.cpp VectorTest.cpp

NAME = EXE
OPTION = -std=c++11 -O2 -Wall
PARALLEL = -fopenmp

all:
	g++ $(SOURCES) -o $(NAME) $(OPTION) $(PARALLEL)
np:
	g++ $(SOURCES) -o $(NAME) $(OPTION)

clean:
	rm -f *.csv *.vector *~
