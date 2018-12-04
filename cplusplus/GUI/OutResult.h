/* OutResult.h */
#ifndef OUTRESULT_H
#define OUTRESULT_H

#include <QWidget>
#include <QLabel>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QString>


class OutResult: public QWidget {
		Q_OBJECT
		
	private:
	//Campi dati
		//QLabel:
		QLabel* lResOutput;
		
		//QPlainTextEdit:
		QPlainTextEdit* pteResOutput;
		
		//QLineEdit:
		QLineEdit* leOtherResOutput;
		
		//QPushButton:
		QPushButton* pbRestart;
		QPushButton* pbSaveFile;
		
	public:
	//Costruttore & Distruttore:
		explicit OutResult(QWidget* parent =0);
		~OutResult();
		
	//Setter pubblici:
		void resetFieldsOutRes();
		void setBigResult(const QString&);
		void setSmallResult(const QString&);
		
	signals:
	//Segnali:
		void sigResetOutPB(const QString&);
		void sigSaveFilePB(const QString&);
		
	public slots:
	//Slot pubblici:
		void slotClickedResetOutPB();
		void slotClickedSaveFilePB();
};


#endif
