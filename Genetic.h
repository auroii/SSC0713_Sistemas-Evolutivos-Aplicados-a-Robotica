#ifndef GENETIC_H
#define GENETIC_H

#include "Antenna.h"
#include <vector>


class Genetic {
	
	public:
		Population *best; //populacao melhor de todas
		int size; // tamanho da populacao
		std::vector<Population *> cell;// vector de populacoes
			
		Genetic(int size, int pop); //costrutor; @pop eh o numero de antenas em cada populacao
		~Genetic(); //destrutor

		void evolve(Environment *en); //evolui todo o sistema com elitismo
		void display(Environment *en);//mostra o fitness da melhor populacao de todas e a media de @cell
			
};




#endif
