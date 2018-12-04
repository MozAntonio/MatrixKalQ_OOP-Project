#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T03:09:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MatrixKalQ
TEMPLATE = app


HEADERS += \
	./Core/MatrixBase.h \
	./Core/DenseMatrix.h \
	./Core/SquareMatrix.h \
	./Core/Matrix2.h \
	./Core/Matrix3.h \
	./Core/RectMatrix.h \
	./Core/Vect.h \
	./Core/VectHor.h \
	./Core/VectVert.h \
	./GUI/InpInsert.h \
	./GUI/InpSelect.h \
	./GUI/OutOperation.h \
	./GUI/OutResult.h \
	./GUI/LayoutManager.h \
	./GUI/LogicManager.h \
	./GUI/cuteMatrixKalk.h
	
	
SOURCES += \
	./Core/MatrixBase.cpp \
	./Core/DenseMatrix.cpp \
	./Core/SquareMatrix.cpp \
	./Core/Matrix2.cpp \
	./Core/Matrix3.cpp \
	./Core/RectMatrix.cpp \
	./Core/Vect.cpp \
	./Core/VectHor.cpp \
	./Core/VectVert.cpp \
	./GUI/InpInsert.cpp \
	./GUI/InpSelect.cpp \
	./GUI/OutOperation.cpp \
	./GUI/OutResult.cpp \
	./GUI/LayoutManager.cpp \
	./GUI/LogicManager.cpp \
	./GUI/cuteMatrixKalk.cpp \
	./main.cpp
	
	
RESOURCES += \
	./MatrixKalQ.qrc
	
	