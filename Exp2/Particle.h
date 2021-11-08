//
//  Particle.h
//  
//
//  Created by Giulio on 05/11/2021.
//

/*
 
 DEFINISCO LA CLASSE PARTICLE DEFINITA DALLE QUANTITA' MASSA, MOMENTO, THETA NEL CM E
 
 */

#ifndef Particle_h
#define Particle_h

#include "TLorentzVector.h"
#include <string>

class Particle{

    private:
        std::string name_; //name of the particle
        double mass_;//mass of the particle
        TLorentzVector p4_CM_; //Four Momentum in the rest fram
        TLorentzVector p4_LAB_; //Four Momentum in the rest fram
        double Px_LAB_;
        double Py_LAB_;
        double Pz_LAB_;
        
    public:
        //Costruttori
        Particle(const std::string& name);
        Particle(const std::string& name, double m,double Px_LAB,double Py_LAB,double Pz_LAB); //p_LAB è la componente di p lungo l'asse x (l'unico asse dove il momento nel LAB è non nullo
        Particle Particle1(const std::string& name, double m,double Px_LAB,double Py_LAB,double Pz_LAB);
        
        //Distruttori
        ~Particle();

        //setters
        void setMass(double m){mass_=m;};
        void setp4_LAB(TLorentzVector p4){p4_LAB_=p4;};
        void setp4_CM(TLorentzVector p4){p4_CM_=p4;};
        
        //getters
        std::string name(){return name_;};
        double mass(){return mass_;};
        TLorentzVector p4_CM(){return p4_CM_;};
        TLorentzVector p4_LAB(){return p4_LAB_;};
        
        //Calculate the CM 4-momentum
        
        
        //printer
        void print();
        
        
        //Overload
        Particle operator=(Particle& par);
};

#endif /* Particle_h */
