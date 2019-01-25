//
//  mutacion.cpp
//  
//
//  Created by Óscar López Arcos on 28/12/16.
//
//

#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "mutacion.h"
#include "enfermedad.h"

using namespace std;

/**
	@file mutacion.hxx
	@brief fichero de implementacion de la clase mutacion
 
 */

/**
	@brief Constructor por defecto.
	Crea un objeto mutacion con sus parametros vacíos.
 */

mutacion::mutacion()	//constructor sin parametros
{
    ID = "";
    chr = "";
    pos = 0;
    common = false;
    
}

/**
	@brief Constructor de copia
	@param m: Mutación que queremos copiar
 
	Construye un objeto copiando m
 */
mutacion::mutacion(const mutacion& m)		//constuctor de copia
{
    ID = m.ID;
    chr = m.chr;
    pos = m.pos;
    ref_alt = m.ref_alt;
    genes = m.genes;
    common = m.common;
    caf = m.caf;
    enfermedades = m.enfermedades;
    clnsig = m.clnsig;
}

/**
	@brief Constructor a partir de cadena
	@param str: Cadena.
 
	Recibe un string con especificaciones y crea un objeto mutación
 */
mutacion::mutacion(const string & str)	//para crear objeto mutacion a partir de la cadena que contiene una linea completa del fichero de entrada
{
    int i = 2;
    string s;
    vector<string> database;
    vector<string> ID_aux;
    vector<string> name;
    enfermedad enfermedad_aux;
    
    s = str[0];
    
    if (str[1] != '\t'){
        s.push_back(str[1]);
        i = 3;
    }
    
    chr = s;	//Lectura numero de cromosoma (Campo CHR)
    s.clear();
    while (str[i] != '\t'){
        s.push_back(str[i]);
        i++;
    }
    
    pos = atoi(s.c_str());	//Lectura posicion dentro del cromosoma (Campo POS)
    i++;
    s.clear();
    while(str[i] != '\t'){
        s.push_back(str[i]);
        i++;
    }
    
    ID = s;		//Lectura identificador posicion dentro del cromosoma (Campo ID)
    
    i++;
    int contador = 0;
    bool sigue_leyendo;
    s.clear();
    while (contador < 4){		//Lectura base(s) en el genoma de referencia y alternativa(s) posible(s) (Campo relf_alt)
        sigue_leyendo = false;
        if (str[i] == '\t')
            i++;
        else if(str[i] == '.'){
            i++;
            contador++;
        }
        else{
            while(str[i] != '\t'){
                if(str[i+1] == ','){
                    CargarString(s, ref_alt, str[i]);
                    CargarString(s, ref_alt, str[i+2]);
                    contador += 2;
                    i+=4;
                }
                else{
                    s.push_back(str[i]);
                    i++;
                    sigue_leyendo = true;
                }
            }
        }
        if(sigue_leyendo){
            ref_alt.push_back(s);
            contador++;
        }
        s.clear();
    }
    
    s.clear();
    
    i = SaltarCampo(str, "GENEINFO");
    if(i != -1)
        LeerCampoString(str, genes, i);
    
    i = SaltarCampo(str, "CLNSIG");
    LeerCampoInt(str, clnsig, i);
    
    i = SaltarCampo(str, "CLNDSDB");
    LeerCampoString(str, database, i);
    
    i = SaltarCampo(str, "CLNDSDBID");
    LeerCampoString(str, ID_aux, i);
    
    i = SaltarCampo(str, "CLNDBN");
    LeerCampoString(str, name, i);
    
    for (int i = 0; i < database.size(); i++){
        enfermedad_aux.setName(name[i]);
        enfermedad_aux.setID(ID_aux[i]);
        enfermedad_aux.setDatabase(database[i]);
        enfermedades.push_back(enfermedad_aux);
    }
    
    i = SaltarCampo(str, "CAF");
    if(i != -1)
        LeerCampoFloat(str, caf , i);
    else
        caf.push_back(1.0);
    
    i = SaltarCampo(str, "COMMON");
    if(i != -1)
        common = str[i];
    else
        common = false;
}

/**
	@brief Establece el ID
	@param id: ID de la mutacion
 */
void mutacion::setID(const string & id)
{
    this->ID = id;
}
/**
	@brief Establece el cromosoma
	@param chr: Cromosoma de la mutacion
 */
void mutacion::setChr(const string & chr)
{
    this->chr = chr;
}

