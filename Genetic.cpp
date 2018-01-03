#include "Genetic.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>

//construtor da classe Genetic
Genetic::Genetic(int size, int pop) {
	this->size = size;
	this->cell.resize(size);
	
	this->best = new Population(pop);	
	//loop para alocar cada populacao com a geracao aleatoria de parametros
	for(int i = 0; i < size; ++i) {
		this->cell[i] = new Population(pop);
	}
}

//destrutor
Genetic::~Genetic(void) {
	for(int i = 0; i < size; ++i) {
		delete this->cell[i];
	}
	
	if(this->best != NULL) delete this->best;
}

//evoluir o conjunto de populacoes em relacao a um ambiente
void Genetic::evolve(Environment *en) {
	std::vector<double> temp_fitness(this->size); //vetor auxiliar para evitar recalculo dos fitness
	
	//loop para preencher @temp_fitness
	for(int i = 0; i < this->size; ++i) {
		temp_fitness[i] = this->cell[i]->fitness(en);
	}
	
	//loop para atualizar o melhor de todos
	for(int i = 0; i < this->size; ++i) {
		if(temp_fitness[i] >= this->best->fitness(en)) {
			*(this->best) = *(this->cell[i]);
		}
	}
	
	//loop para fazer o crossover com todas as populacoes com o melhor de todos (elitismo)
	// caso o gerado seja pior que o pai, ele eh morto (predacao)
	for(int i = 0; i < this->size; ++i) {
		Population *current = best->crossover(this->cell[i]);

		if(current->fitness(en) > temp_fitness[i]) {
			*(this->cell[i]) = *current;
		}
		delete current;
		
	}
	/*
	int x = rand()%DIM;
	int y = rand()%DIM;
	int z = rand()%DIM;
	int w = rand()%DIM;
	
	if(temp_fitness[x] < temp_fitness[y]) x = y;
	if(temp_fitness[z] < temp_fitness[w]) z = w;
	
	Population *current = this->cell[x]->crossover(this->cell[z]);
	
	if(temp_fitness[x] > temp_fitness[z]) x = z;
	
	if(current->fitness(en) > temp_fitness[x]) *(this->cell[x]) = *current;
	delete current;*/
}


//funcao para printar na tela o fitness do @best (melhor de todos) junto com o fitness meio do conjunto de populacoes
void Genetic::display(Environment *en) {
	double sum_fitness = 0.0;
	std::vector<double> temp_fitness(this->size);//vector auxiliar para o desvio padrao

	for(int i = 0; i < this->size; ++i) {
		temp_fitness[i] = this->cell[i]->fitness(en);
		sum_fitness += temp_fitness[i];
	}
	
	sum_fitness/=this->size;
	
	/*DESVIO PADRAO*/
	double sigma = 0.0;
	for(int i = 0; i < this->size; ++i) 
		sigma += (temp_fitness[i] - sum_fitness) * (temp_fitness[i] - sum_fitness);
	
	sigma /= (this->size -1);
	
	sigma = sqrt(sigma);
	
	std::cout <<  ((this->best != NULL) ? this->best->fitness(en) : -1) << ' ' << sum_fitness << ' ' << sigma << '\n';
}










