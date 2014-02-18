FLAGS= -Wall -pedantic -g

test: compConexas ejAdicionales
	./compConexas 23A.pnm
	./ejAdicionales 23A.pnm 23A 81 161

compConexas: compConexas.cc mfset.o imagen.o
	g++ -o compConexas compConexas.cc mfset.o imagen.o $(FLAGS)

ejAdicionales: ejAdicionales.cc mfset.o imagen.o
	g++ -o ejAdicionales ejAdicionales.cc mfset.o imagen.o $(FLAGS)

mfset.o: mfset.h mfset.cc imagen.h 
	g++ -c mfset.cc $(FLAGS)

imagen.o : imagen.h imagen.cc
	g++ -c imagen.cc $(FLAGS)

clean :
	rm -f *~ *.o compConexas ejAdicionales 23A_*.pnm

