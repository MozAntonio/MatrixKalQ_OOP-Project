/* OutResult.cpp */
#include "OutResult.h"
#include <QGridLayout>


OutResult::OutResult(QWidget* parent): QWidget(parent) {
	
	//Creo gli oggetti della finestra per mostrare il risultato in output, e le indicazioni per continuare:
	//Risultato come matrice, o risultato sottoforma di numero; e resettare allo stato iniziale la calcolatrice, o salvare l'output su file
	
	//QLabel:
	lResOutput = new QLabel("Matrice corrente:",this);
	
	//QPlainTextEdit:
	pteResOutput = new QPlainTextEdit("",this);
	pteResOutput->setReadOnly(true);
	
	pteResOutput->setLineWrapMode(QPlainTextEdit::NoWrap);		//per la scroll-bar orizzontale (se necessaria)
	//pteResOutput->setWordWrapMode(QTextOption::NoWrap);		//alternativa altrettanto valida alla precedente (sempre per la scroll-bar orizzontale)
	
	//QLineEdit:
	leOtherResOutput = new QLineEdit("",this);
	leOtherResOutput->setReadOnly(true);
	
	//QPushButton:
	pbRestart = new QPushButton("Reset",this);
	pbSaveFile = new QPushButton("Salva...",this);
	
	pbRestart->setToolTip("Riporta la calcolatrice allo stato iniziale");
	pbSaveFile->setToolTip("Salva la matrice corrente su file");
	
	//Creo un layout a griglia per contenere tutti i widget appena inizializzati:
	QGridLayout* glOutputResFields = new QGridLayout(this);
	
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glOutputResFields->addWidget(lResOutput,0,0,1,5);
	glOutputResFields->addWidget(pteResOutput,1,0,1,5);
	glOutputResFields->addWidget(leOtherResOutput,2,0,1,5);
	
	//Stretch tra la parte di output del risultato, e la parte per salvare/resettare:
	glOutputResFields->setColumnStretch(2,1);
	glOutputResFields->setRowStretch(3,1);
	
	//Strectch e min-height per la QPlaintText:
	glOutputResFields->setRowStretch(1,5);
	pteResOutput->setMinimumHeight(200);
	
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glOutputResFields->addWidget(pbRestart,4,3,1,1);
	glOutputResFields->addWidget(pbSaveFile,4,4,1,1);
	
	this->setLayout(glOutputResFields);
	
	
	//Connessioni per l'evento "clicked()" dei bottoni per il "reset" e per "salvare il risultato su file":
	connect(pbRestart,SIGNAL(clicked()),this,SLOT(slotClickedResetOutPB()));
	connect(pbSaveFile,SIGNAL(clicked()),this,SLOT(slotClickedSaveFilePB()));
}

OutResult::~OutResult() {}

void OutResult::resetFieldsOutRes() {
	pteResOutput->setPlainText("");
	leOtherResOutput->setText("");
}

void OutResult::setBigResult(const QString& bRis) {
	pteResOutput->setPlainText(bRis);
}

void OutResult::setSmallResult(const QString& sRis) {
	leOtherResOutput->setText(sRis);
}

void OutResult::slotClickedResetOutPB() {
	emit sigResetOutPB("");
}

void OutResult::slotClickedSaveFilePB() {
	emit sigSaveFilePB(pteResOutput->toPlainText());
}
