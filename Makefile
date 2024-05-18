all: agenda

agenda: 
	g++ agenda.cpp main.cpp

clean:
	rm -f agenda*.o