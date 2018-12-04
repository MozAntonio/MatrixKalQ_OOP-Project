/* VectVert.h */
#ifndef VECTVERT_H
#define VECTVERT_H

#include "Vect.h"
#include "VectHor.h"
class VectHor;


class VectVert: public Vect {
	public:
	//Costruttori:
		explicit VectVert(unsigned int =0);
		VectVert(unsigned int, double);
		//virtual ~VectVert();
	
	//Metodi 'concretizzati':
		virtual VectVert* clone() const;
		virtual VectVert* sum_p(const MatrixBase*) const;
		virtual VectVert* dif_p(const MatrixBase*) const;
		virtual VectVert* sProd_p(double) const;
		virtual VectVert* rev_p() const;
		virtual Vect* trans_p() const;
		virtual double& at(unsigned int);
		virtual const double& at(unsigned int) const;
		
	//Metodi ridefiniti:
		VectVert operator-() const; //-V
		VectVert operator*(double) const; //V*s
		VectHor trans() const; //trasposto
		
	//Metodi propri:
		VectVert rev() const;
		
	//Metodi ereditati:
		//	unsigned int numRows() const;
		//	unsigned int numCols() const;
		
		//	virtual void swapRows(unsigned int, unsigned int, unsigned int =0);
		//	virtual void swapCols(unsigned int, unsigned int, unsigned int =0);
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
		//	invalid_argument: operator+(..), operator-(const VectVert&, const VectVert&)
		//	invalid_argument: sum_p(..), dif_p(..)
		
}; //fine VectVert

//Funzioni esterne:
VectVert operator+(const VectVert&, const VectVert&); //V+W
VectVert operator-(const VectVert&, const VectVert&); //V-W
VectVert operator*(double, const VectVert&); //s*V


#endif