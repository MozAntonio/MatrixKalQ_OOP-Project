/* InpSelect.cpp */
#include "InpSelect.h"
#include <QGridLayout>
#include <QString>
#include <QMessageBox>


InpSelect::InpSelect(QWidget* parent): QWidget(parent) {
	
	//Creo gli oggetti della finestra di scelta dell'input:
	//Quale matrice, eventuali dimensioni, ecc.
	
	//QPushButton:
	pbMatrix2 = new QPushButton("Matrice 2x2",this);
	pbMatrix3 = new QPushButton("Matrice 3x3",this);
	pbSqMatrix = new QPushButton("Matrice NxN",this);
	pbReMatrix = new QPushButton("Matrice NxM",this);
	pbVector = new QPushButton("Vettore",this);
	
	pbMatrix2->setToolTip("Seleziona una matrice qudrata 2x2");
	pbMatrix3->setToolTip("Seleziona una matrice qudrata 3x3");
	pbSqMatrix->setToolTip("Seleziona una matrice qudrata di N righe ed N colonne");
	pbReMatrix->setToolTip("Seleziona una matrice rettangolare di N righe ed M colonne");
	pbVector->setToolTip("Seleziona un vettore riga o colonna di lunghezza N");
	
	//QLineEdit:
	leSqMatrix = new QLineEdit("",this);
	leReMatrix_1 = new QLineEdit("",this);
	leReMatrix_2 = new QLineEdit("",this);
	leVector = new QLineEdit("",this);
	
	leSqMatrix->setPlaceholderText("N");
	leReMatrix_1->setPlaceholderText("N");
	leReMatrix_2->setPlaceholderText("M");
	leVector->setPlaceholderText("N");
	
	//QRadioButton:
	rbVectHor = new QRadioButton("Riga",this);
	rbVectVert = new QRadioButton("Colonna",this);
	
	//Default QRadioButton: "Vettore Riga"
	rbVectHor->setChecked(true);
	
	
	//Creo un layout a griglia per contenere tutti i widget appena inizializzati:
	QGridLayout* glInputSelFields = new QGridLayout(this);
	
	//Campi matrici quadrate:
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glInputSelFields->addWidget(pbMatrix2,0,0,1,2);
	glInputSelFields->addWidget(pbMatrix3,1,0,1,2);
	glInputSelFields->addWidget(pbSqMatrix,2,0,1,2);
	glInputSelFields->addWidget(leSqMatrix,2,2,1,1);
	
	//Campi matrici rettangolari:
	//addWidget( <nameWidget> , #row , #column , #row-span, #col-span)
	glInputSelFields->addWidget(pbReMatrix,3,0,1,2);
	glInputSelFields->addWidget(pbVector,4,0,1,2);
	glInputSelFields->addWidget(leReMatrix_1,3,2,1,1);
	glInputSelFields->addWidget(leReMatrix_2,3,3,1,1);
	glInputSelFields->addWidget(leVector,4,2,1,1);
	glInputSelFields->addWidget(rbVectHor,4,3,1,1);
	glInputSelFields->addWidget(rbVectVert,4,4,1,1);
	
	//Max-Size delle QLineEdit:
	//setMaximumSize(max-width , max-height)
	leSqMatrix->setMaximumSize(40,30);
	leReMatrix_1->setMaximumSize(40,30);
	leReMatrix_2->setMaximumSize(40,30);
	leVector->setMaximumSize(40,30);
	
	this->setLayout(glInputSelFields);
	
	
	//Connessioni per l'evento "clicked()" dei possibili tipi di input:
	connect(pbMatrix2,SIGNAL(clicked()),this,SLOT(slotClickedSquare()));
	connect(pbMatrix3,SIGNAL(clicked()),this,SLOT(slotClickedSquare()));
	connect(pbSqMatrix,SIGNAL(clicked()),this,SLOT(slotClickedSquare()));
	connect(pbReMatrix,SIGNAL(clicked()),this,SLOT(slotClickedRect()));
	connect(pbVector,SIGNAL(clicked()),this,SLOT(slotClickedRect()));
}

InpSelect::~InpSelect() {}

void InpSelect::resetFieldsInpSel() {
	leSqMatrix->setText("");
	leReMatrix_1->setText("");
	leReMatrix_2->setText("");
	leVector->setText("");
	rbVectHor->setChecked(true);
}

