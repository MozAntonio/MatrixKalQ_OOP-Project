/* Vect.h */
#ifndef VECT_H
#define VECT_H

#include "RectMatrix.h"


class Vect: public RectMatrix {
	public:
	//Costruttori:
		explicit Vect(unsigned int =0, unsigned int =0);
		Vect(unsigned int, unsigned int, double);
		//virtual ~Vect();
	
	//Dichiarazione d'uso
		using RectMatrix::at;
	
	//Metodi virtuali puri:
		virtual Vect* clone() const =0;
		virtual Vect* sum_p(const MatrixBase*) const =0;
		virtual Vect* dif_p(const MatrixBase*) const =0;
		virtual Vect* sProd_p(double) const =0;
		virtual Vect* rev_p() const =0;
		virtual Vect* trans_p() const =0;
		virtual double& at(unsigned int) =0; //ridef
		virtual const double& at(unsigned int) const =0; //ridef
		
	//Override:
		virtual unsigned int rank() const;
		
	//Metodi propri:
		unsigned int numElem() const;
		virtual void swapElem(unsigned int, unsigned int);
		
	//Metodi ereditati:
		//	unsigned int numRows() const;
		//	unsigned int numCols() const;
		
		//	virtual void swapRows(unsigned int, unsigned int, unsigned int =0);
		//	virtual void swapCols(unsigned int, unsigned int, unsigned int =0);
		//	virtual void print(ostream&, string ="\t") const;
		//	virtual void load(istream&);
		//	void fill(double);
		//	void setRandInt(int =0, int =100);
		//	void setRandReal(double =0, double =100);
		
		//	RectMatrix operator-() const; //-A
		//	RectMatrix operator*(double) const; //A*s
		//	RectMatrix trans() const; //trasposta
		
	//Eccezioni:
		// out_of_range: (using)at(..), swapRows(..), swapCols(..)
		
		//	invalid_argument: Vect(..)
		
}; //fine Vect


#endif