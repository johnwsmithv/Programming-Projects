linAlgDebug:
	g++ -g -std=c++20 LinearAlgebra.cpp main.cpp -pthread -fopenmp -o LinearAlgebra_Debug.exe

linAlg:
	g++ -O3 -std=c++20 LinearAlgebra.cpp main.cpp -pthread -fopenmp -o LinearAlgebra.exe

sort:
	g++ -O3 -std=c++20 LinearAlgebra.cpp sort.cpp -pthread -fopenmp -o sort.exe

test:
	g++ -I/home/jwsv61099/workspace/libraries/googletest/googletest/include/ -L/home/jwsv61099/workspace/libraries/googletest/build/lib LinearAlgebra.cpp test_linalg.cpp -lgtest -o test_linalg
# linAlg:
# 	g++ -o LinearAlgebra.o -c LinearAlgebra.cpp
# 	g++ -o main.o -c main.cpp
# 	g++ *.o -o LinAlg.exe