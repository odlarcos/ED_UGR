#include "clinvar.h"
#include "mutacion.h"
#include "enfermedad.h"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void clinvar::load(string nombreBD){

 	ifstream fe;
 	string cadena;

 	cout << "Abrimos "<< nombreBD << endl;
 	fe.open(nombreBD.c_str(), ifstream::in);
 	if (fe.fail()){
   		cerr << "Error al abrir el fichero " << nombreBD << endl;
 	} 
 	else{
    		//leo la cabecera del fichero (líneas que comienzan con #)
    		do{ 
      			getline(fe,cadena,'\n'); 

    		}while (cadena.find("#")==0 && !fe.eof());

    		//leo la tabla de mutaciones, una linea cada vez
    		while ( !fe.eof() ){ 
      			getline(fe,cadena,'\n');
      			if (!fe.eof()) {
        			//cout << "leo:: "<< cadena << endl;
        		// Invoco el constructor de mutacion que recibe una cadena completa, la parsea y crea la mutacion.
        			mutacion mut = mutacion(cadena);
        		// Insertar mutacion en contenedores
				pair< set<mutacion>::iterator, bool > par;

        			par = mutDB.insert(mut); // Inserto en mutDB

				if(par.second){

					IDm_map[mut.getID()] = par.first; // Inserto en IDm_map
					
					const std::vector<string> genes = mut.getGenes(); // Guardo genes

					map<IDgen, list< set<mutacion>::iterator> >::iterator itc;
                    
					for(int i=0; i < genes.size(); i++){ // Por cada gen INSERTO GEN_MAP
						
						list< set<mutacion>::iterator> l;
						itc = gen_map.find( genes[i] ); // FIND

						if ( itc == gen_map.end() ){ // Si no está, lo inserto
							
							l.push_back(par.first);
							gen_map.insert( map<IDgen, list< set<mutacion>::iterator> >::value_type( genes[i], l));
						}
						else{		// Si está, cojo la lista y le añado iterador a la mut
							l = itc->second;
							l.push_back(par.first);
							itc->second = l;
						}
							
					}
					vector<enfermedad> enfermedades = mut.getEnfermedades(); // IDENF_MAP y EnfDB
					for(int i=0; i < enfermedades.size(); i++){
						IDenf_map.insert( multimap<IDenf,set<mutacion>::iterator>::value_type(enfermedades[i].getID(), par.first));
						EnfDB.insert( map<IDenf,enfermedad>::value_type(enfermedades[i].getID(), enfermedades[i]));
					}
				}
      			}
    		}
    		fe.close();
    		//return true;
  	} // else

  	fe.close();
  	//return false;
}

void clinvar::insert (const mutacion & x){

	pair< set<mutacion>::iterator, bool > par;

       	par = mutDB.insert(x); // Inserto en mutDB

	if(par.second){

		IDm_map[x.getID()] = par.first; // Inserto en IDm_map
					
		const std::vector<string> genes = x.getGenes(); // Guardo genes

		map<IDgen, list< set<mutacion>::iterator> >::iterator itc;

		for(int i=0; i < genes.size(); i++){ // Por cada gen INSERTO GEN_MAP
						
			list< set<mutacion>::iterator> l;
			itc = gen_map.find( genes[i] ); // FIND

			if ( itc == gen_map.end() ){ // Si no está, lo inserto
							
				l.push_back(par.first);
				gen_map.insert( map<IDgen, list< set<mutacion>::iterator> >::value_type( genes[i], l));
			}
			else{		// Si está, cojo la lista y le añado iterador a la mut
				l = itc->second;
				l.push_back(par.first); 
				itc->second = l;
			}
							
		}
		vector<enfermedad> enfermedades = x.getEnfermedades(); // IDENF_MAP y EnfDB
		for(int i=0; i < enfermedades.size(); i++){
			IDenf_map.insert( multimap<IDenf,set<mutacion>::iterator>::value_type(enfermedades[i].getID(), par.first));
			EnfDB.insert( map<IDenf,enfermedad>::value_type(enfermedades[i].getID(), enfermedades[i]));
		}
	}
}


