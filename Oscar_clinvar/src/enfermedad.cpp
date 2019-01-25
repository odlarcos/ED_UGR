//
//  enfermedad.cpp
//  
//
//  Created by Óscar López Arcos on 28/12/16.
//
//

#include "enfermedad.h"

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

/**
	@file enfermedad.hxx
	@brief fichero de implementacion de la clase enfermedad
 
 */

/**
	@brief Constructor por defecto.
	Crea un objeto enfermedad con sus parametros vacios.
 */

enfermedad::enfermedad(){
    name = "";
    ID = "";
    database = "";
    // @todo implementar esta funcion
}

/**
	@brief Constructor con parámetros
	@param name: nombre de la enfermedad
	@param ID: ID de la enfermedad
	@param database: base de datos asociada a la enfermedad
	Crea un objeto enfermedad con esos parámetros
 */

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
    // @todo implementar esta funcion
    this->name = name;
    this->ID = ID;
    this->database = database;
}

// @todo implementar el resto de metodos especificados en enfermedad.h

/**
	@brief Establece el nombre
	@param name: nombre de la enfermedad
 */
void enfermedad::setName(const string & name){
    this->name = name;
}

/**
	@brief Establece el ID
	@param ID: ID de la enfermedad
 */

void enfermedad::setID(const string & ID){
    this->ID = ID;
}

/**
	@brief Establece la base de datos
	@param database: base de datos de la enfermedad
 */

void enfermedad::setDatabase(const string & database){
    this->database = database;
}

/**
	@brief Obtiene el nombre
	@return Nombre de la enfermedad
 */
string enfermedad::getName() const{
    return name;
}

/**
	@brief Obtiene el ID
	@return ID de la enfermedad
 */

string enfermedad::getID() const{
    return ID;
}

/**
	@brief Obtiene la base de datos
	@return base de datos de la enfermedad
 */

string enfermedad::getDatabase() const{
    return database;
}

/**
	@brief Asignacion de enfermedad
	@param e: Enfermedad que se asigna
	@return El valor de e
 */

enfermedad& enfermedad::operator=(const enfermedad &e){
    
    if(this != &e){
        this->name = e.name;
        this->ID = e.ID;
        this->database = e.database;
    }
    
    return *this;
}

/**
	@brief Enfermedad a string
	@return nombre, ID y base de datos juntos en un string
	Devuelve enfermedad convertida a string
 */
string enfermedad::toString() const{
    string total = name +'\t'+ ID +'\t'+ database;
    return total;
}

/**
	@brief Enfermedades iguales
	@param e: enfermedad con la que vamos a comparar
	@return "true" si son iguales, "false" si no lo son
	Compara si dos enfermedades son iguales
 */
bool enfermedad::operator==(const enfermedad &e) const{
    bool iguales = false;
    
    if(this->name == e.name && this->ID == e.ID && this->database == e.database)
        iguales = true;
    
    return iguales;
}

/**
	@brief Enfermedades distintas
	@param e: enfermedad con la que vamos a comparar
	@return "true" si son distintas, "false" si no lo son
	
	Compara si dos enfermedades son distintas
 */

bool enfermedad::operator!=(const enfermedad &e) const{
    bool distintos = false;
    
    if(this->name != e.name || this->ID != e.ID || this->database != e.database)
        distintos = true;
    
    return distintos;
}

/**
	@brief Orden alfabetico según el nombre
	@param e: enfermedad con la que vamos a comparar
	@return "true" si es anterior alfabticamente, "false" si es posterior
 */

bool enfermedad::operator< ( const enfermedad & e ) const{
    bool menor = false;
    
    if((this->name) < e.name)
        menor = true;
    
    return menor;
}

/**
	@brief Contiene el nombre
	@param str: cadena que vamos a ver si contiene
	@return "true" si la contiene, "false" si no
 */
bool enfermedad::nameContains(const string & str) const{
    bool contiene = false;
    
    string nombre = this->name;
    string ref = str;
    char *NOMBRE = new char [nombre.length()+1];
    char *REF = new char [ref.length()+1];
    
    strcpy(NOMBRE, nombre.c_str());
    strcpy(REF, ref.c_str());
    
    for(int i=0; NOMBRE[i] != '\0'; i++)
        NOMBRE[i] = tolower(NOMBRE[i]);
    
    for(int j=0; REF[j] != '\0'; j++)
        REF[j] = tolower(REF[j]);
    
    nombre = NOMBRE;
    ref = REF;
    
    
    if( (nombre).find(ref) != string::npos)
        contiene = true;
    
    return contiene;
}

/**
	@brief Operador de conversionn a texto (escritura).
	@param os: flujo al que se nvia el texto. Es MODIFICADO.
	@param f: Enfermedad que se escribe.
	@return el flujo os.
	Escribe en el flujo os el valor de e convetido a texto y devuelve os
 */

ostream& operator<< ( ostream& os, const enfermedad & e){
    // @todo implementa esta funcion
    os << e.getName() << '\t' << e.getID() << '\t' << e.getDatabase();
    os << endl;
    // os << e.getName() ;
    //...
    return os;
}



