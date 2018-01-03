#include "Antenna.h"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <set>
#include <cstdio>

//construtor da antena 
Antenna::Antenna(int x, int y, double e) { 	
	setX(x);
	setY(y);
	setEnergy(e);
}

//seta a coordenada X da antena
void Antenna::setX(int x) {
	p_x = x;
}

//seta a coordenada Y da antena
void Antenna::setY(int y) {
	p_y = y;;
}

//seta a energia da antena
void Antenna::setEnergy(double e) {
	energy = e;
}

int Antenna::getX() const { return p_x; } // retorna a coordenada x da antena 
int Antenna::getY() const { return p_y; } // retorna a coordenada y da antena
double Antenna::getEnergy() const { return energy; } //retorna a energia da antena

// overload para atribuicao em antenas
//para ponteiro, uilzar *a = *b(a e b ponteiros para antenas)
// *****nao copia o endereco, apenas os dados
Antenna& Antenna::operator=(const Antenna& current) {
	this->setX(current.getX());
	this->setY(current.getY());
	this->setEnergy(current.getEnergy());
	
	return *this;
}

//overload para atribuicao em populacoes
// para ponteiro utilizar *a = *b (a e b ponteiros para populacoes)
// *****nao copia o endereco, apenas os dados
Population& Population::operator=(const Population& current) {
	this->size = current.size;
	this->population.resize(this->size);
	
	
	for(int i = 0; i < this->size; ++i) {
		*(this->population[i]) = *(current.population[i]);
	}
	
	return *this;
}	
	


//construtor do ambiente
Environment::Environment(FILE *fp) {
	for(int i = 0; i < DIM; ++i)
		for(int j = 0; j < DIM; ++j) {
			char ch;
			fscanf(fp, "%c", &ch);
			if(ch == '\n') { continue; }
			this->matrix[i][j] = ch;
		}
}


//mostra a matriz do ambiente com relacao a uma determinada populacao
void Environment::display(Population *pop) {
	std::set<std::pair<int, int> > coords; //set auxiliar para printar as antenas
	
	//loop para aquisicao das coordenadas
	for(int i = 0; i < pop->size; ++i) {
		int x = pop->population[i]->getX();	
		int y = pop->population[i]->getY();
		
		coords.insert(std::make_pair(x, y));
	}
	//loop para printar as matrizes
	for(int i = 0; i < DIM; ++i) {
		for(int j = 0; j < DIM; ++j) {
			if(coords.count(std::make_pair(i ,j))) std::cout << 'T' << ' ';
			else if(this->matrix[i][j] == 'p') std::cout << 'p' << ' ';
			else std::cout << "  ";
		}
		std::cout << '\n';
	}
}



//construtor da populacao
Population::Population(int size) {
	this->size = size; //seta o tamanho da populacao
	this->number_of_people = 0;
	this->population.resize(size); //define o tamanho da populacao
			
	
	for(int i = 0; i < size; ++i) 
		this->population[i] = new Antenna(rand()%DIM, rand()%DIM, rand()%MAX_ENERGY); //gera um antena aleatoria e insere a populacao

}


//destrutor da populacao de antenas
Population::~Population() {
	for(int i = 0; i < this->population.size(); ++i) delete this->population[i];
}



//funcao auxiliar para verificar se a coordenada (i, h) eh alcancavel pela antena @an
bool inside(Antenna *an, int i, int j) {
	int x = an->getX();
	int y = an->getY();
	double e = an->getEnergy();
	
	return ((x-i)*(x-i) + (y-j)*(y-j) <= e*e);
}

//funcao fitness que retorna o desempenho da populacao
double Population::fitness(Environment *en) {
	double total_energy = 0.0; //energia total, inicialmente igual a 1, pois sera usado media geometrica
	int people = 0;//o numero de pessoas que cada antena consegue alcancar
						// mesmo alcance em O(lg n) per query	

	for(int i = 0; i < this->size; ++i) {
		total_energy += this->population[i]->getEnergy(); //adiciono a energia da antena 
	}

	total_energy /= this->size; // divido pelo numero de elementos e a media aritmetica esta pronta
	
	std::set<std::pair<int, int> > temp;
	
	//loop na matriz ambiente para cada antena
	for(int k = 0; k < this->size; ++k)
		for(int i = 0; i < DIM; ++i) 
			for(int j = 0; j < DIM; ++j) {
				//se a antena alcanca uma pessoa, incremente @people
				std::pair<int, int> p(i, j);
				if(!temp.count(p) && en->matrix[i][j] == 'p' && inside(this->population[k], i, j)) {
					people++;
					temp.insert(p);
				}
					
			}
	this->number_of_people = people;
		
	return (people - total_energy*total_energy); //retorna a media final
}

//funcao que cruza @this com @current gerando um populacao filha
Population *Population::crossover(Population *current) {
	Population *new_pop = new Population(current->size); //this->size == current-size sempre
	
	//loop nas antenas de @this e @current
	for(int i = 0; i < this->size; ++i) {
		int x_m = (current->population[i]->getX() + this->population[i]->getX())/2; //coordenada media de x
		int y_m = (current->population[i]->getY() + this->population[i]->getY())/2;;//coordenada media de y
		double energy_m = (current->population[i]->getEnergy() + current->population[i]->getEnergy())/2.0; // energia media 
			
		/*MUTACAO*/

		x_m = ((double) rand()/RAND_MAX <= TMUT) ? x_m + pow(-1, rand()%2) : x_m; // somo/subtraio 1	

		y_m = ((double) rand()/RAND_MAX <= TMUT) ? y_m + pow(-1, rand()%2) : y_m; // somo/subtario 1

		//sumo/subtraio TMUT% da energia media 	
		energy_m = ((double) rand()/RAND_MAX <= TMUT ) ? energy_m + pow(-1, rand()%2) * TMUT * energy_m : energy_m;
 
		new_pop->population.push_back(new Antenna(x_m, y_m, energy_m)); //insiro a antena media na nova populacao
	}

	return new_pop; //retorna a nova populacao
}



		
	
	
