bool clinvar::erase (IDmut ID){
	
	set<mutacion>::iterator it;

	unordered_map<IDmut,set<mutacion>::iterator>::iterator ito; //** Este se podrá cambiar

	ito = IDm_map.find(ID);		// Iterador a dónde esté el IDmut
	
	if( ito == IDm_map.end() )
		return false;
	else{
		it = ito->second; 	//Asigno el it del set al second del unordered_map
		IDm_map.erase(ito);	// BORRO DE IDm_map  (unordered map)

		mutacion x = *it;	// Busco la mutacion x en el set principal QUIZÁS NO NECESARIO

		const std::vector<string> genes = x.getGenes(); // *it.getGenes()
		
		map<IDgen, list< set<mutacion>::iterator> >::iterator itc;
		for(int i=0; i < genes.size(); i++){
			
			itc = gen_map.find( genes[i] ); // itc apunta al gen
			
			(itc->second).remove( it ); // Borro de la lista (itc->second) el it (iterador al set)
			
			if( (itc->second).empty() )
				gen_map.erase(itc); // Si era el último, BORRO el objeto entero de gen_map

						
		}
		
		
		vector<enfermedad> enfermedades = x.getEnfermedades();
		for(int i=0; i < enfermedades.size(); i++){

			int num = IDenf_map.count( enfermedades[i].getID() );
			
			if( num == 1){
				IDenf_map.erase(enfermedades[i].getID() );

				EnfDB.erase(enfermedades[i].getID() );
			}
			else{
				pair < multimap<IDenf, set<mutacion>::iterator>::iterator, multimap<IDenf, set<mutacion>::iterator>::iterator > ret;

   				ret = IDenf_map.equal_range( enfermedades[i].getID() );

    				for (multimap<IDenf,set<mutacion>::iterator>::const_iterator i=ret.first; i!=ret.second; ++i)
      					if( i->second == it )
							IDenf_map.erase(i);
			
			}
		}
		mutDB.erase(it);	// BORRO DE mutDB (EL SET ORIGINAL)	
	}
	return true;
}

clinvar::iterator clinvar::find_Mut (IDmut ID){
	
	iterator it;
	
	unordered_map<IDmut,set<mutacion>::iterator>::iterator ito;

	ito = IDm_map.find(ID);		// Iterador a dónde esté el IDmut
	
	it.it = ito->second;
	
	return it;
	
}

clinvar::enfermedad_iterator clinvar::find_Enf(IDenf ID){
	
	enfermedad_iterator it;
	
	it = EnfDB.find(ID);
	
	return it;
}

vector<enfermedad> clinvar::getEnfermedades(mutacion & mut){
	
	vector<enfermedad> v = mut.getEnfermedades();
	
	return v;
}

list<IDenf> clinvar::getEnfermedades(string keyword){
	
	list<IDenf> l;
	enfermedad_iterator it;
	
	for( it = EnfDB.begin(); it != EnfDB.end(); it++)
		if ( (it->second).nameContains(keyword) )
			l.push_back(it->first);
			
	return l;
}

set<IDmut> clinvar::getMutacionesEnf (IDenf ID){
	
	set<IDmut> s;
	
	pair < multimap<IDenf, set<mutacion>::iterator>::iterator, multimap<IDenf, set<mutacion>::iterator>::iterator > ret;
	ret = IDenf_map.equal_range( ID );
	// Recorro todos los que contengan el keyword ID
    for (multimap<IDenf,set<mutacion>::iterator>::const_iterator i=ret.first; i!=ret.second; ++i)    	s.insert( (i->second)->getID() ) ; // Inserto en el set el ID de la mutacion a la que apunta el it que está en el second
    	
    return s;
}

set<IDmut> clinvar::getMutacionesGen (IDgen ID){ // set ID de mutaciones asociadas a un gen
	
	set<IDmut> s;
	map<IDgen, list< set<mutacion>::iterator> >::iterator it;
	it = gen_map.find(ID);
	if( it != gen_map.end() ){
			list< set<mutacion>::iterator>::iterator i; 
			for( i = (it->second).begin(); i != (it->second).end(); i++)
				s.insert( (*i)->getID() ); // (*(*i) ).getID()
	}
	
	return s;
}


set<mutacion,ProbMutaciones> clinvar::topKMutaciones (int k, string keyword){
	
	set<IDmut> s;
	unordered_set<IDmut> aux;
	priority_queue< mutacion, vector<mutacion> , ProbMutaciones> cola;
	set<mutacion, ProbMutaciones> conjunto;
	
	list<IDenf> l = getEnfermedades(keyword); // Hallo una list con las ID de enfermedades asociadas a keyword
	unsigned contador = 0;
	
	for( list<IDenf>::iterator i = l.begin(); i != l.end(); i++ ){ // Recorro la lista
		s = getMutacionesEnf(*i);				// Guardo en el set los ID de mutaciones asociadas a las enfermedades (por su ID)
		
		for(set<IDmut>::iterator it = s.begin(); it != s.end(); it++){ // RECORRO EL SET
		
			mutacion mut = *( (IDm_map.find(*it))->second);		// mut = la mutacion a la que correspone el ID
			
			if( aux.find( mut.getID() ) == aux.end() ) // Si el ID de la mutacion no está en aux
				if (contador < k){	//Así metería las 10 primeras del tirón
					//cout<<mut<<endl;
					//cout<<mut.getCaf()[0]<<endl;
					cola.push( mut );	
					aux.insert(mut.getID()); // Inserto en aux su ID
					contador++;
				}
				else if ( 1 - mut.getCaf()[0] > 1 - cola.top().getCaf()[0]  ) { // Si no, compara si es menor que el top
					cola.pop();
					cola.push(mut);
					aux.insert(mut.getID());
				}
		}
	}
	
	for(int i=0; i < k; i++){
		conjunto.insert(cola.top());
		cola.pop();
	}
	
	return conjunto;
}


