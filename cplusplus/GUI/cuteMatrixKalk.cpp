/* cuteMatrixKalk.cpp */
#include "cuteMatrixKalk.h"


cuteMatrixKalk::cuteMatrixKalk(QObject* parent): QObject(parent), logicm(0), layoutm(0) {
	
//Crea i suoi campi dati
	logicm = new LogicManager(this); //figlio
	layoutm = new LayoutManager(); //non figlio

//Instaura le connessioni tra gli slot e signal dei suoi campi dati

	//signal di LayoutManager con slot di LogicManager
	QObject::connect(layoutm,SIGNAL(newSquare(const QString&,uint)),logicm,SLOT(slotNewSquare(const QString&,uint)));
	QObject::connect(layoutm,SIGNAL(newRect(const QString&,uint,uint)),logicm,SLOT(slotNewRect(const QString&,uint,uint)));
	QObject::connect(layoutm,SIGNAL(unOpAll(const QString&)),logicm,SLOT(slotUnOpAll(const QString&)));
	QObject::connect(layoutm,SIGNAL(unOpSquare(const QString&)),logicm,SLOT(slotUnOpSquare(const QString&)));
	QObject::connect(layoutm,SIGNAL(unOpVect(const QString&)),logicm,SLOT(slotUnOpVect(const QString&)));
	QObject::connect(layoutm,SIGNAL(sBiOpAll(const QString&,qreal)),logicm,SLOT(slotSBiOpAll(const QString&,qreal)));
	QObject::connect(layoutm,SIGNAL(sBiOpSquare(const QString&,uint)),logicm,SLOT(slotSBiOpSquare(const QString&,uint)));
	QObject::connect(layoutm,SIGNAL(biOpAll(const QString&,const QString&)),logicm,SLOT(slotBiOpAll(const QString&,const QString&)));
	QObject::connect(layoutm,SIGNAL(biOpSquare(const QString&,const QString&)),logicm,SLOT(slotBiOpSquare(const QString&,const QString&)));
	QObject::connect(layoutm,SIGNAL(reset()),logicm,SLOT(slotLogicReset()));
	QObject::connect(layoutm,SIGNAL(random(uint, uint, int, int, bool)),logicm,SLOT(slotRandom(uint, uint, int, int, bool)));
	
	//signal di LogicManager con slot di LayoutManager
	QObject::connect(logicm,SIGNAL(doneSquare(const QString&,const QString&)),layoutm,SLOT(slotDoneSquare(const QString&,const QString&)));
	QObject::connect(logicm,SIGNAL(doneRect(const QString&,const QString&)),layoutm,SLOT(slotDoneRect(const QString&,const QString&)));
	QObject::connect(logicm,SIGNAL(doneVect(const QString&,const QString&)),layoutm,SLOT(slotDoneVect(const QString&,const QString&)));
	QObject::connect(logicm,SIGNAL(problem(const QString&)),layoutm,SLOT(slotProblem(const QString&)));
	QObject::connect(logicm,SIGNAL(needReset(const QString&)),layoutm,SLOT(slotLayoutReset(const QString&)));
	
}

cuteMatrixKalk::~cuteMatrixKalk() {
	if(layoutm)
		delete layoutm;
//NON serve, essendo mio figlio si arrangia Qt	
//	if(logicm)
//		delete logicm;
}

void cuteMatrixKalk::avvia() const {
	layoutm->show();
}
