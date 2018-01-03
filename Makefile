all: clean Antenna.o main.o Genetic.o compile

run:
	./exe best.txt ambiente.txt >test.out

Antenna.o:
	g++ Antenna.cpp -c


Genetic.o:
	g++ Genetic.cpp -c

main.o:
	g++ main.cpp -c


compile:
	g++ main.o Antenna.o Genetic.o -o exe

plot:
	python plot.py test.out ambiente.txt best.txt


clean:
	find -name '*.o' | xargs rm -rf {}
	find -name '*.zip' | xargs rm -rf {}
	find -name '.*.swp' | xargs rm -rf {}
	
zip:
	zip -r TRABALHO_EVOLUTIVOS main.cpp plot.py Antenna.cpp Antenna.h Genetic.cpp Genetic.h Makefile	

