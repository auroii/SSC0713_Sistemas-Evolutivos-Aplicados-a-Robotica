#ifndef ANTENNA_H
#define ANTENNA_H

#define MAX_ENERGY 50 //energia maxima de uma antena
#define DIM 200 //dimensao da matriz ambiente
#define TMUT 0.25 //taxa de mutacao
#include <vector>
#include <cstdio>


//cabecalho de classes
class Population; 
class Antenna;
class Environment;

//modelo de antena
class Antenna {
	
	private:
		int p_x, p_y; //posicoes da antena na matriz ambiente
		double energy;; //energia da antena

	public:
		//construtores
		Antenna(int x, int y, double e);

		
		void setX(int x); //seta a coordenada X da antena
		void setY(int y); //seta a coordenada Y da antena
		void setEnergy(double e); //seta a energia da antena

		int getX() const; // retorna a coordenada x da antena 
		int getY() const; // retorna a coordenada y da antena
		double getEnergy() const; //retorna a energia da antena
		
		Antenna &operator = (const Antenna& current);
				
  
};

//modelo para o ambiente onde ocorrerah a evolucao

class Environment {
	public:
		char matrix[DIM][DIM]; //matriz de char para salvar os estados do ambiente (tem pessoa, nada, tem antena)
	
		Environment(FILE *fp); //construtor do ambiente
		
		void display(Population *pop); //mostra a matriz ambiente em relacao a uma populacao de antenas no terminal
};



//modelo de populacao de antenas
class Population {

	public:
	int number_of_people;
	int size; //tamanho da populacao
	std::vector<Antenna *> population; //vector que possui os individuos(antenas) da populacao 
	
	double fitness(Environment *en); //funcao fitness que retorna o desempenho de uma populacao de antenas num ambiente	
	
	Population *crossover(Population *current); //funcao que cruza o @this com o @current e retorna numa populacao filha
	
	Population(int size); //construtor
	~Population();//destrutor
	
	Population& operator=(const Population& current);

};



#endif	
