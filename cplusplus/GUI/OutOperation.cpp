/* OutOperation.cpp */
#include "OutOperation.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>


OutOperation::OutOperation(QWidget* parent): QWidget(parent) {
	
	//Creo gli oggetti della finestra di scelta dell'operazione:
	//QPushButton:
	pbRank = new QPushButton("\u03C1(A)",this);
	pbIsInv = new QPushButton("A\u207B\u00B9 ?",this);
	pbDet = new QPushButton("det(A)",this);
	pbTrace = new QPushButton("tr(A)",this);
	pbTrans = new QPushButton("A\u1D40",this);
	pbInv = new QPushButton("A\u207B\u00B9",this);
	pbAdjoint = new QPushButton("adj(A)",this);
	pbRev = new QPushButton("rev(V)",this);
	
	pbScalarProd = new QPushButton("s*A",this);
	pbExp = new QPushButton("A\u207F",this);
	
	pbPlus = new QPushButton("+",this);
	pbMinus = new QPushButton("-",this);
	pbMul = new QPushButton("\u00D7",this);
	
	pbRank->setToolTip("Rango");
	pbIsInv->setToolTip("Dice se la matrice è invertibile");
	pbDet->setToolTip("Determinante");
	pbTrace->setToolTip("Traccia");
	pbTrans->setToolTip("Trasposta");
	pbInv->setToolTip("Inversa (se possibile)");
	pbAdjoint->setToolTip("Aggiunta (trasposta della matrice dei cofattori)");
	pbRev->setToolTip("Inverte l'ordine degli elementi (del vettore)");
	
	pbScalarProd->setToolTip("Moltiplicazione per uno scalare 's' (con 's' reale)");
	pbExp->setToolTip("Potenza n-esima ('n' intero \u2265 0)");
	
	pbPlus->setToolTip("Addizione");
	pbMinus->setToolTip("Sottrazione");
	pbMul->setToolTip("Moltiplicazione");
	
	//QLineEdit:
	leScalarProd = new QLineEdit("",this);
	leExp = new QLineEdit("",this);
	
	leScalarProd->setPlaceholderText("s");
	leExp->setPlaceholderText("n");
	
	
	//Creo un layout verticale che contiene tre layout a griglia:
	QVBoxLayout* inputOpAll = new QVBoxLayout(this);
	
	//Operazioni unarie:
	QGridLayout* inputUnOp = new QGridLayout();
		//addWidget( <nameWidget> , #row , #column , #row-span =1, #col-span =1)
		inputUnOp->addWidget(pbRank,0,0,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbIsInv,1,0,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbDet,2,0,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbTrace,3,0,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbTrans,0,3,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbInv,1,3,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbAdjoint,2,3,1,2,Qt::AlignHCenter);
		inputUnOp->addWidget(pbRev,3,3,1,2,Qt::AlignHCenter);
	
	//Operazioni semi-binarie:
	QGridLayout* inputSeBinOp = new QGridLayout();
		inputSeBinOp->addWidget(pbScalarProd,0,0,1,1,Qt::AlignHCenter);
		inputSeBinOp->addWidget(leScalarProd,0,1,1,1,Qt::AlignLeft);
		inputSeBinOp->addWidget(pbExp,0,3,1,1,Qt::AlignHCenter);
		inputSeBinOp->addWidget(leExp,0,4,1,1,Qt::AlignLeft);
		
		leScalarProd->setMaximumSize(60,30);
		leExp->setMaximumSize(60,30);
	
	//Operazioni binarie:
	QGridLayout* inputBinOp = new QGridLayout();
		//addWidget( <nameWidget> , #row , #column , #row-span =1, #col-span =1)
		inputBinOp->addWidget(pbPlus,0,0,1,1,Qt::AlignHCenter);
		inputBinOp->addWidget(pbMinus,0,2,1,1,Qt::AlignHCenter);
		inputBinOp->addWidget(pbMul,0,4,1,1,Qt::AlignHCenter);
	
	inputOpAll->addLayout(inputUnOp);
	inputOpAll->addLayout(inputSeBinOp);
	inputOpAll->addLayout(inputBinOp);
	
	this->setLayout(inputOpAll);
	
	
	//Connessioni per l'evento "clicked()" delle possibili operazioni:
	connect(pbIsInv,SIGNAL(clicked()),this,SLOT(slotOpUpSquare()));
	connect(pbDet,SIGNAL(clicked()),this,SLOT(slotOpUpSquare()));
	connect(pbTrace,SIGNAL(clicked()),this,SLOT(slotOpUpSquare()));
	connect(pbInv,SIGNAL(clicked()),this,SLOT(slotOpUpSquare()));
	connect(pbAdjoint,SIGNAL(clicked()),this,SLOT(slotOpUpSquare()));
	connect(pbRank,SIGNAL(clicked()),this,SLOT(slotOpUpRect()));
	connect(pbTrans,SIGNAL(clicked()),this,SLOT(slotOpUpRect()));
	connect(pbRev,SIGNAL(clicked()),this,SLOT(slotOpUpVect()));
	connect(pbExp,SIGNAL(clicked()),this,SLOT(slotOpMidSquare()));
	connect(pbScalarProd,SIGNAL(clicked()),this,SLOT(slotOpMidRect()));
	connect(pbMul,SIGNAL(clicked()),this,SLOT(slotOpLowSquare()));
	connect(pbPlus,SIGNAL(clicked()),this,SLOT(slotOpLowRect()));
	connect(pbMinus,SIGNAL(clicked()),this,SLOT(slotOpLowRect()));
}