/**
	@brief Establece la posicion
	@param pos: Posicion de la mutacion
 */
void mutacion::setPos(const unsigned int & pos)
{
    this->pos = pos;
}

/**
	@brief Establece la(s) base(s) en el genoma de referencia
	@param ref_alt: Genoma de referencia de la mutacion
 */
void mutacion::setRef_alt(const std::vector<string> & ref_alt)
{
    this->ref_alt = ref_alt;
}

/**
	@brief Establece el/los gen(es) asociado(s) al SNP
	@param genes: Genes asociados
 */
void mutacion::setGenes (const std::vector<string> & genes)
{
    this->genes = genes;
}

/**
	@brief Establece si es comun
	@param common: "true" si es comun
 */
void mutacion::setCommon (const bool & common)
{
    this->common = common;
}

/**
	@brief Establece la frecuencia de cada base del SNP en la poblacion
	@param caf: frecuencia de cada base del SNP en la poblacion
 */

void mutacion::setCaf (const std::vector<float> & caf)
{
    this->caf = caf;
}


/**
	@brief Establece enfermedades asociadas al SNP
	@param enfermedades: enfermedades asociadas
 */
void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades)
{
    this->enfermedades = enfermedades;
}

/**
	@brief Establece relevancia clinica del SNP para cada enfermedad
	@param clnsig: relevancia clinica del SNP
 */
void mutacion::setClnsig (const std::vector<int> & clnsig)
{
    this->clnsig = clnsig;
}

/**
	@brief Obtiene el ID
	@return ID de la mutacion
 */
string mutacion::getID( ) const
{
    return ID;
}

/**
	@brief Obtiene el cromosoma
	@return Cromosoma de la mutacion
 */
string mutacion::getChr( ) const
{
    return chr;
}

/**
	@brief Obtiene la posicion
	@return Posicion de la mutacion
 */

unsigned int mutacion::getPos( ) const
{
    return pos;
}

/**
	@brief Obtiene la(s) base(s) en el genoma de referencia
	@return Genoma de referencia de la mutacion
 */
const std::vector<string> & mutacion::getRef_alt () const
{
    return ref_alt;
}

/**
	@brief Obtiene el/los gen(es) asociado(s) al SNP
	@return Genes asociados
 */
const std::vector<string> & mutacion::getGenes () const
{
    return genes;
}

/**
	@brief Obtiene si es comun
	@return "true" si es comun
 */

bool mutacion::getCommon () const
{
    return common;
}

/**
	@brief Obtiene la frecuencia de cada base del SNP en la poblacion
	@return frecuencia de cada base del SNP en la poblacio
 */
const std::vector<float> & mutacion::getCaf () const
{
    return caf;
}

/**
	@brief Obtiene enfermedades asociadas al SNP
	@return enfermedades asociadas
 */

const std::vector<enfermedad> & mutacion::getEnfermedades () const
{
    return enfermedades;
}

/**
	@brief Obtiene relevancia clinica del SNP para cada enfermedad
	@return relevancia clinica del SNP
 */
const std::vector<int> & mutacion::getClnsig () const
{
    return clnsig;
}

/**
	@brief Asignacion de mutacion
	@param m: Mutacion que se asigna
	@return El valor de m
 */
mutacion & mutacion::operator=(const mutacion & m)
{
    if(&m != this){
        ID = m.ID;
        chr = m.chr;
        pos = m.pos;
        ref_alt = m.ref_alt;
        genes = m.genes;
        common = m.common;
        caf = m.caf;
        enfermedades = m.enfermedades;
        clnsig = m.clnsig;
    }
    return *this;
}

/**
	@brief Mutaciones iguales
	@param m: mutacion con la que vamos a comparar
	@return "true" si son iguales, "false" si no lo son
	Compara si dos mutaciones son iguales
 */
bool mutacion::operator==(const mutacion & m) const
{
    bool iguales = false;
    
    if(ID == m.ID)
        iguales = true;
    
    return iguales;
}

/**
	@brief Orden segun cromosoma
	@param m: mutacion con la que vamos a comparar
	@return "true" si es anterior, "false" si es posterior
 
	El orden viene determinado por Chr y pos. El primer criterio es el número de cromosoma. El orden para el numero de cromosoma se rige por "1"<"2"<"3"<...<"22"<"X"<"Y"<"MT". Dos mutaciones del mismo cromosoma deben ordenarse según su posicion, de menor posicion a mayor (orden natural de enteros).
 */

