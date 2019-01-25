/* 
 * enfermedad.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/

/**
	@brief Constructor por defecto.
	Crea un objeto enfermedad con sus parametros vacios.
*/

#ifndef _ENFERMEDAD_H_
#define _ENFERMEDAD_H_

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)
 
 @todo Implementa esta clase, junto con su documentación asociada

*/

class enfermedad {
private:
  string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
  string  ID;         // ID único para la enfermedad
  string  database;   // Base de datos que provee el ID

public:
    /**
     @brief Constructor por defecto.
     Crea un objeto enfermedad con sus parametros vacios.
     */
 enfermedad (); //Constructor de enfermedad por defecto
    /**
     @brief Constructor con parámetros
     @param name: nombre de la enfermedad
     @param ID: ID de la enfermedad
     @param database: base de datos asociada a la enfermedad
     Crea un objeto enfermedad con esos parámetros
     */
 enfermedad (const string & name, const string & ID, const string & database); 
    /**
     @brief Establece el nombre
     @param name: nombre de la enfermedad
     */
 void setName(const string & name);
    /**
     @brief Establece el ID
     @param ID: ID de la enfermedad
     */
 void setID(const string & ID);
    /**
    @brief Establece la base de datos
    @param database: base de datos de la enfermedad
    */
 void setDatabase(const string & database);

    /**
     @brief Obtiene el nombre
     @return Nombre de la enfermedad
     */
 string getName( ) const;
    /**
     @brief Obtiene el ID
     @return ID de la enfermedad
     */
 string getID( ) const;
    /**
     @brief Obtiene la base de datos
     @return base de datos de la enfermedad
     */
 string getDatabase( ) const;
    /**
     @brief Asignacion de enfermedad
     @param e: Enfermedad que se asigna
     @return El valor de e
     */
 enfermedad & operator=(const enfermedad & e);
    /**
     @brief Enfermedad a string
     @return nombre, ID y base de datos juntos en un string
     Devuelve enfermedad convertida a string
     */
 string toString() const;

// Operadores relacionales
    /**
     @brief Enfermedades iguales
     @param e: enfermedad con la que vamos a comparar
     @return "true" si son iguales, "false" si no lo son
     Compara si dos enfermedades son iguales
     */
 bool operator==(const enfermedad & e) const;
    /**
     @brief Enfermedades distintas
     @param e: enfermedad con la que vamos a comparar
     @return "true" si son distintas, "false" si no lo son
     
     Compara si dos enfermedades son distintas
     */
 bool operator!=(const enfermedad & e) const;
    /**
     @brief Orden alfabetico según el nombre
     @param e: enfermedad con la que vamos a comparar
     @return "true" si es anterior alfabticamente, "false" si es posterior
     */
 bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name. 

    /**
     @brief Contiene el nombre
     @param str: cadena que vamos a ver si contiene
     @return "true" si la contiene, "false" si no
     */
 bool nameContains(const string & str) const;   //Devuelve True si str está incluido en el nombre de la enfermedad, aunque no se trate del nombre completo. No debe ser sensible a mayúsculas/minúsculas. 

};

/**
	@brief Operador de conversionn a texto (escritura).
	@param os: flujo al que se nvia el texto. Es MODIFICADO.
	@param f: Enfermedad que se escribe.
	@return el flujo os.
	Escribe en el flujo os el valor de e convetido a texto y devuelve os
 */
ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)

//#include "enfermedad.hxx" // Incluimos la implementacion.

#endif
