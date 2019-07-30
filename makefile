all: KPSA

KPSA: KPSA.o main.o 
	g++ -ggdb -o KPSA KPSA.o main.o

KPSA.o: KPSA.cpp
	g++ -ggdb -c KPSA.cpp

main.o: main.cpp
	g++ -ggdb -c main.cpp

plot: 
	gnuplot pic.gp

dep:
	echo "Do nothing"

clean:
	rm -f KPSA KPSA *.o

cleanDat:
	rm -f KPSA *.dat
