/* Matrix2.cpp */
#include "Matrix2.h"
#include <stdexcept>


//Costruttore di default
Matrix2::Matrix2(): SquareMatrix(2) {}

//Costruttore a 1 param
// crea una matrice quadrata 2x2
// imposta tutti gli elem a init
Matrix2::Matrix2(double init): SquareMatrix(2, init) {}

Matrix2* Matrix2::clone() const {
	return new Matrix2(*this);
}

Matrix2* Matrix2::sum_p(const MatrixBase* m) const {
	const Matrix2* q = dynamic_cast<const Matrix2*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad una matrice 2x2 solo una matrice 2x2");
	
	return new Matrix2(*this + *q);
}

Matrix2* Matrix2::dif_p(const MatrixBase* m) const {
	const Matrix2* q = dynamic_cast<const Matrix2*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad una matrice 2x2 solo una matrice 2x2");
	
	return new Matrix2(*this - *q);
}

Matrix2* Matrix2::sProd_p(double scalar) const {
	return new Matrix2((*this) * scalar);
}

Matrix2* Matrix2::trans_p() const {
	return new Matrix2(trans()); //cioè: (*this).trans(); o this->trans();
}

Matrix2* Matrix2::prod_p(const SquareMatrix* m) const {
	const Matrix2* q = dynamic_cast<const Matrix2*>(m);
	
	if(!q) //sono permessi prodotti solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile moltiplicare una matrice 2x2 solo con una matrice 2x2");
	
	return new Matrix2((*this) * (*q));
}

Matrix2* Matrix2::exp_p(unsigned int pot) const {
	return new Matrix2(exp(pot)); //cioè: (*this).exp(pot); o this->exp(pot);
}

Matrix2* Matrix2::inv_p() const {
	return new Matrix2(inv()); //cioè: (*this).inv; o this->inv;
}

Matrix2* Matrix2::adj_p() const {
	return new Matrix2(adjoint()); //cioè: (*this).adjoint(); o this->adjoint();
}

double Matrix2::det() const {
	return (at(0,0)*at(1,1) - at(0,1)*at(1,0));
}

double Matrix2::trace() const {
	return at(0,0) + at(1,1);
}

Matrix2 Matrix2::operator-() const {
	return ((*this)*(-1));
}

Matrix2 Matrix2::operator*(double scalar) const {
	Matrix2 aux = Matrix2();
	aux.at(0,0) = at(0,0) * scalar;
	aux.at(0,1) = at(0,1) * scalar;
	aux.at(1,0) = at(1,0) * scalar;
	aux.at(1,1) = at(1,1) * scalar;
	return aux;
}

Matrix2 Matrix2::trans() const {
	Matrix2 aux = Matrix2();
	aux.at(0,0) = at(0,0);
	aux.at(1,1) = at(1,1);
	aux.at(0,1) = at(1,0);
	aux.at(1,0) = at(0,1);
	return aux;
}

Matrix2 Matrix2::exp(unsigned int pot) const {
	Matrix2 aux;
	if(pot==0)
		aux.setIdentity();
	 else
		aux = *this;
	
	for(unsigned int i=1; i<pot; ++i)
		aux = aux * (*this);
	
	return aux;
}

Matrix2 Matrix2::inv() const {
	
	if(!isInvertible())
		throw std::domain_error("matrice non invertibile");
	
	Matrix2 aux = Matrix2();
	
	aux.at(0,1) = (-1) * at(0,1);
	aux.at(1,0) = (-1) * at(1,0);
	
	aux.at(0,0) = at(1,1);
	aux.at(1,1) = at(0,0);
	
	return ((1/det()) * aux);
}

Matrix2 Matrix2::adjoint() const {
	Matrix2 aux = Matrix2();
	
	//Utilizzando la formula: "cof_i,j = (-1)^(i+j) * det(A_i,j)"
	//Dove "det(A_i,j)" è l'elemento ottenuto eliminando la i-esima riga e la j-esima colonna dalla matrice A

//	IDEA:
//	cof_0,0 = (-1)^0 * at(1,1);
//	cof_0,1 = (-1)^1 * at(1,0);
//	cof_1,0 = (-1)^1 * at(0,1);
//	cof_1,1 = (-1)^2 * at(0,0);
	
//	cof_A = {{cof_0,0 , cof_0,1} , {cof_1,0 , cof_1,1}};
//	return cof_A.trans();
	
	aux.at(0,0) = at(1,1);
	aux.at(1,1) = at(0,0);
	aux.at(0,1) = -at(0,1);
	aux.at(1,0) = -at(1,0);
	return aux;
}


//Funzioni esterne:

Matrix2 operator+(const Matrix2& m1, const Matrix2& m2) {
	Matrix2 aux = Matrix2();
	aux.at(0,0) = m1.at(0,0) + m2.at(0,0);
	aux.at(0,1) = m1.at(0,1) + m2.at(0,1);
	aux.at(1,0) = m1.at(1,0) + m2.at(1,0);
	aux.at(1,1) = m1.at(1,1) + m2.at(1,1);
	return aux;
}

Matrix2 operator-(const Matrix2& m1, const Matrix2& m2) {
	return (m1 + (-m2));
}

Matrix2 operator*(const Matrix2& m1, const Matrix2& m2) {
	Matrix2 aux = Matrix2(0);
	
	for(unsigned int i=0; i<2; ++i)
		for(unsigned int j=0; j<2; ++j)
			for(unsigned int k=0; k<2; ++k)
				aux.at(i,j) = aux.at(i,j) + (m1.at(i,k) * m2.at(k,j));
	
	return aux;
}

Matrix2 operator*(double scalar, const Matrix2& m) {
	return m*scalar;
}
