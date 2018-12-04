/* Matrix3.cpp */
#include "Matrix3.h"
#include <stdexcept>


//Costruttore di default
Matrix3::Matrix3(): SquareMatrix(3) {}

//Costruttore a 1 param
// crea una matrice quadrata con dim 3x3
// imposta tutti gli elem a init
Matrix3::Matrix3(double init): SquareMatrix(3, init) {}

Matrix3* Matrix3::clone() const {
	return new Matrix3(*this);
}

Matrix3* Matrix3::sum_p(const MatrixBase* m) const {
	const Matrix3* q = dynamic_cast<const Matrix3*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad una matrice 3x3 solo una matrice 3x3");
	
	return new Matrix3(*this + *q);
}

Matrix3* Matrix3::dif_p(const MatrixBase* m) const {
	const Matrix3* q = dynamic_cast<const Matrix3*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad una matrice 3x3 solo una matrice 3x3");
	
	return new Matrix3(*this - *q);
}

Matrix3* Matrix3::sProd_p(double scalar) const {
	return new Matrix3((*this) * scalar);
}

Matrix3* Matrix3::trans_p() const {
	return new Matrix3(trans()); //cioè: (*this).trans(); o this->trans();
}

Matrix3* Matrix3::prod_p(const SquareMatrix* m) const {
	const Matrix3* q = dynamic_cast<const Matrix3*>(m);
	
	if(!q) //sono permessi prodotti solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile moltiplicare una matrice 3x3 solo con una matrice 3x3");
	
	return new Matrix3((*this) * (*q));
}

Matrix3* Matrix3::exp_p(unsigned int pot) const {
	return new Matrix3(exp(pot)); //cioè: (*this).exp(pot); o this->exp(pot);
}

Matrix3* Matrix3::inv_p() const {
	return new Matrix3(inv()); //cioè: (*this).inv; o this->inv;
}

Matrix3* Matrix3::adj_p() const {
	return new Matrix3(adjoint()); //cioè: (*this).adjoint(); o this->adjoint();
}

double Matrix3::det() const { //Sarrus
	return ((at(0,0)*at(1,1)*at(2,2)+at(0,1)*at(1,2)*at(2,0)+at(0,2)*at(1,0)*at(2,1)) - (at(2,0)*at(1,1)*at(0,2)+at(2,1)*at(1,2)*at(0,0)+at(2,2)*at(1,0)*at(0,1)));
}

double Matrix3::trace() const {
	return at(0,0) + at(1,1) + at(2,2);
}

Matrix3 Matrix3::operator-() const {
	return ((*this)*(-1));
}

Matrix3 Matrix3::operator*(double scalar) const {
	Matrix3 aux = Matrix3();
	for(unsigned int i=0; i<3; ++i)
		for(unsigned int j=0; j<3; ++j)
			aux.at(i,j) = at(i,j) * scalar;
	
	return aux;
}

Matrix3 Matrix3::trans() const {
	Matrix3 aux = Matrix3();
	aux.at(0,0) = at(0,0);
	aux.at(1,1) = at(1,1);
	aux.at(2,2) = at(2,2);
	aux.at(1,0) = at(0,1);
	aux.at(2,1) = at(1,2);
	aux.at(0,1) = at(1,0);
	aux.at(1,2) = at(2,1);
	aux.at(2,0) = at(0,2);
	aux.at(0,2) = at(2,0);
	return aux;
}

Matrix3 Matrix3::exp(unsigned int pot) const {
	Matrix3 aux;
	if(pot==0)
		aux.setIdentity();
	else
		aux = *this;
	
	for(unsigned int i=1; i<pot; ++i)
		aux = aux * (*this);
	
	return aux;
}

Matrix3 Matrix3::inv() const {
	if(!isInvertible())
		throw std::domain_error("matrice non invertibile");
	
	Matrix3 aux = Matrix3();
	Matrix3 adj = adjoint();
	
	//Uso la formula: "inverse(A) = adjoint(A) / det(A)"
	for(unsigned int i=0; i<3; ++i)
		for(unsigned int j=0; j<3; ++j)
			aux.at(i,j) = adj.at(i,j) / det();
	
	return aux;
}

