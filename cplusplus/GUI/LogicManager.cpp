/* LogicManager.cpp */
#include "LogicManager.h"
#include "../Core/DenseMatrix.h"
#include "../Core/SquareMatrix.h"
#include "../Core/Matrix3.h"
#include "../Core/Matrix2.h"
#include "../Core/RectMatrix.h"
#include "../Core/Vect.h"
#include "../Core/VectHor.h"
#include "../Core/VectVert.h"
#include <sstream>
#include <iostream>
#include <stdexcept>


LogicManager::LogicManager(QObject* parent): QObject(parent), ris(0), operand2(0), biOp(""), whoS("") {
	
	//Connetto alcuni miei signal con alcuni miei slot (per operaz binarie)
	QObject::connect(this,SIGNAL(biOpAll(const QString&,const QString&)),this,SLOT(slotBiOpAll(const QString&,const QString&)));
	QObject::connect(this,SIGNAL(biOpSquare(const QString&,const QString&)),this,SLOT(slotBiOpSquare(const QString&,const QString&)));
}

LogicManager::~LogicManager() {
	if(ris)
		delete ris;
	if(operand2)
		delete operand2;
}

void LogicManager::scrivi(MatrixBase* pm, const QString& qsInput) {
	std::string stdInput = qsInput.toStdString();
	std::istringstream iss(stdInput);
	if(pm)
		pm->load(iss);
	return;
}

QString LogicManager::leggi(MatrixBase* pm) {
	std::ostringstream oss;
	if(pm)
		pm->print(oss);
	return QString::fromStdString(oss.str());
}

void LogicManager::slotNewSquare(const QString& s, uint n) {
	
	MatrixBase* newM = 0;
	
	switch(n)
	{
		case 2:
			newM = new Matrix2();
		break;
		
		case 3:
			newM = new Matrix3();
		break;
		
		default:
			newM = new SquareMatrix(n);
		break;
	}
	
	//popola la matrice puntata da newM con i dati contenuti in s
	try { scrivi(newM, s); }
	catch(const std::invalid_argument &e){
		//if(newM)
			delete newM;
		emit problem(e.what());
		return;
	}
	
	//verifico se è il primo o l'eventuale secondo operando
	if(!ris) { //è il primo
		ris = newM;
		//newM=0;
		QString ss = leggi(ris); //carico la nuova stringa da reinviare
		emit doneSquare(ss, "");
	}
	else { //è il secondo
		operand2 = newM;
		//newM=0;
		if(whoS=="biOpAll")
			emit biOpAll(biOp, whoS);
		else if(whoS=="biOpSquare")
			emit biOpSquare(biOp, whoS);
		else {
			delete operand2;
			operand2=0;
			biOp="";
			whoS="";
			emit doneSquare(leggi(ris), ""); //chiede alla gui di tornare alla schermata delle operaz
			emit problem("Operatore non riconosciuto, secondo operando cancellato");
		}
	}
	//return;
}

void LogicManager::slotNewRect(const QString& s, uint rig, uint col) {
	
	MatrixBase* newM = 0;
	
	if(rig==1)
		newM = new VectHor(col);
	else if(col==1)
			newM = new VectVert(rig);
		else
			newM = new RectMatrix(rig,col);
	
	//popola la matrice puntata da newM con i dati contenuti in s
	try { scrivi(newM, s); }
	catch(const std::invalid_argument& e){
		//if(newM)
			delete newM;
		emit problem(e.what());
		return;
	}
	
	//verifico se è il primo o l'eventuale secondo operando
	if(!ris) { //è il primo
		ris = newM;
		//newM=0;
		QString ss = leggi(ris); //carico la nuova stringa da reinviare
		if(rig==1 || col==1)
			emit doneVect(ss, "");
		else
			emit doneRect(ss, "");
	}
	else { //è il secondo
		operand2 = newM;
		//newM=0;
		if(whoS=="biOpAll")
			emit biOpAll(biOp, whoS);
		else if(whoS=="biOpSquare")
			emit biOpSquare(biOp, whoS);
		else {
			delete operand2;
			operand2=0;
			biOp="";
			whoS="";
			emit doneSquare(leggi(ris), ""); //chiede alla gui di tornare alla schermata delle operaz
			emit problem("Operatore non riconosciuto, secondo operando cancellato");
		}
	}
	//return;
}