OutOperation::~OutOperation() {}

void OutOperation::resetFieldsOutOpe() {
	leScalarProd->setText("");
	leExp->setText("");
}

void OutOperation::setOpSquare() {
	pbRev->setEnabled(false);
}

void OutOperation::setOpRect() {
	setOpSquare();
	pbIsInv->setEnabled(false);
	pbDet->setEnabled(false);
	pbTrace->setEnabled(false);
	pbInv->setEnabled(false);
	pbAdjoint->setEnabled(false);
	pbExp->setEnabled(false);
	pbMul->setEnabled(false);
}

void OutOperation::setOpVect() {
	setOpRect();
	pbRev->setEnabled(true);
}

void OutOperation::slotOpUpSquare() {
	resetFieldsOutOpe();
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOpUpSquare(whoSender);
}

void OutOperation::slotOpUpRect() {
	resetFieldsOutOpe();
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOpUpRect(whoSender);
}

void OutOperation::slotOpUpVect() {
	resetFieldsOutOpe();
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOpUpVect(whoSender);
}

void OutOperation::slotOpMidSquare() {
	leScalarProd->setText("");
	
	bool ok;
	uint pot = (leExp->text()).toUInt(&ok);
	
	if(ok) {
		QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
		QString whoSender = clickButt->text();
		
		resetFieldsOutOpe();
		emit sigOpMidSquare(whoSender, pot);
	}
	else {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Attenzione");
		msgBox.setText("Il valore 'n' per la potenza deve essere un numero intero \u2265 0");
		msgBox.exec();
	}
}

void OutOperation::slotOpMidRect() {
	leExp->setText("");
	
	bool ok;
	double scalar = (leScalarProd->text()).toDouble(&ok);
	
	if(ok) {
		QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
		QString whoSender = clickButt->text();
		
		resetFieldsOutOpe();
		emit sigOpMidRect(whoSender, scalar);
	}
	else {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setWindowTitle("Attenzione");
		msgBox.setText("Il valore 's' dello scalare deve essere un numero reale");
		msgBox.exec();
	}
}

void OutOperation::slotOpLowSquare() {
	resetFieldsOutOpe();
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOpLowSquare(whoSender);
}

void OutOperation::slotOpLowRect() {
	resetFieldsOutOpe();
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOpLowRect(whoSender);
}
