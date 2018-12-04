/* DenseMatrix.cpp */
#include "DenseMatrix.h"
#include <stdexcept>
#include <cmath> //per std::abs in rank
#include <ctime> //time in setRandX
#include <cstdlib> //rand in setRandX


//Costruttore di default
DenseMatrix::DenseMatrix(unsigned int r, unsigned int c): MatrixBase(r, c), m(r, vector<double>(c)) {}

//Costruttore a 3 param
// crea una matrice con dim rows x cols
// imposta tutti gli elem a init
DenseMatrix::DenseMatrix(unsigned int r, unsigned int c, double init): MatrixBase(r, c), m(r, vector<double>(c, init)) {}

double& DenseMatrix::at(unsigned int i, unsigned int j) {
	return m.at(i).at(j);
}

const double& DenseMatrix::at(unsigned int i, unsigned int j) const {
	return m.at(i).at(j);
}

void DenseMatrix::swapRows(unsigned int row1, unsigned int row2, unsigned int fromCol) {
	for(unsigned int j=fromCol; j<numCols(); ++j) {
		double temp = at(row1, j);
		at(row1, j) = at(row2, j);
		at(row2, j) = temp;
	}
}

void DenseMatrix::swapCols(unsigned int col1, unsigned int col2, unsigned int fromRow) {
	for(unsigned int i=fromRow; i<numRows(); ++i) {
		double temp = at(i, col1);
		at(i, col1) = at(i, col2);
		at(i, col2) = temp;
	}
}

void DenseMatrix::print(ostream& os, string separator) const {
	for(unsigned int i=0; i<numRows(); ++i) {
		for(unsigned int j=0; j<numCols(); ++j)
			os << at(i,j) << separator;
		os << std::endl;
	}
}

void DenseMatrix::load(istream& is) {
	//controlla che sullo stream di input:
	// ci siano almeno i caratteri necessari per riempire la matrice (prima di eof)
	//	valori aggiuntivi (validi o meno) verranno ignorati
	// che tutti i caratteri necessari siano validi (double)
	//altrimenti:
	// eccezione e il contenuto della matrice è inconsistente (garbage)
	
	unsigned int i=0, j=0;
	bool stop = false;
	
	for( ; i<numRows() && !stop; ++i) {
		j=0;
		for( ; j<numCols() && !stop; ++j) {
			is >> at(i,j);
			if(is. eof() || is.fail()) //ho finito i dati o tra essi c'era un non-double
				stop = true;
		}
	}
	
	bool sufficienti = (i*j == numCols()*numRows());
	
	if( is.good() || (is.eof() && sufficienti) ) //tutto ok
        return;
    else
        if( is.eof() ) //&& !sufficienti
            throw std::invalid_argument("valori non sufficienti");
        else
            if( is.fail() ) //tra i dati che mi servono c'è un non-double
                throw std::invalid_argument("valori di tipo errato");
            else //is.bad()
                throw std::invalid_argument("errore imprevisto nelle fasi di input (bad stream), riavviare.\n Se il problema persiste contattare lo sviluppatore");
	

//	approccio naive che accetta tutto senza tanti problemi
//	for(unsigned int i=0; i<numRows(); ++i)
//		for(unsigned int j=0; j<numCols(); ++j)
//			is >> at(i,j);
	
}

//calcola il rango tramite il metodo di eliminazione di Gauss con pivoting parziale
unsigned int DenseMatrix::rank() const {
    unsigned int rig=numRows(), col=numCols(), rk=0;
	DenseMatrix* aux = clone(); //matrice ausiliaria d'appoggio
	bool finito = false;
	
	for(unsigned int d=0; d<col && d<rig && !finito; ++d) {
		
		//cerco il massimo pivot sotto di me
		unsigned int pivot_row = d;
		double cur = std::abs(aux->at(d,d));
		for(unsigned int k=d+1; k<rig; ++k)
			if(std::abs(aux->at(k,d)) > cur) {
				pivot_row = k;
				cur = aux->at(k,d);
			}

		 //se ne ho trovato uno maggiore, scambio la riga attuale con quella con il pivot massimo
		if(pivot_row != d)
			aux->swapRows(d, pivot_row, d); //solo gli elem da 'd' in poi, gli altri sono zeri
		
		if(std::abs(aux->at(d,d)) < 0.00000000000001) { //questa colonna ha solo zeri da qua in giù
			if(d+1<col) { //ho ancora colonne da controllare
				aux->swapCols(d, col-1, d); //col-1 è l'ultima, solo gli elem da 'd' in giù, gli altri non servono
				col--; //la colonna che sposto è inutile, quindi la escludo
				d--; //rifaccio questo giro d'iteraz, lo swap ha messo un nuovo elem in A[d][d]
			}
			else { //ho finito le colonne, quindi ho finito
				delete aux; //pulisco lo heap
				//return rk; //rk a questo punto sarà il num di col linear indip, cioè il rango
				finito=true; //se lascio qui dentro il return il compil mi da warning perchè non lo trova
			}
		}
		else { //aux->at(d,d)!=0
			//devo azzerare gli elem sotto di me, cioè:
			//aux->at(d+1,d), aux->at(d+2,d), ..., aux->at(i,d) con: d<i<rig
			for(unsigned int i=d+1; i<rig; ++i) {
				if(aux->at(i,d) != 0) { //va annullato
					//per annullarlo:
					//sostituisco l'intera riga in cui risiede l'elem da annullare (la i-esima)
					//con la differenza tra essa (la i-esima) e quella del 'pivot' (la d-esima)
					//moltiplicata per un coefficiente (coef)
					//coef è il rapporto tra l'elem da annullare (aux->at(i,d)) e il pivot (aux->at(d,d))
					double coef = aux->at(i,d) / aux->at(d,d);
					for(unsigned int j=d; j<col; ++j)
						aux->at(i,j) = aux->at(i,j) - (aux->at(d,j)*coef);
				}
				//else //l'elem è già zero, passo al prossimo
			}
			rk++; //questa, in cui A[d][d]!=0, è una colonna 'utile' che contribuisce al rango
		}
	}
	return rk;
}

void DenseMatrix::fill(double val) {
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j)
			at(i,j) = val;
}

void DenseMatrix::setRandInt(int from, int to) { //rand in [from,to)
	std::srand(std::time(0)); //seed
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j)
			at(i,j) = (std::rand() % (to-from) + from);
}

void DenseMatrix::setRandReal(double from, double to) { //rand in from[from,to]
	std::srand(std::time(0)); //seed
	for(unsigned int i=0; i<numRows(); ++i)
		for(unsigned int j=0; j<numCols(); ++j)
			at(i,j) = from + static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX/(to-from)));
		
}
