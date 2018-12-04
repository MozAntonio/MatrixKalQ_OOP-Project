/* SquareMatrix.h */
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include "DenseMatrix.h"


class SquareMatrix: public DenseMatrix {
	private:
	//Metodi propri privati:
		SquareMatrix subMatrix(unsigned int, unsigned int, unsigned int =0) const;
		static double calcDet(const SquareMatrix&, unsigned int);
		
	public:
	//Costruttori:
		explicit SquareMatrix(unsigned int =0);
		SquareMatrix(unsigned int, double);
		//virtual ~SquareMatrix();
		
	//Metodi 'concretizzati':
		virtual SquareMatrix* clone() const;
		virtual SquareMatrix* sum_p(const MatrixBase*) const;
		virtual SquareMatrix* dif_p(const MatrixBase*) const;
		virtual SquareMatrix* sProd_p(double) const;
		virtual SquareMatrix* trans_p() const;
		
	//Metodi propri:
		virtual SquareMatrix* prod_p(const SquareMatrix*) const;
		virtual SquareMatrix* exp_p(unsigned int) const;
		virtual SquareMatrix* inv_p() const;
		virtual SquareMatrix* adj_p() const;
		SquareMatrix operator-() const; //-A
		SquareMatrix operator*(double) const; //A*s
		SquareMatrix trans() const; //trasposta
		SquareMatrix exp(unsigned int) const; //A^x
		SquareMatrix inv() const; //A^-1
		SquareMatrix adjoint() const; //aggiunta
		void setIdentity(); //trasforma la matrice in I
		virtual bool isInvertible() const;
		virtual double det() const; //determinante
		virtual double trace() const; //traccia
		
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
		
	//Eccezioni:
		//	out_of_range: at(..), swapRows(..), swapCols(..)
		
		//	domain_error: inv(), inv_p(..)
		//	invalid_argument: operator+(..), operator-(const SquareMatrix&, const SquareMatrix&), operator*(const SquareMatrix&, const SquareMatrix&)
		//	invalid_argument: sum_p(..), dif_p(..), prod_p(..)
		//	out_of_range: (priv)calcDet(..)
		
}; //fine SquareMatrix

//Funzioni esterne:
SquareMatrix operator+(const SquareMatrix&, const SquareMatrix&); //A+B
SquareMatrix operator-(const SquareMatrix&, const SquareMatrix&); //A-B
SquareMatrix operator*(const SquareMatrix&, const SquareMatrix&); //A*B
SquareMatrix operator*(double, const SquareMatrix&); //s*A


#endif