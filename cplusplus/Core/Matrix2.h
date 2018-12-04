/* Matrix2.h */
#ifndef Matrix2_H
#define Matrix2_H

#include "SquareMatrix.h"


class Matrix2: public SquareMatrix {
	public:
	//Costruttori:
		Matrix2();
		explicit Matrix2(double);
		//virtual ~Matrix2();
		
	//Override:
		virtual Matrix2* clone() const;
		virtual Matrix2* sum_p(const MatrixBase*) const;
		virtual Matrix2* dif_p(const MatrixBase*) const;
		virtual Matrix2* sProd_p(double) const;
		virtual Matrix2* trans_p() const;
		virtual Matrix2* prod_p(const SquareMatrix*) const;
		virtual Matrix2* exp_p(unsigned int) const;
		virtual Matrix2* inv_p() const;
		virtual Matrix2* adj_p() const;
		virtual double det() const; //determinante
		virtual double trace() const; //traccia
		
	//Metodi ridefiniti:
		Matrix2 operator-() const; //-A
		Matrix2 operator*(double) const; //A*s
		Matrix2 trans() const; //trasposta
		Matrix2 exp(unsigned int) const; //A^x
		Matrix2 inv() const; //A^-1
		Matrix2 adjoint() const; //aggiunta
		
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
	
}; //fine Matrix2

//Funzioni esterne:
Matrix2 operator+(const Matrix2&, const Matrix2&); //A+B
Matrix2 operator-(const Matrix2&, const Matrix2&); //A-B
Matrix2 operator*(const Matrix2&, const Matrix2&); //A*B
Matrix2 operator*(double, const Matrix2&); //s*A


#endif