/* InpInsert.cpp */
#include "InpInsert.h"
#include <QGridLayout>


InpInsert::InpInsert(QWidget* parent): QWidget(parent) {
	
	//Creo gli oggetti della finestra di inserimento dell'input, e le indicazioni per continuare:
	//Inserimento manuale, random, o da file; e resettare allo stato iniziale la calcolatrice, o proseguire
	
	//QLabel:
	lMatrixInput = new QLabel("Inserisci gli elementi:",this);
	
	//QPlainTextEdit:
	pteMatrixInput = new QPlainTextEdit("",this);
	pteMatrixInput->setToolTip("Gli elementi si considerano inseriti per riga;\nViene accettata la separazione con spazio, tabulazione, e invio;\nEventuali elementi in eccesso verranno ignorati.");
	
	pteMatrixInput->setLineWrapMode(QPlainTextEdit::NoWrap);	//per la scroll-bar orizzontale (se necessaria)
	//pteMatrixInput->setWordWrapMode(QTextOption::NoWrap);		//alternativa altrettanto valida alla precedente (sempre per la scroll-bar orizzontale)
	
	//QPushButton:
	pbRandom = new QPushButton("Random...",this);
	pbFile = new QPushButton("Carica...",this);
	pbRestart = new QPushButton("Reset",this);
	pbGoOn = new QPushButton("Prosegui",this);
	
	pbRandom->setToolTip("Propone un insieme di numeri casuali per la matrice\n(numeri interi compresi tra -100 e 100)");
	pbFile->setToolTip("Carica la matrice da file");
	pbRestart->setToolTip("Riporta la calcolatrice allo stato iniziale");
	pbGoOn->setToolTip("Prosegui con la matrice inserita");
	
	//Creo un layout a griglia per contenere tutti i widget appena inizializzati:
	QGridLayout* glInputInsFields = new QGridLayout(this);
	
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glInputInsFields->addWidget(lMatrixInput,0,0,1,5);
	glInputInsFields->addWidget(pteMatrixInput,1,0,1,5);
	glInputInsFields->addWidget(pbRandom,2,0,1,1);
	glInputInsFields->addWidget(pbFile,2,1,1,1);
	
	//Stretch tra la parte di scelta della modalità di input, e la parte per proseguire/resettare:
	glInputInsFields->setColumnStretch(2,1);
	glInputInsFields->setRowStretch(3,1);
	
	//Strectch e min-height per la QPlaintText:
	glInputInsFields->setRowStretch(1,5);
	pteMatrixInput->setMinimumHeight(200);
	
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glInputInsFields->addWidget(pbRestart,4,3,1,1);
	glInputInsFields->addWidget(pbGoOn,4,4,1,1);
	
	this->setLayout(glInputInsFields);
	
	
	//Connessioni per l'evento "clicked()" dei bottoni di inserimento alternativo di input, e di navigazione:
	connect(pbRandom,SIGNAL(clicked()),this,SLOT(slotClickedOtherInpPB()));
	connect(pbFile,SIGNAL(clicked()),this,SLOT(slotClickedOtherInpPB()));
	connect(pbRestart,SIGNAL(clicked()),this,SLOT(slotClickedResetInpPB()));
	connect(pbGoOn,SIGNAL(clicked()),this,SLOT(slotClickedGoOnPB()));
}

InpInsert::~InpInsert() {}

void InpInsert::resetFieldsInpIns() {
	lMatrixInput->setText("Inserisci gli elementi:");
	pteMatrixInput->setPlainText("");
}

void InpInsert::setFocusOnInputArea() const {
	pteMatrixInput->setFocus();
}

void InpInsert::setInputArea(const QString& input) {
	pteMatrixInput->setPlainText(input);
}

void InpInsert::emptyForNewMatrix(uint dim1, uint dim2) {
	resetFieldsInpIns();
	lMatrixInput->setText("Inserire gli elementi del secondo operando: " + QString::number(dim1) + "x" + QString::number(dim2));
}

void InpInsert::slotClickedOtherInpPB() {
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	emit sigOtherInputPB(whoSender);
}

void InpInsert::slotClickedResetInpPB() {
	emit sigResetInpPB("");
}

void InpInsert::slotClickedGoOnPB() {
	emit sigGoOnPB(pteMatrixInput->toPlainText());
}
