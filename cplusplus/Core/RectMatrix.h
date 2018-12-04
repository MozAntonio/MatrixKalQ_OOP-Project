/* RectMatrix.h */
#ifndef RECTMATRIX_H
#define RECTMATRIX_H

#include "DenseMatrix.h"


class RectMatrix: public DenseMatrix {
	public:
	//Costruttori:
		explicit RectMatrix(unsigned int =0, unsigned int =0);
		RectMatrix(unsigned int, unsigned int, double);
		//virtual ~RectMatrix();
		
	//Metodi 'concretizzati':
		virtual RectMatrix* clone() const;
		virtual RectMatrix* sum_p(const MatrixBase*) const;
		virtual RectMatrix* dif_p(const MatrixBase*) const;
		virtual RectMatrix* sProd_p(double) const;
		virtual RectMatrix* trans_p() const;
		
	//Metodi propri:
		RectMatrix operator-() const; //-A
		RectMatrix operator*(double) const; //A*s
		RectMatrix trans() const; //trasposta
		
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
		//	ut_of_range: at(..), swapRows(..), swapCols(..)
		
		//	invalid_argument: RectMatrix(..), operator+(..), operator-(const RectMatrix&, const RectMatrix&)
		//	invalid_argument: sum_p(..), dif_p(..)
		
}; //fine RectMatrix

//Funzioni esterne:
RectMatrix operator+(const RectMatrix&, const RectMatrix&); //A+B
RectMatrix operator-(const RectMatrix&, const RectMatrix&); //A-B
RectMatrix operator*(double, const RectMatrix&); //s*A


#endif