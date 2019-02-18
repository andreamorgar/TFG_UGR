LFLAGS        = -Wl,-O1
####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		solucion.cpp \
		algoritmogenetico.cpp \
		cec14_test_func.cpp \
		islaag.cpp 
OBJECTS       = main.o \
		solucion.o \
		algoritmogenetico.o \
		cec14_test_func.o \
		islaag.o

DIST          = proyecto.pro solucion.h \
		pseudoaleatorio.h \
		algoritmogenetico.h \
		cec14_test_func.h \
		islaag.h main.cpp \
		solucion.cpp \
		algoritmogenetico.cpp \
		cec14_test_func.cpp \
		islaag.cpp


TARGET        = proyecto


all: proyecto
####### Build rules

$(TARGET):  $(OBJECTS)  
	g++ $(LFLAGS) -o $(TARGET) $(OBJECTS)

####### Compile

main.o: main.cpp algoritmogenetico.h \
		solucion.h \
		cec14_test_func.h \
		islaag.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

solucion.o: solucion.cpp solucion.h \
		cec14_test_func.h \
		pseudoaleatorio.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o solucion.o solucion.cpp

algoritmogenetico.o: algoritmogenetico.cpp algoritmogenetico.h \
		solucion.h \
		cec14_test_func.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o algoritmogenetico.o algoritmogenetico.cpp

cec14_test_func.o: cec14_test_func.cpp cec14_test_func.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cec14_test_func.o cec14_test_func.cpp

islaag.o: islaag.cpp islaag.h \
		solucion.h \
		cec14_test_func.h \
		algoritmogenetico.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o islaag.o islaag.cpp


####### Cleaning
clean:
	-rm $(OBJECTS)

mrproper: clean
	-rm ./proyecto



