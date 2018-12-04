/* DenseMatrix.h */
#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <vector>
#include "MatrixBase.h"

using std::vector;


//Abstract Base Class
class DenseMatrix: public MatrixBase {
	private:
	//Campi dati:
		vector< vector<double> > m; //con vector<vector<double>> si confonde
		
	public:
	//Costruttori:
		explicit DenseMatrix(unsigned int =0, unsigned int =0);
		DenseMatrix(unsigned int, unsigned int, double);
		//virtual ~DenseMatrix();
		
	//Metodi virtuali puri:
		virtual DenseMatrix* clone() const =0;
		virtual DenseMatrix* sum_p(const MatrixBase*) const =0;
		virtual DenseMatrix* dif_p(const MatrixBase*) const =0;
		virtual DenseMatrix* sProd_p(double) const =0;
		virtual DenseMatrix* trans_p() const =0;
		
	//Metodi 'concretizzati':
		virtual double& at(unsigned int, unsigned int);
		virtual const double& at(unsigned int, unsigned int) const;
		virtual void swapRows(unsigned int, unsigned int, unsigned int =0);
		virtual void swapCols(unsigned int, unsigned int, unsigned int =0);
		virtual void print(ostream&, string ="\t") const;
		virtual void load(istream&);
		virtual unsigned int rank() const;
		
	//Metodi propri:
		void fill(double);
		void setRandInt(int =0, int =100);
		void setRandReal(double =0, double =100);
		
	//Metodi ereditati:
		//	unsigned int numRows() const;
		//	unsigned int numCols() const;
		
	//Eccezioni:
		//	out_of_range: at(..), swapRows(..), swapCols(..)
		//	invalid_argument: load(..)
		
}; //fine DenseMatrix


#endif