bool mutacion::operator<(const mutacion & m) const
{
    string cadena1 = chr;
    string cadena2 = m.chr;
    bool menor = false;
    
    if(cadena1 == "X")
        cadena1 = "23";
    
    if(cadena1 == "Y")
        cadena1 = "24";
    
    if(cadena1 == "MT")
        cadena1 = "25";
    
    if(cadena2 == "X")
        cadena2 = "23";
    
    if(cadena2 == "Y")
        cadena2 = "24";
    
    if(cadena2 == "MT")
        cadena2 = "25";
    
    if(atoi(cadena1.c_str()) == atoi(cadena2.c_str())){
        if(pos < m.pos)
            menor = true;
    }
    else if(atoi(cadena1.c_str()) < atoi(cadena2.c_str()))
        menor = true;
    
    return menor;
}

bool mutacion::operator>(const mutacion & m) const
{
    string cadena1 = chr;
    string cadena2 = m.chr;
    bool mayor = false;
    
    if(cadena1 == "X")
        cadena1 = "23";
    
    if(cadena1 == "Y")
        cadena1 = "24";
    
    if(cadena1 == "MT")
        cadena1 = "25";
    
    if(cadena2 == "X")
        cadena2 = "23";
    
    if(cadena2 == "Y")
        cadena2 = "24";
    
    if(cadena2 == "MT")
        cadena2 = "25";
    
    if(atoi(cadena1.c_str()) == atoi(cadena2.c_str())){
        if(pos > m.pos)
            mayor = true;
    }
    else if(atoi(cadena1.c_str()) > atoi(cadena2.c_str()))
        mayor = true;
    
    return mayor;
}


bool mutacion::operator<=(const mutacion & m) const
{
    string cadena1 = chr;
    string cadena2 = m.chr;
    bool menor = false;
    
    if(cadena1 == "X")
        cadena1 = "23";
    
    if(cadena1 == "Y")
        cadena1 = "24";
    
    if(cadena1 == "MT")
        cadena1 = "25";
    
    if(cadena2 == "X")
        cadena2 = "23";
    
    if(cadena2 == "Y")
        cadena2 = "24";
    
    if(cadena2 == "MT")
        cadena2 = "25";
    
    if(atoi(cadena1.c_str()) == atoi(cadena2.c_str())){
        if(pos <= m.pos)
            menor = true;
    }
    else if(atoi(cadena1.c_str()) < atoi(cadena2.c_str()))
        menor = true;
    
    return menor;
}

/**
	@brief Operador de conversion a texto (escritura).
	@param os: flujo al que se envia el texto. Es MODIFICADO.
	@param f: Mutacion que se escribe.
	@return el flujo os.
	Escribe en el flujo os el valor de e convetido a texto y devuelve os
 */
ostream& operator<<(ostream &os, const mutacion & m)
{
    os << m.getChr() << '\t';
    os << m.getPos() << '\t';
    os << m.getID() << '\t';
    
    for (int i = 0; i < m.getRef_alt().size(); i++)
        os << m.getRef_alt()[i] << '\t';
    
    if(m.getGenes().size() > 0){
        os << "GENEINFO=";
        
        for (int i = 0; i < m.getGenes().size(); i++){
            os << m.getGenes()[i];
            if(i+1 < m.getGenes().size())
                os << '|';
        }
        os << ';';
    }
    
    os << "CLNSIG=";
    
    for (int i = 0; i < m.getClnsig().size(); i++){
        os << m.getClnsig()[i];
        if(i+1 < m.getClnsig().size())
            os << '|';
    }
    
    os << ';';
    
    os << "CLNDSDB=";
    
    for (int i = 0; i < m.getEnfermedades().size(); i++){
        os << m.getEnfermedades()[i].getDatabase();
        if(i+1 < m.getEnfermedades().size())
            os << '|';
    }
    
    os << ';';
    
    os << "CLNDSDBID=";
    
    for (int i = 0; i < m.getEnfermedades().size(); i++){
        os << m.getEnfermedades()[i].getID();
        if(i+1 < m.getEnfermedades().size())
            os << '|';
    }
    
    os << ';';
    
    os << "CLNDBN=";
    
    for (int i = 0; i < m.getEnfermedades().size(); i++){
        os << m.getEnfermedades()[i].getName();
        if(i+1 < m.getEnfermedades().size())
            os << '|';
    }
    
    if(m.getCaf().size() > 0){
        os << ';';
        os << "CAF=";
        
        for (int i = 0; i < m.getCaf().size(); i++){
            os << m.getCaf()[i];
            if(i+1 < m.getCaf().size())
                os << '|';
        }
    }
    
    os << ';';
    
    os << "COMMON=";
    os << m.getCommon();
    
    return os;
}

