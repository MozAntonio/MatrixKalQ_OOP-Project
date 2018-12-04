/* MatrixBase.cpp */
#include "MatrixBase.h"


//Metodi interni:

MatrixBase::MatrixBase(unsigned int r, unsigned int c): rows(r), cols(c) {}

MatrixBase::~MatrixBase() {}

unsigned int MatrixBase::numRows() const {
	return rows;
}

unsigned int MatrixBase::numCols() const {
	return cols;
}


//Funzioni esterne:

ostream& operator<<(ostream& os, const MatrixBase& m) {
	m.print(os);
	return os;
}

istream& operator>>(istream& is, MatrixBase& m) {
	m.load(is);
	return is;
}

bool operator==(const MatrixBase& m1, const MatrixBase& m2) {
	bool uguali = true;
	if(!(m1.numRows()==m2.numRows() && m1.numCols()==m2.numCols()))
		uguali = false;
	else
		for(unsigned int i=0; i<m1.numRows() && uguali; ++i) //o: i<m2.numRows()
			for(unsigned int j=0; j<m1.numCols() && uguali; ++j) //o: j<m2.numCols()
				if(m1.at(i,j) != m2.at(i,j))
					uguali = false;
	
	return uguali;
}

bool operator!=(const MatrixBase& m1, const MatrixBase& m2) {
	return !(m1==m2);
}