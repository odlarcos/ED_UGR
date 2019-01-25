#Macros para parametrizacion de directorios

BIN= bin
SRC= src
INC= include
OBJ= obj
LIB= lib

CXX= g++
AR= ar
LDFLAGS= -L
LDLIBS= -lclinvar
CXXFLAGS = -pedantic -std=c++11 -g  -I $(INC)

all: $(BIN)/main

# ************ Generación de ejecutables ******************

$(BIN)/main: $(LIB)/libclinvar.a $(OBJ)/main.o
	$(CXX) $(LDFLAGS)$(LIB) -o $(BIN)/main $(OBJ)/main.o $(LDLIBS)

# ************ Generación de librerías ******************

$(LIB)/libclinvar.a: $(OBJ)/clinvar.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o
	$(AR) rvs $(LIB)/libclinvar.a $(OBJ)/clinvar.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o

# ************ Compilación de módulos ******************

$(OBJ)/clinvar.o: $(SRC)/clinvar.cpp $(INC)/clinvar.h $(INC)/mutacion.h
	$(CXX) -c $(CXXFLAGS) $(SRC)/clinvar.cpp -o $(OBJ)/clinvar.o

$(OBJ)/mutacion.o: $(SRC)/mutacion.cpp $(INC)/mutacion.h $(INC)/enfermedad.h
		$(CXX) -c $(CXXFLAGS) $(SRC)/mutacion.cpp -o $(OBJ)/mutacion.o

$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp $(INC)/enfermedad.h
		$(CXX) -c $(CXXFLAGS) $(SRC)/enfermedad.cpp -o $(OBJ)/enfermedad.o

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/clinvar.h
		$(CXX) -c $(CXXFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ******************
clean:
	-rm $(OBJ)/*.o $(LIB)/lib*.a

mrproper: clean
	-rm $(BIN)/main doc/html/*