void LogicManager::slotUnOpAll(const QString& op) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	MatrixBase* tempRis = 0;
	QString info="";
	
	if(op == "\u03C1(A)")
		info = "Il rango è: " + QString::number(ris->rank());
	else if(op == "A\u1D40")
		tempRis = ris->trans_p();
	else {
		emit problem("Operatore non riconosciuto");
		return;
	}
	
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	if(dynamic_cast<Vect*>(ris))
		emit doneVect(s, info);
	else
		if(dynamic_cast<RectMatrix*>(ris))
			emit doneRect(s, info);
		else
			if(dynamic_cast<SquareMatrix*>(ris))
				emit doneSquare(s, info);
			else //l'operaz richiesta ha prodotto un ris inatteso (need reset)
				emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
	
	//return;
}

void LogicManager::slotUnOpSquare(const QString& op) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	SquareMatrix* squareRis = dynamic_cast<SquareMatrix*>(ris);
	
	if(!squareRis) {
		emit problem("Operazione permessa solo su Matrici quadrate (e suoi sottotipi)");
		return;
	}
	
	SquareMatrix* tempRis = 0;
	QString info = "";
	
	if(op == "A\u207B\u00B9 ?") {
		if(squareRis->isInvertible())
			info = "La matrice è invertibile";
		else
			info = "La matrice non è invertibile";
	}
	else
		if(op == "det(A)")
			info = "Il determinante è: " + QString::number(squareRis->det());
	else
		if(op == "tr(A)")
			info = "La traccia vale: " + QString::number(squareRis->trace());
	else
		if(op == "A\u207B\u00B9") {
			try { tempRis = squareRis->inv_p(); }
			catch(const std::domain_error& e) {
				emit problem(e.what());
				return;
			}
		}
	else
		if(op == "adj(A)")
			tempRis = squareRis->adj_p();
	else {
		emit problem("Operatore non riconosciuto");
		return;
	}
	
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
		//squareRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	emit doneSquare(s, info);
	//return;
}

void LogicManager::slotUnOpVect(const QString& op) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	Vect* vectRis = dynamic_cast<Vect*>(ris);
	
	if(!vectRis) {
		emit problem("Operazione permessa solo su Vettore (e suoi sottotipi)");
		return;
	}
	
	Vect* tempRis = 0;
	
	if(op == "rev(V)")
		tempRis = vectRis->rev_p();
	else {
		emit problem("Operatore non riconosciuto");
		return;
	}
	
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
		//vectRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	emit doneVect(s, "");
	//return;
}

void LogicManager::slotSBiOpAll(const QString& op, qreal scalar) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	MatrixBase* tempRis = 0;
	
	if(op == "s*A")
		tempRis = ris->sProd_p(scalar);
	else {
		emit problem("Operatore non riconosciuto");
		return;
	}
	
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	if(dynamic_cast<Vect*>(ris))
		emit doneVect(s, "");
	else
		if(dynamic_cast<RectMatrix*>(ris))
			emit doneRect(s, "");
		else
			if(dynamic_cast<SquareMatrix*>(ris))
				emit doneSquare(s, "");
			else //l'operaz richiesta ha prodotto un ris inatteso (need reset)
				emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
	
	//return;
}

void LogicManager::slotSBiOpSquare(const QString& op, uint pot) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	SquareMatrix* squareRis = dynamic_cast<SquareMatrix*>(ris);
	
	if(!squareRis) {
		emit problem("Operazione permessa solo su Matrici quadrate (e suoi sottotipi)");
		return;
	}
	
	SquareMatrix* tempRis = 0;
	
	if(op == "A\u207F")
		tempRis = squareRis->exp_p(pot);
	else {
		emit problem("Operatore non riconosciuto");
		return;
	}
	
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
		//squareRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	emit doneSquare(s, "");
	//return;
}

