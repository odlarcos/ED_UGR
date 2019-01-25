/* 
 * mutacion.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/

/**
	@brief Constructor por defecto.
	Crea un objeto mutacion con sus parametros vacíos.
*/

#ifndef _MUTACION_H_
#define _MUTACION_H_

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "enfermedad.h"

using namespace std;
//! Clase mutacion, asociada a la definición de una mutación/SNP 
/*! mutacion::mutacion,  .....
 * 
 @todo Implementa esta clase, junto con su documentación asociada

*/


class mutacion {
 private:
  string ID; // rs...
  string chr; // numerico del prinsipio
  unsigned int pos; // pos
  std::vector<string> ref_alt; // LETRAS GUAPAS
  std::vector<string> genes; //GENEINFO separados por |
  bool common; // COMMON
  std::vector<float> caf; // CAF separados por ,
  std::vector<enfermedad> enfermedades; //NOMBRE SNP, ID CLNDSDBID, database CLNDSDB. SEPARADOS POR | dentro de cada campo
  std::vector<int> clnsig; // numero o numeros separados por , | si hay varias enfermedades

 public:

    /**
     @brief Constructor por defecto.
     Crea un objeto mutacion con sus parametros vacíos.
     */

  mutacion();
    
    /**
     @brief Constructor de copia
     @param m: Mutación que queremos copiar
     
     Construye un objeto copiando m
     */
  mutacion(const mutacion& m);
    
    /**
     @brief Constructor a partir de cadena
     @param str: Cadena.
     
     Recibe un string con especificaciones y crea un objeto mutación
     */
  mutacion(const string & str);   //para crear objeto mutacion a partir de la cadena que contiene una línea completa del fichero de entrada
 
    /**
     @brief Establece el ID
     @param id: ID de la mutacion
     */
  void setID(const string & id);
    /**
     @brief Establece el cromosoma
     @param chr: Cromosoma de la mutacion
     */
  void setChr(const string & chr);
    /**
     @brief Establece la posicion
     @param pos: Posicion de la mutacion
     */
  void setPos(const unsigned int & pos);
    /**
     @brief Establece la(s) base(s) en el genoma de referencia
     @param ref_alt: Genoma de referencia de la mutacion
     */
  void setRef_alt(const std::vector<string> & ref_alt);
    /**
     @brief Establece el/los gen(es) asociado(s) al SNP
     @param genes: Genes asociados
     */
  void setGenes (const std::vector<string> & genes);
    /**
     @brief Establece si es comun
     @param common: "true" si es comun
     */
  void setCommon (const bool & common);
    /**
     @brief Establece la frecuencia de cada base del SNP en la poblacion
     @param caf: frecuencia de cada base del SNP en la poblacion
     */
  void setCaf (const std::vector<float> & caf);
    /**
     @brief Establece enfermedades asociadas al SNP
     @param enfermedades: enfermedades asociadas
     */
  void setEnfermedades (const std::vector<enfermedad> & enfermedades);
    /**
     @brief Establece relevancia clinica del SNP para cada enfermedad
     @param clnsig: relevancia clinica del SNP
     */
  void setClnsig (const std::vector<int> & clnsig);  
  
    /**
     @brief Obtiene el ID
     @return ID de la mutacion
     */
  string getID( ) const;
    /**
     @brief Obtiene el cromosoma
     @return Cromosoma de la mutacion
     */
  string getChr( ) const;
    /**
     @brief Obtiene la posicion
     @return Posicion de la mutacion
     */
  unsigned int getPos( ) const;
    /**
     @brief Obtiene la(s) base(s) en el genoma de referencia
     @return Genoma de referencia de la mutacion
     */
  const std::vector<string> & getRef_alt () const;
    /**
     @brief Obtiene el/los gen(es) asociado(s) al SNP
     @return Genes asociados
     */
  const std::vector<string> & getGenes () const;
    /**
     @brief Obtiene si es comun
     @return "true" si es comun
     */
  bool getCommon () const;
    /**
     @brief Obtiene la frecuencia de cada base del SNP en la poblacion
     @return frecuencia de cada base del SNP en la poblacio
     */
  const std::vector<float> & getCaf () const;
    /**
     @brief Obtiene enfermedades asociadas al SNP
     @return enfermedades asociadas
     */
  const std::vector<enfermedad> & getEnfermedades () const;
    /**
     @brief Obtiene relevancia clinica del SNP para cada enfermedad
     @return relevancia clinica del SNP
     */
  const std::vector<int> & getClnsig () const;
    
    /**
     @brief Asignacion de mutacion
     @param m: Mutacion que se asigna
     @return El valor de m
     */
  mutacion & operator=(const mutacion & m);
    /**
     @brief Mutaciones iguales
     @param m: mutacion con la que vamos a comparar
     @return "true" si son iguales, "false" si no lo son
     Compara si dos mutaciones son iguales
     */
  bool operator==(const mutacion & m) const;
    /**
     @brief Orden segun cromosoma
     @param m: mutacion con la que vamos a comparar
     @return "true" si es anterior, "false" si es posterior
     
     El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el numero de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posicion, de menor posicion a mayor (orden natural de enteros).
     */
  bool operator<(const mutacion & m) const;      //El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el número de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posición, de menor posición a mayor (orden natural de enteros).
  bool operator>(const mutacion & m) const;
  bool operator<=(const mutacion & m) const;
};

/**
	@brief Operador de conversion a texto (escritura).
	@param os: flujo al que se envia el texto. Es MODIFICADO.
	@param f: Mutacion que se escribe.
	@return el flujo os.
	Escribe en el flujo os el valor de e convetido a texto y devuelve os
 */
  ostream& operator<< ( ostream& , const mutacion& );   //Imprimir TODOS los campos del objeto mutación.
  void CargarString(string &s, vector<string> & vector, char elemento);
  int SaltarCampo(string str, string campo);
  void LeerCampoString(string str, vector<string> & vector, int posicion_lectura);
  void LeerCampoInt(string str, vector<int> & vector, int posicion_lectura);
  void LeerCampoFloat(string str, vector<float> & vector, int posicion_lectura);

//#include "mutacion.hxx"
#endif
