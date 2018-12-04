/* Matrix3.h */
#ifndef MATRIX3_H
#define MATRIX3_H

#include "SquareMatrix.h"


class Matrix3: public SquareMatrix {
	public:
	//Costruttori:
		Matrix3();
		explicit Matrix3(double);
		//virtual ~Matrix3();
		
	//Override:
		virtual Matrix3* clone() const;
		virtual Matrix3* sum_p(const MatrixBase*) const;
		virtual Matrix3* dif_p(const MatrixBase*) const;
		virtual Matrix3* sProd_p(double) const;
		virtual Matrix3* trans_p() const;
		virtual Matrix3* prod_p(const SquareMatrix*) const;
		virtual Matrix3* exp_p(unsigned int) const;
		virtual Matrix3* inv_p() const;
		virtual Matrix3* adj_p() const;
		virtual double det() const; //determinante
		virtual double trace() const; //traccia
		
	//Metodi ridefiniti:
		Matrix3 operator-() const; //-A
		Matrix3 operator*(double) const; //A*s
		Matrix3 trans() const; //trasposta
		Matrix3 exp(unsigned int) const; //A^x
		Matrix3 inv() const; //A^-1
		Matrix3 adjoint() const; //aggiunta
		
	//Metodi ereditati:
		//	unsigned int numRows() const;
		//	unsigned int numCols() const;
		
		//	virtual double& at(unsigned int, unsigned int);
		//	virtual const double& at(unsigned int, unsigned int) const;
		//	virtual void swapRows(unsigned int, unsigned int, unsigned int =0);
		//	virtual void swapCols(unsigned int, unsigned int, unsigned int =0);
		//	virtual void print(ostream&, string ="\t") const;
		//	virtual void load(istream&);
		//	virtual unsigned int rank() const;
		//	void fill(double);
		//	void setRandInt(int =0, int =100);
		//	void setRandReal(double =0, double =100);
		
		//	virtual bool isInvertible() const;
		//	void setIdentity();
		
	//Eccezioni:
		//	out_of_range: at(..), swapRows(..), swapCols(..)
		
		//	domain_error: inv(), inv_p(..)
		//	invalid_argument: sum_p(..), dif_p(..), prod_p(..)
	
}; //fine Matrix3

//Funzioni esterne:
Matrix3 operator+(const Matrix3&, const Matrix3&); //A+B
Matrix3 operator-(const Matrix3&, const Matrix3&); //A-B
Matrix3 operator*(const Matrix3&, const Matrix3&); //A*B
Matrix3 operator*(double, const Matrix3&); //s*A


#endif