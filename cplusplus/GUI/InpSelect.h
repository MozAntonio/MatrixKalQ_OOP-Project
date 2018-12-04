/* InpSelect.h */
#ifndef INPSELECT_H
#define INPSELECT_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>


class InpSelect: public QWidget {
		Q_OBJECT
	
	private:
	//Campi dati
		//QPushButton:
		QPushButton* pbMatrix2;
		QPushButton* pbMatrix3;
		QPushButton* pbSqMatrix;
		QPushButton* pbReMatrix;
		QPushButton* pbVector;
		
		//QLineEdit:
		QLineEdit* leSqMatrix;
		QLineEdit* leReMatrix_1;
		QLineEdit* leReMatrix_2;
		QLineEdit* leVector;
		
		//QRadioButton:
		QRadioButton* rbVectHor;
		QRadioButton* rbVectVert;
		
	public:
	//Costruttore & Distruttore:
		explicit InpSelect(QWidget* parent =0);
		~InpSelect();
		
	//Setter pubblici:
		void resetFieldsInpSel();
		void blockForNewMatrix(uint, uint);
		
	signals:
	//Segnali:
		void pbSquare(uint);
		void pbRect(uint, uint);
		
	public slots:
	//Slot pubblici:
		void slotClickedSquare();
		void slotClickedRect();
};


#endif
