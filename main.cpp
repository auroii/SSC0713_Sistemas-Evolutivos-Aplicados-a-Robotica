/*Autores: Auro Martins Soares Junior, 9791201
	   Gisela Moreira Ortt, 8937761


*/	


#include "Antenna.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Genetic.h"
#include <fstream>

#define nPop 10
#define nAntenna 5
#define FILENAME_BEST 1
#define FILENAME_EN 2

//main
int main(int argc, char *argv[]) {
	
	srand(time(NULL)); //atualizo a semente de numeros aleatorio com o tempo do computador
	FILE* arq = fopen( "primeiro.txt", "r+" );	
	Genetic *ag = new Genetic(nPop, nAntenna); //inicializo a classe Genetic
	Environment *en = new Environment(arq); //inicializo a classe ambiente
	fclose(arq);
	
	int r = 50; //defino o numero de rodadas que o ag ira evoluir
	
	//loop para evolucao e geracao do grafico
	while(r--) {
		ag->evolve(en);
		ag->display(en); 
	}
	//Colocar os dados do melhor de todos no arquivo argv[FILENAME_BEST]
	// e a matriz ambiente (0 se nao ha pessoa e 1 se ha) no arquivo argv[FILENAME_EN]
	
	std::ofstream data_best;
	std::ofstream data_en;

	data_best.open(argv[FILENAME_BEST]);
	data_en.open(argv[FILENAME_EN]);

	for(int i = 0; i < nAntenna; ++i) {
		data_best << ag->best->population[i]->getX() << ' ' << ag->best->population[i]->getY();
		data_best << ' ' << ag->best->population[i]->getEnergy() << '\n';
	}
	
	for(int i = 0; i < DIM; ++i) {
		for(int j = 0; j < DIM; ++j){
			if(en->matrix[i][j] == 'p') 
				data_en << 1;
			else data_en << 0;
			if(j != DIM-1) data_en << ' ';
		}
		data_en << '\n';
	}	
	
		
	data_en.close();	
	data_best.close();
	
	
	//en->display(ag->best);
//	std::cout << ag->best->number_of_people << '\n';	
	
	delete ag; //apago a memoria
	delete en;

	return (EXIT_SUCCESS); 
}	


