/* OutOperation.h */
#ifndef OUTOPERATION_H
#define OUTOPERATION_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>


class OutOperation: public QWidget {
		Q_OBJECT
	
	private:
	//Campi dati
		//QPushButton:
		QPushButton* pbRank;
		QPushButton* pbIsInv;
		QPushButton* pbDet;
		QPushButton* pbTrace;
		QPushButton* pbTrans;
		QPushButton* pbInv;
		QPushButton* pbAdjoint;
		QPushButton* pbRev;
		
		QPushButton* pbScalarProd;
		QPushButton* pbExp;
		
		QPushButton* pbPlus;
		QPushButton* pbMinus;
		QPushButton* pbMul;
		
		//QLineEdit:
		QLineEdit* leScalarProd;
		QLineEdit* leExp;
		
	public:
	//Costruttore & Distruttore:
		explicit OutOperation(QWidget* parent =0);
		~OutOperation();
		
	//Setter pubblici:
		void resetFieldsOutOpe();
		void setOpSquare();
		void setOpRect();
		void setOpVect();
		
	signals:
	//Segnali:
		void sigOpUpSquare(const QString&);			//det, trace, adj, isInv, inv
		void sigOpUpRect(const QString&);			//rank, trans
		void sigOpUpVect(const QString&); 			//rev
		void sigOpMidSquare(const QString&, uint);	//exp
		void sigOpMidRect(const QString&, qreal);	//sProd
		void sigOpLowSquare(const QString&);		//prod
		void sigOpLowRect(const QString&);			//sum, diff
		
	public slots:
	//Slot pubblici:
		void slotOpUpSquare();
		void slotOpUpRect();
		void slotOpUpVect();
		void slotOpMidSquare();
		void slotOpMidRect();
		void slotOpLowSquare();
		void slotOpLowRect();
	
};


#endif
