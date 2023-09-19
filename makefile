askisi3: main.o classes.o
	g++ main.o classes.o -o askisi3

main.o: main.cpp
	g++ -c main.cpp

classes.o: classes.cpp classes.h
	g++ -c classes.cpp
clean:

	rm *.o askisi3
