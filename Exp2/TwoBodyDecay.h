//
//  TwoBodyDecay.h
//  
//
//  Created by Giulio on 05/11/2021.
//

#ifndef TwoBodyDecay_h
#define TwoBodyDecay_h
#include "Particle.h"

class TwoBodyDecay{

    private:
        Particle* Mother_;
        Particle* son1_;
        Particle* son2_;

    public:
        //Constructors and Deconstructors
        TwoBodyDecay();
        TwoBodyDecay(Particle& Mother,Particle& son1, Particle& son2);

        //Deconstructor
        ~TwoBodyDecay();

        //Generate two random angles
        double genTheta(); //restituisce un angolo theta in gradi
        double genPhi(); //restituisce un angolo phi in gradi

        // calcolo l'impulso
        double pStar_1(){return sqrt(pow(Mother_->mass()*Mother_->mass()+son1_->mass()*son1_->mass()-son2_->mass()*son2_->mass(),2)-4*son1_->mass()*son1_->mass()*Mother_->mass()*Mother_->mass())/(2*Mother_->mass());};
        double pStar_2(){return sqrt(pow(Mother_->mass()*Mother_->mass()+son2_->mass()*son2_->mass()-son1_->mass()*son1_->mass(),2)-4*son2_->mass()*son2_->mass()*Mother_->mass()*Mother_->mass())/(2*Mother_->mass());};
        void StartDecay(Particle& mother,Particle& son1,Particle& son2);
    
};

#endif /* TwoBodyDecay_h */
