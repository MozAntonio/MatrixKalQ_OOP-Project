/* cuteMatrixKalk.h */
#ifndef CUTEMATRIXKALK_H
#define CUTEMATRIXKALK_H

#include "LogicManager.h"
#include "LayoutManager.h"
#include <QObject>
#include <QString>

class cuteMatrixKalk: public QObject {
		Q_OBJECT

	private:
		//Campi dati
		LogicManager* logicm;
		LayoutManager* layoutm;
	
	public:
		//Costruttore
		explicit cuteMatrixKalk(QObject* parent =0);
		 ~cuteMatrixKalk();
		
		//Metodi
		void avvia() const;
		
}; //fine cuteMatrixKalk


#endif
