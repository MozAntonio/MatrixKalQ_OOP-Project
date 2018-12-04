/* VectVert.cpp */
#include "VectVert.h"
#include <stdexcept>


//Metodi interni:

//Costruttore di default
VectVert::VectVert(unsigned int n): Vect(n, 1) {}

//Costruttore a 2 param
// crea un vettore verticale lungo n
// imposta tutti gli elem a init
VectVert::VectVert(unsigned int n, double init): Vect(n, 1, init) {}

VectVert* VectVert::clone() const {
	return new VectVert(*this);
}

VectVert* VectVert::sum_p(const MatrixBase* m) const {
	const VectVert* q = dynamic_cast<const VectVert*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad un vettore verticale solo un vettore verticale");
	
	return new VectVert(*this + *q);
}

VectVert* VectVert::dif_p(const MatrixBase* m) const {
	const VectVert* q = dynamic_cast<const VectVert*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad un vettore verticale solo un vettore verticale");
	
	return new VectVert(*this - *q);
}

VectVert* VectVert::sProd_p(double scalar) const {
	return new VectVert((*this) * scalar);
}

VectVert* VectVert::rev_p() const {
	return new VectVert(rev()); //cioè: (*this).rev(); o this->rev();
}

Vect* VectVert::trans_p() const {
	//un VectVert trasposto è un VectHor
	//non posso tornare VectHor* perchè violerei le regole della covarianza
	return new VectHor(trans()); //cioè: (*this).trans(); o this->trans();
}

double& VectVert::at(unsigned int i) {
	return Vect::at(i,0);
}

const double& VectVert::at(unsigned int i) const {
	return Vect::at(i,0);
}

VectVert VectVert::operator-() const {
	return ((*this)*(-1));
}

VectVert VectVert::operator*(double scalar) const {
	VectVert aux = VectVert(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
			aux.at(i) = at(i) * scalar;
	
	return aux;
}

VectHor VectVert::trans() const {
	VectHor aux = VectHor(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
			aux.at(i) = at(i);
	
	return aux;
}

VectVert VectVert::rev() const {
	VectVert aux = VectVert(numElem());
	for(unsigned int i=0; i<numElem(); ++i)
		aux.at(i) = at(numElem()-i-1);
	
	return aux;
}


//Funzioni esterne:

VectVert operator+(const VectVert& v1, const VectVert& v2) {
	if(v1.numElem() != v2.numElem())
		throw std::invalid_argument("la somma è permessa solo tra vettori della stessa lunghezza"); //dimensioni non compatibili
	
	unsigned int e=v1.numElem(); //o: e=v2.numElem();
	VectVert aux = VectVert(e);
	for(unsigned int i=0; i<e; ++i)
		aux.at(i) = v1.at(i) + v2.at(i);
	
	return aux;
}

VectVert operator-(const VectVert& v1, const VectVert& v2) {
	return (v1 + (-v2));
}

VectVert operator*(double scalar, const VectVert& v) {
	return v*scalar;
}
