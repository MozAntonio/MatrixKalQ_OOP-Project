/* InpInsert.h */
#ifndef INPINSERT_H
#define INPINSERT_H

#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QString>


class InpInsert: public QWidget {
		Q_OBJECT
		
	private:
	//Campi dati
		//QLabel:
		QLabel* lMatrixInput;
		
		//QPlainTextEdit:
		QPlainTextEdit* pteMatrixInput;
		
		//QPushButton:
		QPushButton* pbRandom;
		QPushButton* pbFile;
		QPushButton* pbRestart;
		QPushButton* pbGoOn;
		
	public:
	//Costruttore & Distruttore:
		explicit InpInsert(QWidget* parent =0);
		~InpInsert();
		
	//Setter pubblici:
		void resetFieldsInpIns();
		void setFocusOnInputArea() const;
		void setInputArea(const QString&);
		void emptyForNewMatrix(uint, uint);
		
	signals:
	//Segnali:
		void sigOtherInputPB(const QString&);
		void sigResetInpPB(const QString&);
		void sigGoOnPB(const QString&);
		
	public slots:
	//Slot pubblici:
		void slotClickedOtherInpPB();
		void slotClickedResetInpPB();
		void slotClickedGoOnPB();
};


#endif
