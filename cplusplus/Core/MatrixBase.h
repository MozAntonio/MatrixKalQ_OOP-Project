/* MatrixBase.h */
#ifndef MATRIXBASE_H
#define MATRIXBASE_H

#include <iostream>
#include <string>

using std::ostream;
using std::istream;
using std::string;


//Abstract Base Class
class MatrixBase {
	private:
	//Campi dati:
		unsigned int rows;
		unsigned int cols;
		
	public:
	//Costruttore e distruttore:
		explicit MatrixBase(unsigned int =0, unsigned int =0);
		virtual ~MatrixBase();
		
	//Metodi virtuali puri:
		virtual MatrixBase* clone() const =0;
		virtual double& at(unsigned int, unsigned int) =0;
		virtual const double& at(unsigned int, unsigned int) const =0;
		virtual void swapRows(unsigned int, unsigned int, unsigned int =0) =0;
		virtual void swapCols(unsigned int, unsigned int, unsigned int =0) =0;
		virtual void print(ostream&, string ="\t") const =0;
		virtual void load(istream&) =0;
		virtual unsigned int rank() const =0;
		virtual MatrixBase* sum_p(const MatrixBase*) const =0;
		virtual MatrixBase* dif_p(const MatrixBase*) const =0;
		virtual MatrixBase* sProd_p(double) const =0;
		virtual MatrixBase* trans_p() const =0;
		
	//Metodi propri:
		unsigned int numRows() const;
		unsigned int numCols() const;
		
}; //fine MatrixBase

//Funzioni esterne:
ostream& operator<<(ostream&, const MatrixBase&);
istream& operator>>(istream&, MatrixBase&);
bool operator==(const MatrixBase&, const MatrixBase&); //A==B
bool operator!=(const MatrixBase&, const MatrixBase&); //A!=B


#endif