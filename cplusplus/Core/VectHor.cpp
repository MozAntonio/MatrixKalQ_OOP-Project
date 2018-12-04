/* VectHor.cpp */
#include "VectHor.h"
#include <stdexcept>


//Metodi interni:

//Costruttore di default
VectHor::VectHor(unsigned int n): Vect(1, n) {}

//Costruttore a 2 param
// crea un vettore orizzontale lungo n
// imposta tutti gli elem a init
VectHor::VectHor(unsigned int n, double init): Vect(1, n, init) {}

VectHor* VectHor::clone() const {
	return new VectHor(*this);
}

VectHor* VectHor::sum_p(const MatrixBase* m) const {
	const VectHor* q = dynamic_cast<const VectHor*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad un vettore orizzontale solo un vettore orizzontale");
	
	return new VectHor(*this + *q);
}

VectHor* VectHor::dif_p(const MatrixBase* m) const {
	const VectHor* q = dynamic_cast<const VectHor*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad un vettore orizzontale solo un vettore orizzontale");
	
	return new VectHor(*this - *q);
}

VectHor* VectHor::sProd_p(double scalar) const {
	return new VectHor((*this) * scalar);
}

VectHor* VectHor::rev_p() const {
	return new VectHor(rev()); //cioè: (*this).rev(); o this->rev();
}

Vect* VectHor::trans_p() const {
	//un VectHor trasposto è un VectVert
	//non posso tornare VectVert* perchè violerei le regole della covarianza
	return new VectVert(trans()); //cioè: (*this).trans(); o this->trans();
}

double& VectHor::at(unsigned int i) {
	return Vect::at(0,i);
}

const double& VectHor::at(unsigned int i) const {
	return Vect::at(0,i);
}

VectHor VectHor::operator-() const {
	return ((*this)*(-1));
}

VectHor VectHor::operator*(double scalar) const {
	VectHor aux = VectHor(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
			aux.at(i) = at(i) * scalar;
	
	return aux;
}

VectVert VectHor::trans() const {
	VectVert aux = VectVert(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
			aux.at(i) = at(i);
	
	return aux;
}

VectHor VectHor::rev() const {
	VectHor aux = VectHor(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
		aux.at(i) = at(numElem()-i-1);
	
	return aux;
}


//Funzioni esterne:

VectHor operator+(const VectHor& v1, const VectHor& v2) {
	if(v1.numElem() != v2.numElem())
		throw std::invalid_argument("la somma è permessa solo tra vettori della stessa lunghezza"); //dimensioni non compatibili
	
	unsigned int e=v1.numElem(); //o: e=v2.numElem();
	VectHor aux = VectHor(e);
	for(unsigned int i=0; i<e; ++i)
		aux.at(i) = v1.at(i) + v2.at(i);
	
	return aux;
}

VectHor operator-(const VectHor& v1, const VectHor& v2) {
	return (v1 + (-v2));
}

VectHor operator*(double scalar, const VectHor& v) {
	return v*scalar;
}
