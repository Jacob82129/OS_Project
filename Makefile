project: main.o sdisk.o filesys.o block.o table.o
	c++ -o project main.o sdisk.o filesys.o block.o table.o

sdisk.o: sdisk.cpp sdisk.h
	c++ -c sdisk.cpp

filesys.o: filesys.cpp filesys.h
	c++ -c filesys.cpp

block.o: block.cpp block.h
	c++ -c block.cpp

table.o: table.cpp table.h
	c++ -c table.cpp	
	
main.o: main.cpp
	c++ -c main.cpp

clean:
	rm *.o