/**
	@brief Cargar String
	@param elemento: caracter que se añade al string "s"
	@param s: string que se añade al vector "vector"
	@param vector: vector de strings
	
	Guarda en el vector "vector" el string "s" al que se le ha añadido el caracter "elemento"
 */
void CargarString(string &s, vector<string> & vector, char elemento)
{
    s.push_back(elemento);
    vector.push_back(s);
    s.clear();
}

/**
	@brief Saltar identificador del campo
	@param str: texto en el que esta el campo
	@param campo: nombre del identificador del campo
	@return posición en la que empezar a escribir
 
	El programa busca el identificador del campo en str y devuelve la posición donde acaba (incluyendo el =)
 */

int SaltarCampo(string str, string campo)
{
    int posicion_lectura;
    
    posicion_lectura = str.find(campo);
    if(posicion_lectura != -1){
        while(str[posicion_lectura] != '=')
            posicion_lectura++;
        posicion_lectura++;
    }
    
    return posicion_lectura;
}

/**
	@brief Leer nombre del del campo (STRING)
	@param str: texto en el que esta el campo
	@param vector: Vector que guarda el campo
	@param posicion_lectura: Indica por donde empezar a leer
 
	Lee el campo y guarda el/los valor/es en el vector "vector"
 */
void LeerCampoString(string str, vector<string> & vector, int posicion_lectura)
{
    string s;
    bool sigue_leyendo;
    
    while(str[posicion_lectura] != ';'){
        sigue_leyendo = false;
        s.push_back(str[posicion_lectura]);
        
        if (str[posicion_lectura+1] == '|' || str[posicion_lectura+1] == ','){
            vector.push_back(s);
            posicion_lectura+=2;
            sigue_leyendo = true;
        }
        else
            posicion_lectura++;
        
        if(str[posicion_lectura] == ';'){
            vector.push_back(s);
        }
        
        if (sigue_leyendo)
        {
            s.clear();
        }
    }
}

/**
	@brief Leer nombre del del campo (INT)
	@param str: texto en el que esta el campo
	@param vector: Vector que guarda el campo
	@param posicion_lectura: Indica por donde empezar a leer
 
	Lee el campo y guarda el/los valor/es en el vector "vector"
 */

void LeerCampoInt(string str, vector<int> & vector, int posicion_lectura)
{
    string s;
    bool sigue_leyendo;
    
    while(str[posicion_lectura] != ';'){
        sigue_leyendo = false;
        s.push_back(str[posicion_lectura]);
        
        if (str[posicion_lectura+1] == '|' || str[posicion_lectura+1] == ','){
            vector.push_back(atoi(s.c_str()));
            posicion_lectura+=2;
            sigue_leyendo = true;
        }
        else
            posicion_lectura++;
        
        if(str[posicion_lectura] == ';'){
            vector.push_back(atoi(s.c_str()));
        }
        
        if (sigue_leyendo)
        {
            s.clear();
        }
    }
}

/**
	@brief Leer nombre del del campo (FLOAT)
	@param str: texto en el que esta el campo
	@param vector: Vector que guarda el campo
	@param posicion_lectura: Indica por donde empezar a leer
 
	Lee el campo y guarda el/los valor/es en el vector "vector"
 */

void LeerCampoFloat(string str, vector<float> & vector, int posicion_lectura)
{
    string s;
    bool sigue_leyendo;
    
    while(str[posicion_lectura] != ';'){
        sigue_leyendo = false;
        s.push_back(str[posicion_lectura]);
        
        if (str[posicion_lectura+1] == '|' || str[posicion_lectura+1] == ','){
            vector.push_back(strtof(s.c_str(), NULL));
            posicion_lectura+=2;
            sigue_leyendo = true;
        }
        else
            posicion_lectura++;
        
        if(str[posicion_lectura] == ';'){
            vector.push_back(strtof(s.c_str(), NULL));
        }
        
        if (sigue_leyendo)
        {
            s.clear();
        }
    }
}
