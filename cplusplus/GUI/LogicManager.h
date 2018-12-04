/* LogicManager.h */
#ifndef LOGICMANAGER_H
#define LOGICMANAGER_H

#include <QObject>
#include <QString>
#include "../Core/MatrixBase.h"


class LogicManager: public QObject {
		Q_OBJECT
	
	private:
	//Campi dati
		MatrixBase* ris;
		MatrixBase* operand2;
		QString biOp;
		QString whoS;
	
	//Funzioni di utilità
		static void scrivi(MatrixBase*, const QString&);
		static QString leggi(MatrixBase*);
		
	public:
	//Costruttore & Distruttore:
		explicit LogicManager(QObject* parent=0);
		~LogicManager();
		
	signals:
	//Segnali
		void doneSquare(const QString&, const QString&); //2x2, 3x3, nxn
		void doneRect(const QString&, const QString&); //rxc
		void doneVect(const QString&, const QString&); //1xc, rx1
		void problem(const QString&); //problema da comunicare all'utente
		void needReset(const QString&); //chiede il reset dell'app
		void biOpAll(const QString&, const QString&); //mi autochiedo di fare l'operaz binaria
		void biOpSquare(const QString&, const QString&); //mi autochiedo di fare l'operaz binaria
		
	public slots:
	//Slot pubblici:
		//creazioni
		void slotNewSquare(const QString&, uint);
		void slotNewRect(const QString&, uint, uint);
		//op unari
		void slotUnOpAll(const QString&); //rank, trans
		void slotUnOpSquare(const QString&); //isInv, det, trace, inv, adj
		void slotUnOpVect(const QString&); //rev
		//op semi-binari
		void slotSBiOpAll(const QString&, qreal); //prod per scalare
		void slotSBiOpSquare(const QString&, uint); //exp
		//op binari
		void slotBiOpAll(const QString&, const QString&); //+, -
		void slotBiOpSquare(const QString&, const QString&); //*
		void slotRandom(uint, uint, int, int, bool); //per matrici con valori random
		void slotLogicReset(); //se mi viene chiesto, resetto tutto
	
}; //fine LogicManager


#endif