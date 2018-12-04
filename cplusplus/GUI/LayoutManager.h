/* LayoutManager.h */
#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H

#include "InpSelect.h"
#include "InpInsert.h"
#include "OutOperation.h"
#include "OutResult.h"
#include <QWidget>
#include <QString>


class LayoutManager: public QWidget {
		Q_OBJECT
		
	private:
	//Campi dati
		InpSelect* inpSelectWind;	//input: sotto-finestra (sinistra) di scelta della matrice
		InpInsert* inpInsertWind;	//input: sotto-finestra (destra) di inserimento della matrice
		OutOperation* outOperWind;	//output: sotto-finestra (sinistra) di scelta dell'operazione
		OutResult* outResWind;		//output: sotto-finestra (destra) per la stampa del risultato
		
		uint numRows;
		uint numCols;
		
	public:
	//Costruttore & Distruttore:
		explicit LayoutManager(QWidget* parent =0);
		~LayoutManager();
		
	signals:
	//Segnali:
		void newSquare(const QString&, uint);		//Matrix: 2x2, 3x3, NxN (input dell'utente così com'è); Dimensione: 2, 3, N
		void newRect(const QString&, uint, uint);	//Matrix: NxM, 1xN, Nx1 (input dell'utente così com'è); Dimensione: #row, #col
	
		void unOpAll(const QString&);		//rank, trans
		void unOpSquare(const QString&);	//isInv, inv, adj, det, trace
		void unOpVect(const QString&);		//rev
		
		void sBiOpAll(const QString&, qreal);		//sProd: input utente + scalare
		void sBiOpSquare(const QString&, uint);		//exp: input utente + esponente
		
		void biOpAll(const QString&, const QString&);			//sum, diff
		void biOpSquare(const QString&, const QString&);		//prod
		
		void reset();								//segnale di reset e riavvio della QKalk (per la parte logica)
		void random(uint, uint, int, int, bool);	//segnale per la generazione di una matrice con numeri casuali (per la parte logica)
		
	public slots:
	//Slot pubblici
		//Input:
		void slotSelectSquare(uint);		//2x2, 3x3, NxN
		void slotSelectRect(uint, uint);	//NxM, 1xN, Nx1
		
		void slotOtherInput(const QString&);	//random, file
		void slotGoOn(const QString&);			//go on!
		
		//Input & Output:
		void slotLayoutReset(const QString&);		//reset e riavvio della QKalk
		
		//Output:
		void slotSelectUnOpSquare(const QString&);			//det, trace, adj, isInv, inv
		void slotSelectUnOpRect(const QString&);			//rank, trans
		void slotSelectUnOpVect(const QString&);			//rev
		void slotSelectSBiOpSquare(const QString&, uint);	//exp
		void slotSelectSBiOpRect(const QString&, qreal);	//scalarProd
		void slotSelectBiOpSquare(const QString&);			//prod
		void slotSelectBiOpRect(const QString&);			//sum, diff
		
		void slotSaveFile(const QString&);		//save matrix in file
		
		//LogicManager:
		void slotDoneSquare(const QString&, const QString&);	//costruita matrice quadrata (risultato per "text" e "line")
		void slotDoneRect(const QString&, const QString&);		//costruita matrice rettangolare (risultato per "text" e "line")
		void slotDoneVect(const QString&, const QString&);		//costruito vettore (risultato per "text" e "line")
		
		void slotProblem(const QString&);		//si è verificato un problema durante l'esecuzione della parte logica
};


#endif