void InpSelect::blockForNewMatrix(uint dim1, uint dim2) {
	resetFieldsInpSel();
	
	if(dim1 == dim2) {
		if(dim1 > 3)
			leSqMatrix->setText(QString::number(dim1));		//o: QString::number(dim2)
	}
	else {
		if((dim1 != 1) && (dim2 != 1)) {
			leReMatrix_1->setText(QString::number(dim1));
			leReMatrix_2->setText(QString::number(dim2));
		}
		else {
			if(dim1 == 1) {
				leVector->setText(QString::number(dim2));
				//rbVectHor->setChecked(true);
			}
			else {
				leVector->setText(QString::number(dim1));
				rbVectVert->setChecked(true);
			}
		}
	}
}

void InpSelect::slotClickedSquare() {
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	
	if(whoSender=="Matrice 2x2") {
		resetFieldsInpSel();
		emit pbSquare(2);
	}
	else
		if(whoSender=="Matrice 3x3") {
			resetFieldsInpSel();
			emit pbSquare(3);
		}
		else {
			bool ok;
			uint dim = (leSqMatrix->text()).toUInt(&ok);
			
			if(ok && (dim > 3)) {
				QString aux = leSqMatrix->text();
				resetFieldsInpSel();
				leSqMatrix->setText(aux);
				emit pbSquare(dim);
			}
			else
				if(!ok || (dim < 2)) {
					QMessageBox msgBox;
					msgBox.setIcon(QMessageBox::Warning);
					msgBox.setWindowTitle("Attenzione");
					msgBox.setText("La dimensione della matrice quadrata deve essere un numero intero > 3");
					msgBox.exec();
				}
				else {	//caso: (dim==2 || dim==3)
					QMessageBox msgBox;
					msgBox.setIcon(QMessageBox::Question);
					msgBox.setWindowTitle("Suggerimento");
					msgBox.setText("Si desidera avere una dimensione uguale a 2 o a 3?\nSi consiglia di utilizzare una struttura 'Matrice 2x2' e/o 'Matrice 3x3'");
					msgBox.exec();
				}
		}
}

void InpSelect::slotClickedRect() {
	QPushButton* clickButt = qobject_cast<QPushButton*>(sender());
	QString whoSender = clickButt->text();
	
	if(whoSender=="Matrice NxM") {
		bool ok1;
		bool ok2;
		uint dim1 = (leReMatrix_1->text()).toUInt(&ok1);
		uint dim2 = (leReMatrix_2->text()).toUInt(&ok2);
		
		if(ok1 && ok2 && (dim1 > 1) && (dim2 > 1) && (dim1 != dim2)) {
			QString aux1 = leReMatrix_1->text();
			QString aux2 = leReMatrix_2->text();
			resetFieldsInpSel();
			leReMatrix_1->setText(aux1);
			leReMatrix_2->setText(aux2);
			emit pbRect(dim1, dim2);
		}
		else {
			if(!ok1 || !ok2 || (dim1 < 1) || (dim2 < 1)) {
				QMessageBox msgBox;
				msgBox.setIcon(QMessageBox::Warning);
				msgBox.setWindowTitle("Attenzione");
				msgBox.setText("Le dimensioni della matrice rettangolare devono essere numeri interi > 1");
				msgBox.exec();
			}
			else {
				if(dim1 != dim2) {		//caso: (dim1==1 || dim2==1)
					QMessageBox msgBox;
					msgBox.setIcon(QMessageBox::Question);
					msgBox.setWindowTitle("Suggerimento");
					msgBox.setText("Si desidera avere una dimensione uguale a 1?\nSi consiglia di utilizzare una struttura 'Vettore'");
					msgBox.exec();
				}
				else {					//caso: ((dim1==dim2) && (dim1 != 1) && (dim2 != 1))
					QMessageBox msgBox;
					msgBox.setIcon(QMessageBox::Question);
					msgBox.setWindowTitle("Suggerimento");
					msgBox.setText("Si desidera avere le due dimensioni uguali?\nSi consiglia di utilizzare una struttura 'Matrice NxN'");
					msgBox.exec();
				}
			}
		}
	}
	else {
		bool ok;
		uint dim = (leVector->text()).toUInt(&ok);
		
		if(ok && (dim > 1)) {
			QString aux = leVector->text();
			bool isHorizontal = rbVectHor->isChecked();
			
			resetFieldsInpSel();
			leVector->setText(aux);
			
			if(isHorizontal) {
				emit pbRect(1, dim);
			}
			else {
				rbVectVert->setChecked(true);
				emit pbRect(dim, 1);
			}
		}
		else {
			QMessageBox msgBox;
			msgBox.setIcon(QMessageBox::Warning);
			msgBox.setWindowTitle("Attenzione");
			msgBox.setText("La dimensione del vettore deve essere un numero intero > 1");
			msgBox.exec();
		}
	}
}
