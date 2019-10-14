all: library/fileIO.cpp library/library.cpp src/Model_A_Library.cpp includes_usr/constants.h includes_usr/datastructures.h includes_usr/fileIO.h includes_usr/library.h
	 g++ -std=c++11 -g -Wall -o myexe library/fileIO.cpp library/library.cpp src/Model_A_Library.cpp includes_usr/constants.h includes_usr/datastructures.h includes_usr/fileIO.h includes_usr/library.h

 clean:
	 rm -f myexe *.o