void LogicManager::slotBiOpAll(const QString& op, const QString& who) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	//se è la prima volta che arrivo, setto l'op binario
	if(biOp.isEmpty()) { // ||!operand2
		biOp = op;
		whoS = who;
		return;
	}
	//else //è la seconda volta che arrivo, il secondo operando è in operand2
	
	MatrixBase* tempRis = 0;
	bool operatorNotFound = false; //true sse l'operatore non è valido
	QString exceptionMsg = "";
	
	if(op == "+") {
		try { tempRis = ris->sum_p(operand2); }
		catch(const std::invalid_argument& e) { exceptionMsg = e.what(); }
	}
	else
		if(op == "-") {
		try { tempRis = ris->dif_p(operand2); }
		catch(const std::invalid_argument& e) { exceptionMsg = e.what(); }
	}
	else
		operatorNotFound = true;
	
	//a prescindere resetto la roba del secondo operando
	//if(operand2)
		delete operand2;
	operand2=0;
	biOp="";
	whoS="";
	
	//se l'operaz è andata a buon fine, imposto il nuovo risultato
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	//emetto un segnale che farà cambiare schermata alla gui
	if(dynamic_cast<Vect*>(ris))
		emit doneVect(s, "");
	else
		if(dynamic_cast<RectMatrix*>(ris))
			emit doneRect(s, "");
		else
			if(dynamic_cast<SquareMatrix*>(ris))
				emit doneSquare(s, "");
			else { //l'operaz richiesta ha prodotto un ris inatteso (need reset)
				operatorNotFound=false; //non è più un problema, quello più grave ha la precedenza
				emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
			}
	
	//se si era verificato un problema
	if(operatorNotFound)
		emit problem("Operatore non riconosciuto, secondo operando cancellato");
	//else
	if(!exceptionMsg.isEmpty())
		emit problem(exceptionMsg + ", secondo operando cancellato");
	
	//return;
}

void LogicManager::slotBiOpSquare(const QString& op, const QString& who) {
	
	if(!ris) { //operaz invocata su operando nullo (need reset)
		emit needReset("A causa di un grave errore interno, la calcolatrice è stata riavviata");
		return;
	}
	
	//se è la prima volta che arrivo, setto l'op binario
	if(biOp.isEmpty()) { // ||!operand2
		biOp = op;
		whoS = who;
		return;
	}
	//else //è la seconda volta che arrivo, il secondo operando è in operand2
	
	SquareMatrix* squareRis = dynamic_cast<SquareMatrix*>(ris);
	SquareMatrix* squareOperand2 = dynamic_cast<SquareMatrix*>(operand2);
	SquareMatrix* tempRis = 0;
	bool operandNotValid = false; //true sse gli operandi non sono valide per questa operaz
	bool operatorNotFound = false; //true sse l'operatore non è valido
	QString exceptionMsg = "";
	
	if(!squareRis || !squareOperand2) {
		operandNotValid = true;
	}
	else {
		if(op == "\u00D7") {
			try { tempRis = squareRis->prod_p(squareOperand2); }
			catch(const std::invalid_argument& e) { exceptionMsg = e.what(); }
		}
		else
			operatorNotFound = true;
	}
	
	//a prescindere resetto la roba del secondo operando
	//if(operand2)
		delete operand2;
	operand2=0;
	biOp="";
	whoS="";
	
	//se l'operaz è andata a buon fine, imposto il nuovo risultato
	if(tempRis) {
		delete ris;
		ris = tempRis;
		//tempRis=0;
		//squareRis=0;
	}
	
	//crea un stringa contenente tutti i dati della matrice puntata da ris
	QString s = leggi(ris);
	
	//emetto un segnale che farà cambiare schermata alla gui
	emit doneSquare(s, "");
	
	//se si era verificato un errore lo comunico
	if(operandNotValid)
		emit problem("Operazione permessa solo tra Matrici quadrate (e tra suoi sottotipi), secondo operando cancellato");
	else if(operatorNotFound)
			emit problem("Operatore non riconosciuto, secondo operando cancellato");
	//else
	if(!exceptionMsg.isEmpty())
		emit problem(exceptionMsg + ", secondo operando cancellato");
	
	//return;
}

void LogicManager::slotRandom(uint rig, uint col, int from, int to, bool interi) {
	
	DenseMatrix* newM = 0;
	
	if(rig==col) { //quadrate
		switch(rig)
		{
			case 2:
				newM = new Matrix2();
			break;
			
			case 3:
				newM = new Matrix3();
			break;
			
			default:
				newM = new SquareMatrix(rig);
			break;
		}
		
		if(interi)
			newM->setRandInt(from, to);
		else
			newM->setRandReal(from, to);
		
		slotNewSquare(leggi(newM),rig);
	}
	else { //rettangolari e vettori
		if(rig==1)
			newM = new VectHor(col);
		else if(col==1)
				newM = new VectVert(rig);
			else
				newM = new RectMatrix(rig,col);
		
		if(interi)
			newM->setRandInt(from, to);
		else
			newM->setRandReal(from, to);
		
		slotNewRect(leggi(newM),rig,col);
	}
}

void LogicManager::slotLogicReset() {
	
	if(ris)
		delete ris;
	
	if(operand2)
		delete operand2;
	
	ris=0;
	operand2=0;
	biOp="";
	whoS="";
	
	//return;
}
