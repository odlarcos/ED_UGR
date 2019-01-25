#ifndef _CLINVAR_H_
#define _CLINVAR_H_

/**
	@brief Constructor por defecto.
	Crea un objeto mutacion con sus parametros vacíos.
 */

#include "mutacion.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <queue>
#include <set>
#include <vector>

using namespace std;
typedef string IDgen;
typedef string IDmut;
typedef string IDenf;

//! Functor ProbMutaciones
class ProbMutaciones{
public:
    /**
     @brief Criterio de ordenacion segun probabilidad
     @param a: Primera mutacion
     @param b: Segunda mutacion
     
     Criterio de ordenacion segun probabilidad
     */
    bool operator()(const mutacion &a, const mutacion &b);
};

//! Clase clinvar
class clinvar{
  public:

  class iterator;
  class gen_iterator;
  
    /* @brief iterador sobre mutaciones
     */
    
	class iterator {
		  private:
		    friend class clinvar;
		    set<mutacion>::iterator it;
		  public:
		    const mutacion & operator*();
		    const iterator & operator=(iterator it);
		    const iterator & operator=(set<mutacion>::iterator it);
		    const iterator & operator++();
		    const iterator operator++(int val);
		    bool operator==(iterator x);
		    bool operator==(set<mutacion>::iterator it);
		    bool operator!=(iterator x);
		    bool operator!=(set<mutacion>::iterator it);
	};
	
	
	/* @brief iterador sobre enfermedades
	  */

	typedef  map<IDenf, enfermedad>::iterator enfermedad_iterator;
	
	/* @brief iterador sobre mutaciones considerando el orden creciente del ID del gen
	  */
	class gen_iterator {
	    public:
  	    friend class clinvar;
  	    const mutacion & operator*();
  	    const gen_iterator & operator=(gen_iterator it);
  		  const gen_iterator & operator++();
  		  const gen_iterator operator++(int val);
  		  bool operator==(gen_iterator x);
  		  bool operator==(set<mutacion>::iterator it);
  		  bool operator!=(gen_iterator x);
	   
	    private:
    		map<IDgen, list< set<mutacion>::iterator> >::iterator itmap;
    		list< set<mutacion>::iterator >::iterator itlist;
    		clinvar *ptrclinvar;
	};	


    //...
    
    /**
     @brief Cargar mutaciones
     @param nombreDB: Nombre del archivo donde están las mutaciones
     
     Construye clinvar a partir del archivo de mutaciones
     */
    void load (string nombreDB);
    /**
     @brief Insertar mutación
     @param x: mutación a insertar
     
     Inserta la mutacion en el conjunto clinvar
     */
    void insert (const mutacion & x);
    /**
     @brief Elimina mutación
     @param ID: ID de mutación a eliminar
     
     Elimina la mutacion en el conjunto clinvar
     */
    bool erase (IDmut ID);
    /**
     @brief Busca mutación por ID
     @param ID: ID de mutación a buscar
     @return iterator a la mutacion
     Busca la mutacion en el conjunto clinvar
     */
    iterator find_Mut (IDmut ID);
    
    /**
     @brief Busca enfermedad por ID
     @param ID: ID de enfermedad a buscar
     @return iterator a la enfermedad
     Busca la enfermedad en el conjunto clinvar
     */
    enfermedad_iterator find_Enf(IDenf ID);
    /**
     @brief Obtiene enfermedades asociadas a mutacion
     @param mut: mutación de la que obtener enfermedades
     @return vector de enfermedades
     Obtiene enfermedades asociadas a mutacion
     */
    vector<enfermedad> getEnfermedades(mutacion & mut);
    /**
     @brief Obtiene ID de enfermedades asociadas a una palabra
     @param keyword: palabra de la que obtener enfermedades
     @return lista de ID de enfermedades
     Obtiene ID de enfermedades asociadas a una palabra
     */
    list<IDenf> getEnfermedades(string keyword);
    /**
     @brief Obtiene ID de mutaciones asociadas a una enfermedad
     @param ID: ID enfermedad de la que obtener mutaciones
     @return set de ID de mutaciones
     Obtiene ID de mutaciones asociadas a una enfermedad
     */
    set<IDmut> getMutacionesEnf (IDenf ID);
    /**
     @brief Obtiene ID de mutaciones asociadas a un gen
     @param ID: ID gen del que obtener mutaciones
     @return set de ID de mutaciones
     Obtiene ID de mutaciones asociadas a un gen
     */
    set<IDmut> getMutacionesGen (IDgen ID);
    /**
     @brief Obtiene k mutaciones de mayor probabilidad que contienen keyword
     @param k: Numero de mutaciones
     @param keyword: keyword
     @return set de k mutaciones más probables
    */
    set<mutacion,ProbMutaciones> topKMutaciones (int k, string keyword);

    /* Métodos relacionados con los iteradores */
    
    iterator begin();
    iterator end();
    iterator lower_bound(string cromosoma, unsigned int posicion);
    iterator upper_bound(string cromosoma, unsigned int posicion);
    enfermedad_iterator ebegin();
    enfermedad_iterator eend();
    gen_iterator gbegin();
    gen_iterator gend();

  private:
    friend class iterator;
    friend class gen_iterator;
    
    set<mutacion> mutDB; //base de datos que contiene toda la información asociada a una mutacion
    unordered_map<IDmut,set<mutacion>::iterator> IDm_map; // Asocia IDmutacion con mutación
    map<IDgen, list< set<mutacion>::iterator> > gen_map; // Asocia genes con mutaciones
    map<IDenf,enfermedad> EnfDB; // Base de datos de enfermedades
    multimap<IDenf,set<mutacion>::iterator> IDenf_map; // Asocia enfermedad con mutaciones
};

//#include "clinvar.hxx"
#endif
