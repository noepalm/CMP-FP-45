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
        TLorentzVector *Mother_, *son1_, *son2_;
        
    public:
        //Constructors and Deconstructors
        TwoBodyDecay();
        TwoBodyDecay(TLorentzVector& Mother, TLorentzVector& son1, TLorentzVector& son2);

        //Deconstructor
        ~TwoBodyDecay();

        //Generate two random angles
        double genTheta(); //restituisce un angolo theta in gradi
        double genPhi(); //restituisce un angolo phi in gradi

        // calcolo l'impulso
        double pStar(){return sqrt(pow(Mother_->M()*Mother_->M() + son1_->M()*son1_->M() - son2_->M()*son2_->M(),2) - 4*son1_->M()*son1_->M()*Mother_->M()*Mother_->M())/(2*Mother_->M());};
        void StartDecay();
};

#endif /* TwoBodyDecay_h */
