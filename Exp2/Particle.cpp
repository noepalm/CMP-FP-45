//
//  Particle.cpp
//  
//
//  Created by Giulio on 05/11/2021.
//

#include "Particle.h"
#include <iostream>
//#include "TMath.h"
#include <cmath>
#include <string>

using namespace std;

Particle::Particle(const string& name){
    name_=name;
};

Particle::Particle(const string& name, double m,double Px_LAB,double Py_LAB,double Pz_LAB){
    name_=name;
    mass_=m;
    Px_LAB_=Px_LAB;
    Py_LAB_=Py_LAB;
    Pz_LAB_=Pz_LAB;
    p4_LAB_.SetPxPyPzE(Px_LAB,Py_LAB,Pz_LAB,sqrt((Px_LAB*Px_LAB+Py_LAB*Py_LAB+Pz_LAB*Pz_LAB)+mass_*mass_));
};
Particle Particle::Particle1(const string& name, double m,double Px_LAB,double Py_LAB,double Pz_LAB){
    name_=name;
    mass_=m;
    Px_LAB_=Px_LAB;
    Py_LAB_=Py_LAB;
    Pz_LAB_=Pz_LAB;
    p4_LAB_.SetPxPyPzE(Px_LAB,Py_LAB,Pz_LAB,sqrt((Px_LAB*Px_LAB+Py_LAB*Py_LAB+Pz_LAB*Pz_LAB)+mass_*mass_));
    
};


Particle::~Particle(){
    cout<<"Particle::~Particle() called for Particle " << name_ <<endl;
};


void Particle::print(){
    cout<<" Print() called for Particle "<<name_<<" with mass: "<<mass_<<"\n"<<endl;
    cout<<" LAB 4-momentum: "<<endl;
    p4_LAB_.Print();
    cout<<" \n"<<"CM 4-momentum: "<<endl;
    p4_CM_.Print();
    cout<<"\n"<<endl;
};



Particle Particle::operator=(Particle& par){
    return Particle::Particle1(name_,mass_,par.Px_LAB_,par.Py_LAB_,par.Pz_LAB_);
};




/*
double Particle::gentTheta_CM(){
    TRandom3 *r = new TRandom3(0);
    //Genero coordinate sulla sfera e poi prendo gli angoli phi* e theta*
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    r->Sphere(x, y, z, rho);
    Double_t thetaStar=acos(z)*360/(2*M_PI);
    delete r;
    
    return thetaStar;
}/*
/*double Particle::gentPhi_CM(){
    TRandom3 *r = new TRandom3(0);
    //Genero coordinate sulla sfera e poi prendo gli angoli phi* e theta*
    Double_t rho = 1;
    Double_t x = 0, y = 0, z = 0;
    r->Sphere(x, y, z, rho);
    Double_t phiStar=atan2(y,x)*360/(2*M_PI);
    delete r;
    
    return phiStar;
}*/



