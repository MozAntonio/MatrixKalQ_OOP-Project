/* LayoutManager.cpp */
#include "LayoutManager.h"
#include <QHBoxLayout>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>


LayoutManager::LayoutManager(QWidget* parent): QWidget(parent) {
	//Imposto il titolo e l'icona della GUI:
	this->setWindowTitle("MatrixKalQ - Calcolatrice per Matrici");
	this->setWindowIcon(QIcon(":/MatrixKalkQ_ico_64x64.png"));
	
	//Creo la finestra principale della QKalk:
	QHBoxLayout* windowKalk = new QHBoxLayout(this);
	
	//Creo i widget per la finestra di input e di output:
	inpSelectWind = new InpSelect(this);
	inpInsertWind = new InpInsert(this);
	
	inpInsertWind->setEnabled(false);	//all'inizio è abilitata solamente l'input per la scelta del tipo di matrice
	
	outOperWind = new OutOperation(this);
	outResWind = new OutResult(this);
	
	//Inizializzo la finestra con la parte relativa all'input:
	windowKalk->insertWidget(0,inpSelectWind,1);
	windowKalk->insertWidget(1,inpInsertWind,2);
	
	//Preparo la finestra di output, e all'inizio la nascondo:
	windowKalk->insertWidget(0,outOperWind,1);
	windowKalk->insertWidget(1,outResWind,2);
	outOperWind->hide();
	outResWind->hide();
	
	//Imposto il layout per la finestra principale:
	this->setLayout(windowKalk);
	
	
	//Connessioni per i "SIGNAL" e gli "SLOT" relativi all'input:
	connect(inpSelectWind,SIGNAL(pbSquare(uint)),this,SLOT(slotSelectSquare(uint)));
	connect(inpSelectWind,SIGNAL(pbRect(uint, uint)),this,SLOT(slotSelectRect(uint, uint)));
	
	connect(inpInsertWind,SIGNAL(sigOtherInputPB(const QString&)),this,SLOT(slotOtherInput(const QString&)));
	connect(inpInsertWind,SIGNAL(sigGoOnPB(const QString&)),this,SLOT(slotGoOn(const QString&)));
	
	//Connessioni per i "SIGNAL" e gli "SLOT" relativi sia all'input sia all'output:
	connect(inpInsertWind,SIGNAL(sigResetInpPB(const QString&)),this,SLOT(slotLayoutReset(const QString&)));
	connect(outResWind,SIGNAL(sigResetOutPB(const QString&)),this,SLOT(slotLayoutReset(const QString&)));
	
	//Connessioni per i "SIGNAL" e gli "SLOT" relativi all'output:
	connect(outOperWind,SIGNAL(sigOpUpSquare(const QString&)),this,SLOT(slotSelectUnOpSquare(const QString&)));
	connect(outOperWind,SIGNAL(sigOpUpRect(const QString&)),this,SLOT(slotSelectUnOpRect(const QString&)));
	connect(outOperWind,SIGNAL(sigOpUpVect(const QString&)),this,SLOT(slotSelectUnOpVect(const QString&)));
	connect(outOperWind,SIGNAL(sigOpMidSquare(const QString&, uint)),this,SLOT(slotSelectSBiOpSquare(const QString&, uint)));
	connect(outOperWind,SIGNAL(sigOpMidRect(const QString&, qreal)),this,SLOT(slotSelectSBiOpRect(const QString&, qreal)));
	connect(outOperWind,SIGNAL(sigOpLowSquare(const QString&)),this,SLOT(slotSelectBiOpSquare(const QString&)));
	connect(outOperWind,SIGNAL(sigOpLowRect(const QString&)),this,SLOT(slotSelectBiOpRect(const QString&)));
	
	connect(outResWind,SIGNAL(sigSaveFilePB(const QString&)),this,SLOT(slotSaveFile(const QString&)));
}

LayoutManager::~LayoutManager() {}

void LayoutManager::slotSelectSquare(uint dim) {
	numRows = numCols = dim;
	inpSelectWind->setEnabled(false);
	inpInsertWind->setEnabled(true);
	
	inpInsertWind->setFocusOnInputArea();
}

void LayoutManager::slotSelectRect(uint dim1, uint dim2) {
	numRows = dim1;
	numCols = dim2;
	inpSelectWind->setEnabled(false);
	inpInsertWind->setEnabled(true);
	
	inpInsertWind->setFocusOnInputArea();
}

void LayoutManager::slotOtherInput(const QString& whoSender) {
	if(whoSender=="Carica...") {
		QString fileName = QFileDialog::getOpenFileName(this, "Apri file", "", "File di testo (*.txt);;Tutti i file (*)");
		
		if(fileName.isEmpty()) {
			inpInsertWind->setFocusOnInputArea();
			return;
		}
		else {
			QFile file(fileName);
			
			if(!(file.open(QIODevice::ReadOnly))) {
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Critical);
				msgBox.setWindowTitle("Errore");
				msgBox.setText("Problema con l'apertura del file:\n" + file.errorString());
				msgBox.exec();
				
				inpInsertWind->setFocusOnInputArea();
				return;
			}
			
			QDataStream in(&file);
			in.setVersion(QDataStream::Qt_4_5);
			inpInsertWind->setInputArea("");		//svuoto il contenuto per il caricamento
			
			QString inputFile;							//stringa d'appoggio per il caricamento del contenuto
			in >> inputFile;							//riempio la stringa con il contenuto dello stream
			
			file.close();
			
			if(inputFile.isEmpty()) {
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Information);
				msgBox.setWindowTitle("Informazione");
				msgBox.setText("Il file indicato è vuoto.\nRiprovare con un altro file.");
				msgBox.exec();
				
				inpInsertWind->setFocusOnInputArea();
				return;
			}
			
			inpInsertWind->setInputArea(inputFile);		//Tutto ok: Carico la matrice appena letta dal file sull'area di input
			inpInsertWind->setFocusOnInputArea();		//Sposto il focus sull'area di input
		}
	}
	else {	//Caso: << whoSender=="Random..." >>
		emit random(numRows, numCols, -100, 100, true);
	}
}

