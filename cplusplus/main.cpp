/* Main.cpp */
#include "./GUI/cuteMatrixKalk.h"
#include <QApplication>


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	cuteMatrixKalk MatrixKalQ;
	MatrixKalQ.avvia();
	
	return app.exec();
}
