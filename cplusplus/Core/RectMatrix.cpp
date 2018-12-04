/* RectMatrix.cpp */
#include "RectMatrix.h"
#include <stdexcept>


//Metodi interni:

//Costruttore di default
RectMatrix::RectMatrix(unsigned int r, unsigned int c): DenseMatrix(r, c) {
	if(r==c && r!=0) //non si può fare una matrice nxm con n==m a meno che n==m==0
		throw std::invalid_argument("una matrice rettangolare deve avere un numero diverso di righe e colonne"); //dimensioni non valide
}

//Costruttore a 3 param
// crea una matrice con dim rows x cols
// imposta tutti gli elem a init
RectMatrix::RectMatrix(unsigned int r, unsigned int c, double init): DenseMatrix(r, c, init) {
	if(r==c && r!=0) //non si può fare una matrice nxm con n==m a meno che n==m==0
		throw std::invalid_argument("una matrice rettangolare deve avere un numero diverso di righe e colonne"); //dimensioni non valide
}

RectMatrix* RectMatrix::clone() const {
	return new RectMatrix(*this);
}

RectMatrix* RectMatrix::sum_p(const MatrixBase* m) const {
	const RectMatrix* q = dynamic_cast<const RectMatrix*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad una matrice rettangolare solo una matrice rettangolare");
	
	return new RectMatrix(*this + *q);
}

RectMatrix* RectMatrix::dif_p(const MatrixBase* m) const {
	const RectMatrix* q = dynamic_cast<const RectMatrix*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad una matrice rettangolare solo una matrice rettangolare");
	
	return new RectMatrix(*this - *q);
}

RectMatrix* RectMatrix::sProd_p(double scalar) const {
	return new RectMatrix((*this) * scalar);
}

RectMatrix* RectMatrix::trans_p() const {
	return new RectMatrix(trans()); //cioè: (*this).trans(); o this->trans();
}

RectMatrix RectMatrix::operator-() const {
	return ((*this)*(-1));
}

RectMatrix RectMatrix::operator*(double scalar) const {
	RectMatrix aux = RectMatrix(numRows(), numCols());
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j)
			aux.at(i,j) = at(i,j) * scalar;
	
	return aux;
}

RectMatrix RectMatrix::trans() const {
	RectMatrix aux = RectMatrix(numCols(), numRows(), 0);
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j)
			aux.at(j,i) = at(i,j);
	
	return aux;
}


//Funzioni esterne:

RectMatrix operator+(const RectMatrix& m1, const RectMatrix& m2) {
	if(!(m1.numRows()==m2.numRows() && m1.numCols()==m2.numCols()))
		throw std::invalid_argument("la somma è permessa solo tra matrici rettangolari delle stesse dimensioni"); //dimensioni non compatibili
	
	unsigned int r=m1.numRows(), c=m1.numCols(); //o: r=m2.numRows(), c=m2.numCols();
	
	RectMatrix aux = RectMatrix(r,c);
	
	for(unsigned int i=0; i<r; ++i)
		for(unsigned int j=0; j<c; ++j)
			aux.at(i,j) = m1.at(i,j) + m2.at(i,j);
	
	return aux;
}

RectMatrix operator-(const RectMatrix& m1, const RectMatrix& m2) {
	return (m1 + (-m2));
}

RectMatrix operator*(double scalar, const RectMatrix& m) {
	return m*scalar;
}