void LayoutManager::slotGoOn(const QString& matrix) {
	if(numRows==numCols)
		emit newSquare(matrix, numRows);	//o: newSquare(matrix, numCols);
	else
		emit newRect(matrix, numRows, numCols);
}

void LayoutManager::slotLayoutReset(const QString& what) {
	//Reset dei campi della GUI:
	inpSelectWind->resetFieldsInpSel();
	inpInsertWind->resetFieldsInpIns();
	outOperWind->resetFieldsOutOpe();
	outResWind->resetFieldsOutRes();
	
	//Schermata iniziale (input):
	//Prima "hide()" e poi "show()"
	outOperWind->hide();
	outResWind->hide();
	inpSelectWind->show();
	inpInsertWind->show();
	inpSelectWind->setEnabled(true);
	inpInsertWind->setEnabled(false);
	
	//Invio segnale per reset della parte logica:
	emit reset();
	
	//Mostro eventuale messaggio critico di errore:
	if(!(what.isEmpty())) {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowTitle("Errore critico");
		msgBox.setText(what);
		msgBox.exec();
	}
}

void LayoutManager::slotSelectUnOpSquare(const QString& operand) {
	emit unOpSquare(operand);		//det, trace, adj, isInv, inv
}

void LayoutManager::slotSelectUnOpRect(const QString& operand) {
	if(operand=="A\u1D40") {	//se è stata richiesta una "Trasposta": inverto #righe e #colonne
		uint temp = numRows;
		numRows = numCols;
		numCols = temp;
	}
	
	emit unOpAll(operand);			//rank, trans
}

void LayoutManager::slotSelectUnOpVect(const QString& operand) {
	emit unOpVect(operand);			//rev
}

void LayoutManager::slotSelectSBiOpRect(const QString& operand, qreal scalar) {
	emit sBiOpAll(operand, scalar);	//scalarProd
}

void LayoutManager::slotSelectSBiOpSquare(const QString& operand, uint pot) {
	emit sBiOpSquare(operand, pot);	//exp
}

void LayoutManager::slotSelectBiOpRect(const QString& operand) {
	//Prima "hide()" e poi "show()":
	outOperWind->hide();
	outResWind->hide();
	inpSelectWind->show();
	inpInsertWind->show();
	
	inpSelectWind->blockForNewMatrix(numRows, numCols);
	inpInsertWind->emptyForNewMatrix(numRows, numCols);
	
	inpInsertWind->setFocusOnInputArea();
	
	emit biOpAll(operand, "biOpAll");			//sum, diff
}

void LayoutManager::slotSelectBiOpSquare(const QString& operand) {
	//Prima "hide()" e poi "show()":
	outOperWind->hide();
	outResWind->hide();
	inpSelectWind->show();
	inpInsertWind->show();
	
	inpSelectWind->blockForNewMatrix(numRows, numRows);		//o: numCols
	inpInsertWind->emptyForNewMatrix(numRows, numRows);		//o: numCols
	
	inpInsertWind->setFocusOnInputArea();
	
	emit biOpSquare(operand, "biOpSquare");		//prod
}

void LayoutManager::slotSaveFile(const QString& matrixToSave) {
	QString fileName = QFileDialog::getSaveFileName(this, "Salva Matrice su file", "", "File di testo (*.txt);;Tutti i file (*)");
	
	if(fileName.isEmpty()) {
		return;
	}
	else {
		QFile file(fileName);
		
		if(!(file.open(QIODevice::WriteOnly))) {
			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Critical);
			msgBox.setWindowTitle("Errore");
			msgBox.setText("Problema con l'apertura del file appena creato:\n" + file.errorString());
			msgBox.exec();
			return;
		}
		
		QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << matrixToSave;
		
		file.close();
	}
}

void LayoutManager::slotDoneSquare(const QString& bigRis, const QString& smallRis) {
	//Prima "hide()" e poi "show()":
	inpSelectWind->hide();
	inpInsertWind->hide();
	outOperWind->show();
	outResWind->show();
	
	outOperWind->setOpSquare();
	outResWind->setBigResult(bigRis);
	outResWind->setSmallResult(smallRis);
}

void LayoutManager::slotDoneRect(const QString& bigRis, const QString& smallRis) {
	//Prima "hide()" e poi "show()":
	inpSelectWind->hide();
	inpInsertWind->hide();
	outOperWind->show();
	outResWind->show();
	
	outOperWind->setOpRect();
	outResWind->setBigResult(bigRis);
	outResWind->setSmallResult(smallRis);
}

void LayoutManager::slotDoneVect(const QString& bigRis, const QString& smallRis) {
	//Prima "hide()" e poi "show()":
	inpSelectWind->hide();
	inpInsertWind->hide();
	outOperWind->show();
	outResWind->show();
	
	outOperWind->setOpVect();
	outResWind->setBigResult(bigRis);
	outResWind->setSmallResult(smallRis);
}

void LayoutManager::slotProblem(const QString& error) {
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setWindowTitle("Attenzione");
	msgBox.setText(error.left(1).toUpper() + error.mid(1));
	msgBox.exec();
	
	inpInsertWind->setFocusOnInputArea();
}
