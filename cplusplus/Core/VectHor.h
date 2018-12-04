/* VectHor.h */
#ifndef VECTHOR_H
#define VECTHOR_H

#include "Vect.h"
#include "VectVert.h"
class VectVert;


class VectHor: public Vect {
	public:
	//Costruttori:
		explicit VectHor(unsigned int =0);
		VectHor(unsigned int, double);
		//virtual ~VectHor();
	
	//Metodi 'concretizzati':
		virtual VectHor* clone() const;
		virtual VectHor* sum_p(const MatrixBase*) const;
		virtual VectHor* dif_p(const MatrixBase*) const;
		virtual VectHor* sProd_p(double) const;
		virtual VectHor* rev_p() const;
		virtual Vect* trans_p() const;
		virtual double& at(unsigned int);
		virtual const double& at(unsigned int) const;
		
	//Metodi ridefiniti:
		VectHor operator-() const; //-V
		VectHor operator*(double) const; //V*s
		VectVert trans() const; //trasposto
		
	//Metodi propri:
		VectHor rev() const;
		
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
		
		//	virtual unsigned int rank() const;
		//	unsigned int numElem() const;
		//	virtual void swapElem(unsigned int, unsigned int);
		
	//Eccezioni:
		// out_of_range: swapRows(..), swapCols(..)
		
		//	out_of_range: swapElem(..) [a causa di at(..)]
		//	out_of_range: at(..)
		//	invalid_argument: operator+(..), operator-(const VectHor&, const VectHor&)
		//	invalid_argument: sum_p(..), dif_p(..)
		
}; //fine VectHor

//Funzioni esterne:
VectHor operator+(const VectHor&, const VectHor&); //V+W
VectHor operator-(const VectHor&, const VectHor&); //V-W
VectHor operator*(double, const VectHor&); //s*V


#endif