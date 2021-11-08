//
//  TwoBodyDecay.cpp
//  
//
//  Created by Giulio on 05/11/2021.
//

#include <iostream>

#include "TwoBodyDecay.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "Functions.h"

using namespace std;

//Costruttore
TwoBodyDecay::TwoBodyDecay(TLorentzVector& Mother, TLorentzVector& son1, TLorentzVector& son2){
    Mother_= &Mother;
    son1_= &son1;
    son2_= &son2;
};

TwoBodyDecay::~TwoBodyDecay(){
    cout<<"TwoBodyDecay::~TwoBodyDecay() called" <<endl;
};

//QUESTO CREA UN DECADIMENTO A DUE CORPI: ESTRAE RANDOMICAMENTE DUE DIREZIONI PER LE PARTICELLE FIGLIE E CALCOLA IL MODULO DELL'IMPULSO PER LE DUE, DUNQUE CREA DUE 4-MOMENTI PER LE PARTICELLE E INFINE COMPIE IL BOOST NEL LAB DI MASSA DATO DALLA PARTICELLA MADRE
void TwoBodyDecay::StartDecay(){
    cout<<"\n** INIZIO DECADIMENTO **\n"<<endl;
    //genero casualmente le direzioni finali
    double theta = genTheta();
    double phi = genPhi();

    //genero i due momenti nel CM delle particelle
    double pstar = pStar();
    double px = pstar*cos(phi)*sin(theta), py=pstar*sin(phi)*sin(theta), pz = pstar*cos(theta);

    //set del 4-momento delle due particelle nel cm
    TLorentzVector p1, p2;
    p1.SetPxPyPzE(px, py, pz, sqrt(son1_->M()*son1_->M() + pstar*pstar));
    p2.SetPxPyPzE(-px, -py, -pz, sqrt(son2_->M()*son2_->M() + pstar*pstar));
    
    //ottengo i parametri per il boost del LAB dalla particella madre
    TVector3 boost_vec = Mother_->BoostVector();

    //faccio il boost nel LAB    
    p1.Boost(boost_vec);
    p2.Boost(boost_vec);
    
    //ora assegno i risultati alle particelle figlie
    *son1_ = p1;
    *son2_ = p2;
    
    cout<<"\n** FINE DECADIMENTO **\n"<<endl;
    
};
