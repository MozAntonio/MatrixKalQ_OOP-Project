/* Vect.cpp */
#include "Vect.h"
#include <stdexcept>


//Costruttore di default
Vect::Vect(unsigned int n1, unsigned int n2): RectMatrix(n1, n2) {
	if(n1!=1 && n2!=1)
		throw std::invalid_argument("un vettore deve avere almeno una delle due dimensioni pari a '1'"); //dimensioni non valide
}

//Costruttore a 3 param
// crea un vettore verticale lungo n1 o un vettore orizzontale lungo n2
// imposta tutti gli elem a init
Vect::Vect(unsigned int n1, unsigned int n2, double init): RectMatrix(n1, n2, init) {
	if(n1!=1 && n2!=1)
		throw std::invalid_argument("un vettore deve avere almeno una delle due dimensioni pari a '1'"); //dimensioni non valide
}

unsigned int Vect::rank() const {
	unsigned int rank = 0;
	for(unsigned int i=0; i<numElem() && rank==0; ++i) 
		if(at(i) != 0)
			rank = 1;
	
	return rank;
}

void Vect::swapElem(unsigned int e1, unsigned int e2) {
	double temp = at(e1);
	at(e1) = at(e2);
	at(e2) = temp;
}

unsigned int Vect::numElem() const {
	if(numCols() == 1) //è verticale
		return numRows();
	else //è orizzontale
		return numCols();
}
