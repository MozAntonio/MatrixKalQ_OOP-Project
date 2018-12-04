/* SquareMatrix.cpp */
#include "SquareMatrix.h"
#include <stdexcept>


//Costruttore di default
SquareMatrix::SquareMatrix(unsigned int n): DenseMatrix(n, n) {}

//Costruttore a 2 param
// crea una matrice quadrata con dim n x n
// imposta tutti gli elem a init
SquareMatrix::SquareMatrix(unsigned int n, double init): DenseMatrix(n, n, init) {}

SquareMatrix* SquareMatrix::clone() const {
	return new SquareMatrix(*this);
}

SquareMatrix* SquareMatrix::sum_p(const MatrixBase* m) const {
	const SquareMatrix* q = dynamic_cast<const SquareMatrix*>(m);
	
	if(!q) //sono permesse somme solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sommare ad una matrice quadrata solo una matrice quadrata");
	
	return new SquareMatrix(*this + *q);
}

SquareMatrix* SquareMatrix::dif_p(const MatrixBase* m) const {
	const SquareMatrix* q = dynamic_cast<const SquareMatrix*>(m);
	
	if(!q) //sono permesse differenze solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile sottrarre ad una matrice quadrata solo una matrice quadrata");
	
	return new SquareMatrix(*this - *q);
}

SquareMatrix* SquareMatrix::sProd_p(double scalar) const {
	return new SquareMatrix((*this) * scalar);
}

SquareMatrix* SquareMatrix::trans_p() const {
	return new SquareMatrix(trans()); //cioè: (*this).trans(); o this->trans();
}

SquareMatrix* SquareMatrix::prod_p(const SquareMatrix* m) const {
	const SquareMatrix* q = dynamic_cast<const SquareMatrix*>(m);
	
	if(!q) //sono permessi prodotti solo tra un tipo (T1) e un suo sottotipo (T2) (T2<=T1)
		throw std::invalid_argument("è possibile moltiplicare una matrice quadrata solo con una matrice quadrata");
	
	return new SquareMatrix((*this) * (*q));
}

SquareMatrix* SquareMatrix::exp_p(unsigned int pot) const {
	return new SquareMatrix(exp(pot)); //cioè: (*this).exp(pot); o this->exp(pot);
}

SquareMatrix* SquareMatrix::inv_p() const {
	return new SquareMatrix(inv()); //cioè: (*this).inv; o this->inv;
}

SquareMatrix* SquareMatrix::adj_p() const {
	return new SquareMatrix(adjoint()); //cioè: (*this).adjoint(); o this->adjoint();
}

//Funzione che restituisce una copia della sotto-matrice ottenuta eliminando la riga "rowElem" e la colonna "colElem" dalla matrice quadrata di invocazione "n x n"
SquareMatrix SquareMatrix::subMatrix(unsigned int rowElem, unsigned int colElem, unsigned int n) const {
	if(n==0)
		n=numRows(); //o: n=numCols();
	
	unsigned int i=0, j=0;
	SquareMatrix aux = SquareMatrix(n);
	
	//Scorro tutti gli elementi della matrice d'invocazione
	for(unsigned int r=0; r<n; ++r)
		for(unsigned int c=0; c<n; ++c) {
			
			//Creo la sotto-matrice di copia dalla sotto-matrice dell'oggetto d'invocazione
			//Escludendo gli elementi appartenenti alla riga "rowElem" e quelli appartenenti alla colonna "colElem"
			if ((r!=rowElem) && (c!=colElem)) {
				aux.at(i,j) = at(r,c);
				j++;
				
				//Se la riga della sotto-matrice che sto costruendo è piena:
				//Incremento l'indice delle righe, e riazzero l'indice delle colonne
				if (j==n-1) {
					i++;
					j=0;
				}
			}
		}
	
	return aux;
}

//Funzione statica ricorsiva che calcola il determinante della matrice quadrata passata come parametro con dimensioni "n x n"
double SquareMatrix::calcDet(const SquareMatrix& m, unsigned int n) {
	//Inizializzo a "0" il determinante risultato
	double ris=0;
	
	//Caso base: La matrice contiene un solo elemento (matrice 1x1)
	if(n==1)
		return m.at(0,0);
	
	//Caso ricorsivo:
	//Variabile per il 'segno': Valori possibili "1" o "-1"
	int sign=1;
	
	//Matrice temporanea per salvarmi le sotto-matrici ottenute dall'eliminazione dell'i-esima riga e della j-esima colonna della matrice d'invocazione
	SquareMatrix temp;
	
	for(unsigned int j=0; j<n; ++j) {
		//Calcolo la sotto-matrice eliminando la riga "0" e la colonna "j" dalla matrice d'invocazione: "m"
		temp = m.subMatrix(0,j,n);
		
		//Sommo al determinante risultato che ho già la moltiplicazione fra "sign", l'elemento in riga "0" e colonna "j",
		//e la chiamata ricorsiva sulla matrice diminuita di una colonna
		ris = ris + (sign * m.at(0,j) * calcDet(temp,n-1));
		
		//Di volta in volta i termini per il calcolo del determinante risultato devono essere sommati con segno opposto
		sign = -sign;
	}
	
	return ris;
}

SquareMatrix SquareMatrix::operator-() const {
	return ((*this)*(-1));
}

SquareMatrix SquareMatrix::operator*(double scalar) const {
	SquareMatrix aux = SquareMatrix(numRows());
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j) //o: j<numRows()
			aux.at(i,j) = at(i,j) * scalar;
	
	return aux;
}