Matrix3 Matrix3::adjoint() const {
	Matrix3 aux = Matrix3();
	
	//Utilizzando la formula: "cof_i,j = (-1)^(i+j) * det(A_i,j)"
	//Dove "det(A_i,j)" è il determinante della sotto-matrice ottenuta eliminando la i-esima riga e la j-esima colonna dalla matrice A

//	IDEA:
//	cof_0,0 = (-1)^0 * det(A_0,0);	//det(A_0,0) = (at(1,1)*at(2,2)) - (at(2,1)*at(1,2));
//	cof_0,1 = (-1)^1 * det(A_0,1);	//det(A_0,1) = (at(1,0)*at(2,2)) - (at(2,0)*at(1,2));
//	cof_0,2 = (-1)^2 * det(A_0,2);	//det(A_0,2) = (at(1,0)*at(2,1)) - (at(2,0)*at(1,1));
//	cof_1,0 = (-1)^1 * det(A_1,0);	//det(A_1,0) = (at(0,1)*at(2,2)) - (at(2,1)*at(0,2));
//	cof_1,1 = (-1)^2 * det(A_1,1);	//det(A_1,1) = (at(0,0)*at(2,2)) - (at(2,0)*at(0,2));
//	cof_1,2 = (-1)^3 * det(A_1,2);	//det(A_1,2) = (at(0,0)*at(2,1)) - (at(2,0)*at(0,1));
//	cof_2,0 = (-1)^2 * det(A_2,0);	//det(A_2,0) = (at(0,1)*at(1,2)) - (at(1,1)*at(0,2));
//	cof_2,1 = (-1)^3 * det(A_2,1);	//det(A_2,1) = (at(0,0)*at(1,2)) - (at(1,0)*at(0,2));
//	cof_2,2 = (-1)^4 * det(A_2,2);	//det(A_2,2) = (at(0,0)*at(1,1)) - (at(1,0)*at(0,1));
	
//	cof_A =	{ {cof_0,0 , cof_0,1 , cof_0,2},
//			  {cof_1,0 , cof_1,1 , cof_1,2},
//			  {cof_2,0 , cof_2,1 , cof_2,2} };
//	return cof_A.trans();
	
	aux.at(0,0) = (at(1,1)*at(2,2)) - (at(2,1)*at(1,2));
	aux.at(1,1) = (at(0,0)*at(2,2)) - (at(2,0)*at(0,2));
	aux.at(2,2) = (at(0,0)*at(1,1)) - (at(1,0)*at(0,1));
	aux.at(1,0) = -((at(1,0)*at(2,2)) - (at(2,0)*at(1,2)));
	aux.at(2,1) = -((at(0,0)*at(2,1)) - (at(2,0)*at(0,1)));
	aux.at(0,1) = -((at(0,1)*at(2,2)) - (at(2,1)*at(0,2)));
	aux.at(1,2) = -((at(0,0)*at(1,2)) - (at(1,0)*at(0,2)));
	aux.at(2,0) = (at(1,0)*at(2,1)) - (at(2,0)*at(1,1));
	aux.at(0,2) = (at(0,1)*at(1,2)) - (at(1,1)*at(0,2));
	return aux;
}


//Funzioni esterne:

Matrix3 operator+(const Matrix3& m1, const Matrix3& m2) {
	Matrix3 aux = Matrix3();
	for(unsigned int i=0; i<3; ++i)
		for(unsigned int j=0; j<3; ++j)
			aux.at(i,j) = m1.at(i,j) + m2.at(i,j);
	
	return aux;
}

Matrix3 operator-(const Matrix3& m1, const Matrix3& m2) {
	return (m1 + (-m2));
}

Matrix3 operator*(const Matrix3& m1, const Matrix3& m2) {
	Matrix3 aux = Matrix3(0);
	
	for(unsigned int i=0; i<3; ++i)
		for(unsigned int j=0; j<3; ++j)
			for(unsigned int k=0; k<3; ++k)
				aux.at(i,j) = aux.at(i,j) + (m1.at(i,k) * m2.at(k,j));
	
	return aux;
}

Matrix3 operator*(double scalar, const Matrix3& m) {
	return m*scalar;
}
