//
//  main.cpp
//  Created by Óscar López Arcos on 24/12/16.

#include "clinvar.h"
#include "mutacion.h"
#include "enfermedad.h"

#include <stdio.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <list>
#include <queue>
#include <set>
#include <vector>

using namespace std;


int main(){
    
    clinvar conjunto;
    
    conjunto.load("./datos/prueba.vcf");
    
    mutacion m = mutacion("19	10759731	rs148318860	C	A,T	.	.	RS=148318860;RSPOS=10759731;dbSNPBuildID=134;SSR=0;SAO=1;VP=0x050060080005040036100100;GENEINFO=DNM2:1785;WGT=1;VC=SNV;PM;INT;ASP;VLD;KGPhase1;KGPhase3;LSD;CLNALLE=1;CLNHGVS=NC_000019.10:g.10759731C>A;CLNSRC=.;CLNORIGIN=1;CLNSRCID=.;CLNSIG=2|2;CLNDSDB=MedGen|MedGen:OMIM;CLNDSDBID=CN169374|C1847902:606482;CLNDBN=not_specified|DNM2-related_intermediate_Charcot-Marie-Tooth_neuropathy;CLNREVSTAT=single|single;CLNACC=RCV000175646.1|RCV000205800.1");
    
    conjunto.insert(m);

    if ( !conjunto.erase("rs571063157") )
        cout<<"rs571063157 No existe\n";
    else
        cout<<"Mutacion rs571063157 borrada correctamente\n";
    
    cout<<endl;
    
    clinvar::iterator i;
    
    i = conjunto.find_Mut("rs863224450");
    cout<<"Mutacion rs863224450 encontrada:\n";
    cout<<*i;
    
    cout<<endl;
    cout<<"\n---------MUTACIONES---------\n";
    
    i = conjunto.begin();
    
    while(i != conjunto.end()){
        cout<<*i<<endl;
        ++i;
    }
    
    cout<<endl;
    cout<<"\n---------ENFERMEDADES---------\n";
    
    clinvar::enfermedad_iterator eit;
    
    eit = conjunto.ebegin();
    
    while(eit != conjunto.eend()){
        cout<< eit->second <<endl;
        ++eit;
    }
    
    list<IDenf> l;
    list<IDenf>::iterator it;
    
    cout<<endl;
    cout<<"\nIDs Enfermedades asociadas a cancer:  ";
    l = conjunto.getEnfermedades("cancer");
    for(it = l.begin(); it != l.end(); it++)
        cout<<*it<<" ";
    
    cout<<endl;
    cout<<"\n---------TOP K MUT---------\n";
    
    set<mutacion,ProbMutaciones> s = conjunto.topKMutaciones(10, "cancer");
    
    for(set<mutacion,ProbMutaciones>::iterator si = s.begin(); si != s.end(); si++)
        cout<< *si <<endl;
    
    cout<<endl;
    cout<<"\n---------Mutaciones sociadas al gen PALB2:79728---------\n";
    
    set<IDmut> sg = conjunto.getMutacionesGen("PALB2:79728");
    
    for(set<IDmut>::iterator si = sg.begin(); si != sg.end(); si++)
        cout<< *conjunto.find_Mut(*si)<<endl;
    
    cout<<endl;
    cout<<"\n---------Mutaciones asociadas a la enfermedad C0027672:699346009---------\n";
    
    sg = conjunto.getMutacionesEnf("C0027672:699346009");
    for(set<IDmut>::iterator si = sg.begin(); si != sg.end(); si++)
        cout<< *conjunto.find_Mut(*si)<<endl;
    
    cout<<endl;
    cout<<"\n---------Mutaciones ordenadas segun GEN---------\n";
    
    for( clinvar::gen_iterator g = conjunto.gbegin(); g != conjunto.gend(); g++)
        cout<<*g<<endl;
    
    return 0;
    
}