SquareMatrix SquareMatrix::trans() const {
	SquareMatrix aux = SquareMatrix(numRows(), 0);
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j) //o: j<numRows()
			aux.at(j,i) = at(i,j);
	
	return aux;
}

SquareMatrix SquareMatrix::exp(unsigned int pot) const {
	SquareMatrix aux = SquareMatrix(numRows()); //o: numCols()
	if(pot==0)
		aux.setIdentity();
	else
		aux = *this;
	
	for(unsigned int i=1; i<pot; ++i)
		aux = aux * (*this);
	
	return aux;
}

SquareMatrix SquareMatrix::inv() const {
	
	if(!isInvertible())
		throw std::domain_error("matrice non invertibile");
	
	//Calcolo il determinante della matrice quadrata d'invocazione
	double determinant = det();
	
	unsigned int n=numRows(); //o: n=numCols();
	SquareMatrix aux = SquareMatrix(n);
	
	//Calcolo la matrice aggiunta della matrice quadrata d'invocazione
	SquareMatrix adj = adjoint();
	
	//Calcolo la matrice inversa utilizzando la formula: "inverse(A) = adjoint(A) / det(A)"
	for(unsigned int i=0; i<n; ++i)
		for(unsigned int j=0; j<n; ++j)
			aux.at(i,j) = adj.at(i,j) / determinant;
	
	return aux;
}

SquareMatrix SquareMatrix::adjoint() const {
	unsigned int n=numRows(); //o: n=numCols();
	SquareMatrix aux = SquareMatrix(n);
	
	//Caso banale: n=1
	if(n==1)
		aux.at(0,0) = at(0,0);
	else {
		//Variabile per il 'segno': Valori possibili "1" o "-1"
		int sign=1;
		
		//Matrice temporanea per salvarmi le sotto-matrici ottenute dall'eliminazione dell'i-esima riga e della j-esima colonna della matrice d'invocazione
		SquareMatrix temp;
		
		//Scorro tutte le righe della matrice d'invocazione
		for(unsigned int i=0; i<n; ++i)
			//Scorro tutte le colonne della matrice d'invocazione
			for(unsigned int j=0; j<n; ++j) {
				//Calcolo la sotto-matrice eliminando la riga "i" e la colonna "j" dalla matrice d'invocazione
				temp = subMatrix(i,j);
				
				//Il segno dell'elemento "aux.at(i,j)" è positivo se la somma "i+j" (#row + #col) è pari
				//Altrimenti, ovvero se la somma "i+j" (#row + #col) è dispari, il segno è negativo
				if(((i+j) % 2) == 0)
					sign = 1;
				else
					sign = -1;
				
				//Scambio l'indice delle righe "i" con l'indice delle colonne "j" per ottenere la trasposta della matrice dei cofattori della matrice d'invocazione
				aux.at(j,i) = (sign) * (calcDet(temp,n-1));
			}
	}
	
	return aux;
}

bool SquareMatrix::isInvertible() const {
	if(rank() == numCols()) //o: numRows()
		return true;
	else
		return false;
}

double SquareMatrix::det() const {
	return calcDet(*this, numRows()); //o: numCols()
}

double SquareMatrix::trace() const {
	double tr=0;
	unsigned int n=numRows(); //o: n=numCols();
	
	for(unsigned int i=0; i<n; ++i)
		for(unsigned int j=0; j<n; ++j)
			if(i==j)
				tr = tr + at(i,j);
	
	return tr;
}

void SquareMatrix::setIdentity() {
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j) { //o: numRows()
			if(i!=j)
				at(i,j)=0;
			else
				at(i,j)=1;
		}
}


//Funzioni esterne:

SquareMatrix operator+(const SquareMatrix& m1, const SquareMatrix& m2) {
	if(m1.numRows() != m2.numRows()) //o: m1.numcols() != m2.numCols()
		throw std::invalid_argument("la somma è permessa solo tra matrici quadrate dello stesso ordine"); //dimensioni non compatibili
	
	unsigned int n=m1.numRows(); //o: m1.numCols(), m2.numRows(), m2.numCols()
	
	SquareMatrix aux = SquareMatrix(n);
	
	for(unsigned int i=0; i<n; ++i)
		for(unsigned int j=0; j<n; ++j)
			aux.at(i,j) = m1.at(i,j) + m2.at(i,j);
	
	return aux;
}

SquareMatrix operator-(const SquareMatrix& m1, const SquareMatrix& m2) {
	return (m1 + (-m2));
}

SquareMatrix operator*(const SquareMatrix& m1, const SquareMatrix& m2) {
	if(m1.numRows() != m2.numRows()) //o: m1.numcols() != m2.numCols()
		throw std::invalid_argument("il prodotto è permesso solo tra matrici quadrate dello stesso ordine"); //dimensioni non compatibili
	
	SquareMatrix aux = SquareMatrix(m1.numRows(),0); //o: m1.numCols(), m2.numRows(), m2.numCols()
	
	for(unsigned int i=0; i<m1.numRows(); ++i)
		for(unsigned int j=0; j<m2.numCols(); ++j)
			for(unsigned int k=0; k<m1.numCols(); ++k) //o: k<m2.numRows()
				aux.at(i,j) = aux.at(i,j) + (m1.at(i,k) * m2.at(k,j));
			
	return aux;
}

SquareMatrix operator*(double scalar, const SquareMatrix& m) {
	return m*scalar;
}
