//
//  TwoBodyDecay.cpp
//  
//
//  Created by Giulio on 05/11/2021.
//

#include <iostream>
#include "TwoBodyDecay.h"
#include "Particle.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TLorentzVector.h"

using namespace std;

//Costruttore
TwoBodyDecay::TwoBodyDecay(Particle& Mother,Particle& son1, Particle& son2){
    Mother_= &Mother;
    son1_= &son1;
    son2_= &son2;
};

TwoBodyDecay::~TwoBodyDecay(){
    cout<<"TwoBodyDecay::~TwoBodyDecay() called" <<endl;
};

//Genero i due angoli

double TwoBodyDecay::genTheta(){
    TRandom3 *r = new TRandom3(0);
    //Genero coordinate sulla sfera e poi prendo gli angoli phi* e theta*
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    r->Sphere(x, y, z, rho);
    Double_t thetaStar=acos(z)*360/(2*M_PI);
    delete r;
    
    return thetaStar;
};

double TwoBodyDecay::genPhi(){
    TRandom3 *r = new TRandom3(0);
    //Genero coordinate sulla sfera e poi prendo gli angoli phi* e theta*
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    r->Sphere(x, y, z, rho);
    Double_t phiStar=atan2(y,x)*360/(2*M_PI);
    delete r;
    
    return phiStar;
};

//QUESTO CREA UN DECADIMENTO A DUE CORPI: ESTRAE RANDOMICAMENTE DUE DIREZIONI PER LE PARTICELLE FIGLIE E CALCOLA IL MODULO DELL'IMPULSO PER LE DUE, DUNQUE CREA DUE 4-MOMENTI PER LE PARTICELLE E INFINE COMPIE IL BOOST NEL LAB DI MASSA DATO DALLA PARTICELLA MADRE


void TwoBodyDecay::StartDecay(Particle& mother,Particle& son1,Particle& son2){
    cout<<"\n** INIZIO DECADIMENTO **\n"<<endl;
    //genero casualmente le direzioni finali
    double theta1_CM=TwoBodyDecay::genTheta();
    double phi1_CM=TwoBodyDecay::genPhi();
    double theta2_CM=TwoBodyDecay::genTheta();
    double phi2_CM=TwoBodyDecay::genPhi();
    //genero i due momenti nel CM delle particelle
    double p1=pStar_1();
    double p2=pStar_2();
    //set del 4-momento delle due particelle nel cm
    TLorentzVector p1_CM;
    TLorentzVector p2_CM;
    p1_CM.SetPxPyPzE(p1*cos(phi1_CM)*sin(theta1_CM),p1*sin(phi1_CM)*sin(theta1_CM),p1*cos(theta1_CM),sqrt(son1.mass()*son1.mass()+p1*p1));
    p2_CM.SetPxPyPzE(p2*cos(phi2_CM)*sin(theta2_CM),p1*sin(phi2_CM)*sin(theta2_CM),p2*cos(theta2_CM),sqrt(son2.mass()*son2.mass()+p2*p2));
    //ora assegno i risultati alle particelle figlie
    son1.setp4_CM(p1_CM);
    son2.setp4_CM(p2_CM);
    
    //ottengo i parametri per il boost del LAB dalla particella madre
    mother.p4_LAB().BoostVector();
    //faccio il boost nel LAB
    TLorentzVector p1_LAB=p1_CM;//lo setto inizialmente uguale al cm
    TLorentzVector p2_LAB=p2_CM;//lo setto inizialmente uguale al cm
    
    p1_LAB.Boost(mother.p4_LAB().BoostVector());
    p2_LAB.Boost(mother.p4_LAB().BoostVector());
    
    
    son1.setp4_LAB(p1_LAB);
    son2.setp4_LAB(p2_LAB);
    
    mother.print();
    son1.print();
    son2.print();
    
    
    cout<<"\n** FINE DECADIMENTO **\n"<<endl;
    
};