//---------- FUNCTOR -----------------

bool ProbMutaciones::operator()(const mutacion& a, const mutacion& b)
{
	
    return (1-a.getCaf()[0] >= 1-b.getCaf()[0]); // a.getCaf()[0] < b.getCaf()[0] :S
}

//---------- ITERATOR CLASE -----------

const mutacion & clinvar::iterator::operator*(){
	return *it;
}

const clinvar::iterator & clinvar::iterator::operator=(iterator x){
	if( this != &x )
		this->it = x.it;
				
	return *this;
}

/*
const clinvar::iterator & clinvar::iterator::operator=(set<mutacion>::iterator it){
	this->it = it;
	
	return *this;
}
*/

const clinvar::iterator & clinvar::iterator::operator++(){
	++it;
	
	return *this;

}

const clinvar::iterator clinvar::iterator::operator++(int val){
	iterator aux = *this;
	++(*this);
	return aux;
}

bool clinvar::iterator::operator==(iterator x){
	
	return it == x.it;
}

bool clinvar::iterator::operator==(set<mutacion>::iterator it){
	
	return this->it == it;
}

bool clinvar::iterator::operator!=(iterator x){
	
	return it != x.it;
}

bool clinvar::iterator::operator!=(set<mutacion>::iterator it){
	
	return this->it != it;
}

//---------- GEN_ITERATOR CLASE -----------

const mutacion & clinvar::gen_iterator::operator*(){
	return *(*itlist);
}

const clinvar::gen_iterator & clinvar::gen_iterator::operator=(gen_iterator x){
	if( this != &x){
		itmap = x.itmap;
		itlist = x.itlist;
		ptrclinvar = x.ptrclinvar;
	}
	return *this;
}

const clinvar::gen_iterator & clinvar::gen_iterator::operator++(){
	
	if( itlist != --(itmap->second).end() ){
		itlist++;
	}
	else{
		itmap++;
		if(itmap != ptrclinvar->gen_map.end() )
		itlist = (itmap->second).begin();
	}
	
	return *this;
}

const clinvar::gen_iterator clinvar::gen_iterator::operator++(int val){
	
	gen_iterator aux = *this;
	
	if( itlist != --(itmap->second).end() ){
		itlist++;
	}
	else{
		itmap++;
		if(itmap != (ptrclinvar->gen_map).end() )
		itlist = (itmap->second).begin();
	}
	
	return aux;
}

bool clinvar::gen_iterator::operator==(gen_iterator x){
	
	if(itlist == x.itlist && itmap == x.itmap)
		return true;
	else
		return false;
}

bool clinvar::gen_iterator::operator!=(gen_iterator x){
	
	if(itlist != x.itlist || itmap != x.itmap)
		return true;
	else
		return false;
}

//---------- MÉTODOS ITERATOR ----------

clinvar::iterator clinvar::begin(){
	iterator it;
	it.it = mutDB.begin();
	return it;
}

clinvar::iterator clinvar::end(){
	iterator it;
	it.it = mutDB.end();
	return it;
}

clinvar::iterator clinvar::lower_bound(string cromosoma, unsigned int posicion){
	mutacion mut;
	mut.setChr(cromosoma);
	mut.setPos(posicion);
	
	iterator it;
	it.it = mutDB.begin();
	
	while(*it < mut) // Se para en el primero 
		it.it++;
		
	return it;
}

clinvar::iterator clinvar::upper_bound(string cromosoma, unsigned int posicion){
	mutacion mut;
	mut.setChr(cromosoma);
	mut.setPos(posicion);
	
	iterator it;
	it.it = mutDB.begin();
	
	while(*it <= mut) // Se para en el último
		it.it++;
		
	return it;
}

clinvar::enfermedad_iterator clinvar::ebegin(){
	enfermedad_iterator it;
	it = EnfDB.begin();
	return it;
}

clinvar::enfermedad_iterator clinvar::eend(){
	enfermedad_iterator it;
	it = EnfDB.end();
	return it;
}

clinvar::gen_iterator clinvar::gbegin(){
	gen_iterator it;
	
	it.itmap = gen_map.begin();
	it.itlist = ( ( gen_map.begin() )->second ).begin();
	it.ptrclinvar = this;
	return it;
}

clinvar::gen_iterator clinvar::gend(){ 
	gen_iterator it;
	
	it.itmap = (gen_map.end());
	it.itlist = ( ( --(gen_map.end()) )->second ).end();
	it.ptrclinvar = this;
	return it;
}

 