TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -O3

SOURCES += main.cpp \
    solucion.cpp \
    algoritmogenetico.cpp \
    cec14_test_func.cpp

HEADERS += \
    solucion.h \
    pseudoaleatorio.h \
    algoritmogenetico.h \
    cec14_test_func.h
